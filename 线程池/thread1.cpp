#include <iostream>  // std::cout
#include <thread>  // std::thread
#include <mutex>  // std::mutex

std::mutex mtx;  // mutex for critical section
void print_block (int n, char c) 
{
// critical section (exclusive access to std::cout signaled by locking mtx):
    mtx.lock();
    for (int i=0; i<n; ++i) 
    {
       std::cout << c; 
    }
    std::cout << '\n';
    mtx.unlock();
}
int main ()
{
    std::thread th1 (print_block,10,'*');//线程1：打印*
    std::thread th2 (print_block,10,'$');//线程2：打印$
	std::cout<<th1.joinable()<<std::endl;
	std::cout<<th2.joinable()<<std::endl;
    th1.join();
    th2.join();
    std::cout<<th1.joinable()<<std::endl;
	std::cout<<th2.joinable()<<std::endl;
    return 0;
}
