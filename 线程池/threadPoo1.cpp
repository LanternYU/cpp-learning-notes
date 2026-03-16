#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

template<typename T>
class SafeQueue
{
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
public:
	SafeQueue() {}
	SafeQueue(SafeQueue &&other) {}
	~SafeQueue() {}
	
	bool empty()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		
		return m_queue.empty();
	}	
	
	int size()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		
		return m_queue.size();
	}
	
	void enqueue(T& t)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		
		m_queue.emplace(t);
	}
	
	bool dequeue(T &t)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		
		if(m_queue.empty()) return false;
		t = std::move(m_queue.front());//function内重载的移动赋值 更轻量 m_queue.front()后队头元素生命周期结束 安全转移  
		m_queue.pop();
		
		return true;
	}
};

class ThreadPool
{
private:
	class ThreadWorker{
		private:
			int m_id;//工作id 
			ThreadPool *m_pool;//所属线程池 
		public:
			ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id) {}
			void operator()()
			{
				std::function<void()> func;
				bool dequeued;
				while(!(m_pool->m_shutdown))
				{
					{
					// 为线程环境加锁，互访问工作线程的休眠和唤醒
                    std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);

                    // 如果任务队列为空，阻塞当前线程 后续submit时被唤醒 
                    if (m_pool->m_queue.empty())
                    {
                        m_pool->m_conditional_lock.wait(lock); // 等待条件变量通知，开启线程
                    }

                    // 取出任务队列中的元素
                    dequeued = m_pool->m_queue.dequeue(func);
					}
					 // 如果成功取出，执行工作函数 
               		if (dequeued) func(); //即warpper_func() 即(*task_ptr)() 即func();
				}
			}
	};
	
	bool m_shutdown;
	
	SafeQueue<std::function<void()>> m_queue;//任务队列
	
	std::vector<std::thread> m_threads; //工作线程队列
	
	std::mutex m_conditional_mutex;//线程休眠锁互斥变量 
	
	std::condition_variable m_conditional_lock;//线程环境锁 
	
public:
	ThreadPool(const int n_threads = 4)
	:m_threads(std::vector<std::thread>(n_threads)),m_shutdown(false){}
	
	ThreadPool(const ThreadPool &) = delete;//禁用拷贝构造 
	
    ThreadPool(ThreadPool &&) = delete;//禁用移动构造 
    
    ThreadPool &operator = (const ThreadPool &) = delete;//禁用拷贝赋值 
    
    ThreadPool &operator = (ThreadPool &&) = delete;//禁用移动赋值 
		
	void init()
	{
		for(int i = 0;i<m_threads.size();i++)
		{
			m_threads.at(i) = std::thread(ThreadWorker(this, i));
		}
	}		
	
	void shutdown()
	{
		m_shutdown = true;
		m_conditional_lock.notify_all();// 通知，唤醒所有工作线程
		
		for(int i = 0;i<m_threads.size();i++)
		{
			if(m_threads.at(i).joinable())// 判断线程是否在等待
			{
				m_threads.at(i).join();	// 将线程加入到等待队列
			}	
		}
	}
	
	template<typename F,typename... Args>//F f可调用函数类型 ...Args args...可变参数模板 
	auto submit(F&&f,Args&&...args)->std::future<decltype(f(args...))>//后置类型推断 
	{
		std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		//f(args...)整体是一个类型 
		auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
		
		std::function<void()> warpper_func = [task_ptr]()
		{
			(*task_ptr)();
		};//封装为一个返回值为空 参数为空的函数 注意warpper_func是可调用对象 
		
		// 队列通用安全封包函数，并压入安全队列
        m_queue.enqueue(warpper_func);

        // 唤醒一个等待中的线程
        m_conditional_lock.notify_one();

        // 返回先前注册的任务指针
        return task_ptr->get_future();
		
	}
	
};

#include <iostream>
#include <random>
std::random_device rd; // 真实随机数产生器

std::mt19937 mt(rd()); //生成计算随机数mt

std::uniform_int_distribution<int> dist(-1000, 1000); //生成-1000到1000之间的离散均匀分布数

auto rnd = std::bind(dist, mt);

// 设置线程睡眠时间
void simulate_hard_computation()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// 添加两个数字的简单函数并打印结果
void multiply(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

// 添加并输出结果
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl;
}

// 结果返回
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

void example()
{
    // 创建3个线程的线程池
    ThreadPool pool(3);

    // 初始化线程池
    pool.init();

    // 提交乘法操作，总共30个
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 10; ++j)
        {
            pool.submit(multiply, i, j);
        }

    // 使用ref传递的输出参数提交函数
    int output_ref = 0;
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    // 等待乘法输出完成
    future1.get();
    std::cout << "Last operation result is equals to " << output_ref << std::endl;

    // 使用return参数提交函数
    auto future2 = pool.submit(multiply_return, 5, 3);

    // 等待乘法输出完成
    int res = future2.get();
    std::cout << "Last operation result is equals to " << res << std::endl;

    // 关闭线程池
    pool.shutdown();
}
std::mutex mtx; 
class A{
	public:
		A (int i):i(i){}
		void operator()()
		{	
			mtx.lock();
			std::cout<<"TESTA"<<std::endl;
			mtx.unlock();
		}
	private:
		int i;
};
int main()
{
    example();
    return 0;
}
