# STL
## 1.lambda 表达式
不带参数列表的Lambda表达式:[captures] { body }    

captures：捕获列表，定义哪些外部变量被 Lambda 表达式捕获以及如何捕获（值捕获或引用捕获）。
body：Lambda 表达式的函数体。

基于不显式模板参数列表的Lambda表达式:[captures](params ) specs(exception) back-attr(trailing-type) requires { body }  

params：参数列表，定义 Lambda 表达式接收的参数。
specs：指定 Lambda 表达式的属性，如 mutable、constexpr 等（可选）。  
exception：异常规范，指定 Lambda 表达式可以抛出的异常类型（可选）。  
back-attr：后置属性（可选）。  
trailing-type：返回类型后置语法（可选）。  
requires：约束表达式，用于模板 Lambda 表达式（可选）。  
```cpp
#include<iostream>
int main()
{
	using namespace std;
	int x=5,y=6;
	auto add_sum = [](int a,int b)->int {return a+b;};//不捕获变量
	cout<<add_sum(x,y)<<endl;
	auto add_sum1 = [&](int a)->int {return a+x;};//引用捕获 外部变量x的改变会影响函数结果
	auto add_sum2 = [=](int a)->int {return a+y;};//值捕获 外部变量y的改变不会影响函数结果
	x=3;
	y=4;
	cout<<add_sum1(3)<<endl;
	cout<<add_sum2(3)<<endl;
}
```

```cpp

```
## 2.STL基础结构：六大部件
```cpp
#include<vector>
#include<algorithm>
#include<functional>
#include<iostream>

using namespace std;

int main()
{
    int vi[6] = {1,2,3,4,5,6};
    vector<int,allocator<int>> arr(vi,vi+6);

    cout<<count_if(vi.begin(),vi.end(),bind2nd(less<int>(),40));
}
```
vector:container容器  
allocator<int>:allocator分配器  
count_if :algorithm算法  
vi.begin(),vi.end():iterator迭代器  
bind2nd:function adapter适配器  
less<int>():function object函数对象

## 3.迭代器 
Iterator迭代  
特点：左闭右开
```cpp
Container<T> c;
...
Container<T>::iterator it= c.begin();//指向c的第一个元素
for(;it!=c.end();it++){...}//指向c的最后一个元素之后的一个位置
```
auto迭代(range-based for statement)
```cpp
vector<int> nums = {1,2,3,4,5};
for(auto num:nums){
    std::cout<<num<<" "<<endl;
}
for(auto &num:nums){
    num*=3;
}

list<int> li;
list<int>::iterator ite;
ite = std::find(li.begin(),li.end(),target);
auto ite =std::find(li.begin(),li.end(),target);//和上一行等效
```
## 4.容器
sequence container
### 4.1 array/vector/list
```cpp
array<int,size> arr;//必须指定size
for(int i=0;i<size;i++){
    arr[i]=rand();
}
cout<<"array.size()"<<arr.size()<<endl;//10
cout<<"array.size()"<<arr.front()<<endl;//第一个元素的值
cout<<"array.size()"<<arr.back()<<endl;//最后一个元素的值
cout<<"array.size()"<<arr.data()<<endl;//arr的地址
```

```cpp
namespace yzl02
{
void test_vector(long& value)//10,000,000
{
vector<string> c;
char buf[10];
    for(int i=0;i<value;i++){
        try{
            snprintf(buf,10,"%d",rand());
            c.push_back(stirng(buf));
        }
        catch(expection& p){
            cout<<"i: "<<i<<" "<<p.what()<<endl;
            abort();
        }
    }
    cout<<"vector.capacity()"<<c.capacity()<<endl;//16,777,216 从1开始成倍增长
    cout<<"vector.size()"<<c.size()<<endl;//10,000,000
    cout<<"vector.front()"<<c.front()<<endl;//第一个元素的值
    cout<<"vector.back()"<<c.back()<<endl;//最后一个元素的值
    cout<<"vector.data()"<<c.data()<<endl;//c的地址
    c.reserve(100000);
    c.resize(5000);
}
}
```
### 4.2 queue
### 4.3 stack
asscoiate container
### 4.4 set/multiset/unorder_set
### 4.5 map/multimap/unorder_map
### 4.6 hashtable