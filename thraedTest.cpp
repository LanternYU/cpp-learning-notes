#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<string>
#include<chrono>
using namespace std;
class Printer{
	private:
		mutex mtx;
		condition_variable cv;
		bool is_free;
	public:
		Printer() :is_free(true) {}
		void print(const string& thread_name, const string& doc_name) {
			unique_lock<mutex> lock(mtx);
			
			while(!is_free){
				cout<<"[等待] 线程 "<<thread_name<<" 等待打印机\n";
				cv.wait(lock,[this](){return is_free;});
			}
			
			is_free = false;
			cout<<"[占用] 线程 "<<thread_name<<" 开始打印<<"<<doc_name<<">>\n";
			lock.unlock();
			
			this_thread::sleep_for(chrono::seconds(rand()%3+10));
			
			lock.lock();
			is_free = true;
			cout<<"[释放] 线程 "<<thread_name<<"打印完成 释放打印机\n";
			cv.notify_all(); 
		}
};

void thread_task(Printer& printer,const string& thread_name) {
	for(int i=0 ;i<2;i++){
		string doc_name = thread_name + "的文档" +to_string(i);
		printer.print(thread_name,doc_name);
		this_thread::sleep_for(chrono::seconds(1));
	}
}
int main(){
	srand(time(0));
	Printer printer;
	thread t1(thread_task,ref(printer),"Thread-1");
	thread t2(thread_task,ref(printer),"Thread-2");
	thread t3(thread_task,ref(printer),"Thread-3");
	t1.join();
	t2.join();
	t3.join();
	return 0;
}
