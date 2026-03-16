# 侯捷老师的c++课程学习笔记
## 三.面向对象开发
### 3.1 头文件与类的声明
#### 3.1.1 头文件的保护措施
在头文件中，通过 #define 定义一个名字，并且通过条件编译 #ifndef...#endif 使得编译器可以根据这个名字是否被定义，再决定要不要继续编译该头文中后续的内容。  
```cpp 
#ifndef _COMPLEX_
#define _COMPLEX_
{
    ......//class define
}
#endif
```
不这样定义的话，很有可能出现“重复”，比如类B包含了头文件head.h,类A在定义时也用到了head.h。类C同时用到了A,B两类，包含了A.h与B.h,就出现了重复错误。
#### 3.1.2 类的声明
类的声明方式如下
```cpp
class copmlex//class+类名
{
    public：//能被直接访问的成员函数等
        complex (double r = 0,double i = 0)
			: re (r) ,im (i)
		{ }
    private：//不能被直接访问的数据成员等
        double re,im;
};//不要忘了分号
```
#### 3.1.3 类内访问权限
C++ 中，类的成员（数据成员和成员函数）的访问权限（public/private/protected）是 针对类外部的代码 而言的，类内部的成员函数不受这些权限限制。
```cpp
class Box {
private:
    int length;
public:
    Box(int l) : length(l) {}
    // 成员函数：比较当前对象与另一个Box对象的长度
    bool isLongerThan(const Box& other) const {
        // 直接访问other的私有成员length（合法！）
        return this->length > other.length; 
    }
};
```
也就是说，private 成员 length 虽然不允许类外部的代码直接访问，但类自己的成员函数（如 isLongerThan()）可以自由访问它。
### 3.2 构造函数
构造函数的名称要与类名完全相同，对于complex类，其构造函数必须名为complex，如下：
```cpp
complex (double r = 0,double i = 0)
		: re (r) ,im (i)
		{ }
```
#### 3.2.1 初始化成员列表
上述的声明方式，是构造函数特有的声明方式，其中
```cpp
:re (r) ,im (i)
```
称作Member Initializer List，初始化成员列表，在对象创建时，成员变量 re 和 im 直接以 r 和 i 为初始值进行构造（相当于 re(r) 和 im(i) 的直接调用）。  
当然,构造函数也可以写作
```cpp
complex (double r = 0,double i = 0){re=r ,im=i;}
```
这样，成员变量经历了 “默认构造 → 赋值” 两个阶段（即使是基础类型，也存在逻辑上的两步操作）  
第一种写法的效率更高，此外，还有许多场景不允许使用第二种写法。因此，实际开发中应优先使用第一种写法。
```cpp
//必须使用初始化成员列表的一种情况
class Test {
private:
    const int value; // const成员变量，必须初始化且不能修改
public:
    // 正确：必须用初始化列表初始化const成员
    Test(int v) : value(v) {} 

    // 错误：函数体中赋值无法初始化const成员（const变量不能被赋值）
    // Test(int v) { value = v; } // 编译报错
};
```
#### 3.2.2 重载
构造函数当然允许重载，但是，下面这段代码中的重载是不合法的
```cpp
complex (double r = 0,double i = 0)
			: re (r) ,im (i)
		{ }
complex () : re(0),im(0) { } //valid
```
如果程序这样定义
```cpp
complex c1();
```
则会导致冲突，因为此时两个构造函数都可以生效。    
如果第一个构造函数没有默认值 =0，第二种重载则是允许的，此时想使用第一种构造函数，必须要写入参数
### 3.3 参数传递与返回
#### 3.3.1 引用
引用不是新定义一个变量，而是给**已经存在的变量**取了一个**别名**。
```cpp
using namespace std
int main()
{
    int a=10;
    int& b=a;
    cout<<"The value of a is: "<<a<<endl;
    cout<<"The value of b is: "<<b<<endl;
    cout<<"The address of a is: "<<&a<<endl;
    cout<<"The address of b is: "<<&b<<endl;
    return 0;
}
```
其运行结果为： 
```cpp
The value of a is: 10
The value of b is: 10
The address of a is: 0x000137DF5A
The address of a is: 0x000137DF5A
```
b是a的引用，共用一块地址，无论修改谁的值，另一个的值都发生同样的变化。  
要注意取地址和引用完全不同，只是共用了&符号而已。  
```cpp
int* p = &a;         // 取 a 的地址，赋值给指针 p（p 存储 a 的地址）
int& b = a;          // 声明 b 是 a 的引用（别名）
```
取地址（& 运算符）：是 “查询地址” 的动作，结果是一个地址值，用于指针相关操作。  
引用（& 声明）：是 “变量的别名”，与原变量共内存，用于简化操作、避免拷贝
#### 3.3.2 传递值或引用
传值时，函数会创建原变量的一份独立拷贝，函数内部操作的是这份 “副本”，而非原变量本身。

传引用时，函数接收的是原变量的 “别名”，函数内部操作的本质是原变量本身。

传值适用于基础类型、小对象，或无需修改原变量且怕生命周期问题时

传引用适用于大对象（类）且能确保原变量生命周期足够长时
```cpp
// 传非const引用：直接修改外部的Person对象（年龄+1）
void increaseAge(Person& p) { 
    p.age++; 
}

// 传const引用：避免拷贝大vector，且保证不修改外部容器
int getVectorSum(const vector<int>& vec) { 
    int sum = 0;
    for (int num : vec) sum += num;
    return sum;
}
```

#### 3.3.3 返回值或引用
当返回函数内部的局部对象或返回独立的新对象，必须返回值.返回引用会导致 “悬垂引用” 或逻辑错误
```cpp
// 必须返回值：localStr是局部对象，返回引用会崩溃
string createGreeting(const string& name) { 
    string localStr = "Hello, " + name;
    return localStr; // 返回拷贝，调用方可安全接收
}

// 返回值
Point getMidPoint(const Point& p1, const Point& p2) { 
    return Point((p1.x + p2.x)/2, (p1.y + p2.y)/2);
}
```
还有几个例子用作辨析
```cpp
// 返回参数引用：s1/s2由调用方传入，生命周期可控
const string& getLongerStr(const string& s1, const string& s2) { 
    return (s1.size() > s2.size()) ? s1 : s2;
}
```
### 3.4 运算符重载
运算符重载格式如下  
Typename operator 运算符 (参数a,参数b,...)；  
Typename是返回值，可以是基本类型或类
```cpp
//2-1
class complex
{
	public:
		complex& operator += (const complex&);
	private:
        friend complex& _doapl(complex*,const complex&)
        ......
};
inline complex& 
_doapl(complex* ths,const complex& r)
{
	ths->re +=r.re;
	ths->im +=r.im;
	return *ths; 	
}

inline complex&//操作符重载，成员函数 
complex::operator += (const complex& r) //操作符重载 自己定义运算符号 
{
	return _doapl (this,r);
} //比如执行 c2 += c1时 将c1的实部和虚部加到c2上 
```

### 3.5 带有指针的类
定义带指针成员的类String如下  
```cpp
class String
{
	public:
		String(const char* cstr = 0);
		String(const String& str);//拷贝构造 
		String& operator = (const String& str);//拷贝赋值 copy assignment operation 
		~String();//析构函数 
		char* get_c_str() const {return m_data};
	private:
		char* m_data;
}
```
浅拷贝  
浅拷贝是仅复制对象的成员变量值的拷贝方式。对于普通类型（如 int、double），这意味着直接复制值；**但对于指针成员**（或其他指向动态资源的成员，如文件句柄），浅拷贝仅复制指针的 “地址值”，而不复制指针指向的实际数据。
最终结导致多个对象的指针成员会指向同一块内存，共享同一份资源。  
```cpp
int main() {
    String s1("hello"); 
    String s2 = s1; // 假设没有定义拷贝构造函数 则进行浅拷贝：s2.m_data 复制 s1.m_data 的地址（指向同一块内存）

    // s1和s2的m_data指向同一块内存（例如 0x1000）
    return 0; 
   // 问题1:当 s1 和 s2 销毁时，析构函数会两次释放同一块内存（delete[] 0x1000），导致程序崩溃（未定义行为）。
   // 问题2：当后续修改s2时,但无需修改s1时，s1的值也会发生变化
}
```
深拷贝（Deep Copy）  
深拷贝是不仅复制成员变量值，还会为指针成员重新分配内存，并复制原指针指向的实际数据的拷贝方式。深拷贝后，多个对象的指针成员指向独立的内存块，各自拥有一份资源副本，互不干扰。  


#### 3.5.1 拷贝构造
```cpp
String::String(const String& str)//拷贝构造函数 
{
	m_data = new char[strlen(str.m_data)+1];
	strcpy(m_data,str.m_data); 
}
```
#### 3.5.2 拷贝赋值
```cpp
//拷贝赋值函数
String& String::operator = (const String& str)
{
	if (this == &str) return *this;//检测自我赋值 
	delete[] m_data; //先删除自己的内存 
	m_data = new char[ strlen(str.m_data) + 1]; //不检测自我赋值 这里可能会出错 
	strcpy(m_data,str.m_data);
	return *this;
}//一定牢记 this是指针 

```
#### 3.5.3 析构函数
```cpp
String::~String()
{
	delete[] m_data;
}//在对象生命周期结束后，释放对象内存 
```
在没有自定义析构函数时，析构函数可能如下所示  
```cpp
```cpp
String::~String()
{
	delete m_data;
}//在对象生命周期结束后，释放对象内存 
```
这可能会造成内存泄漏，如图所示

#### 3.5.4 概念辨析：初始化&赋值
String s2 = s1; 和 String s2; s2 = s1; 是两种不同的操作，核心区别在于前者是 “初始化”，后者是 “先初始化再赋值”，
```cpp
int a = 10; // 拷贝初始化（定义时用=赋值）
int b(20); // 直接初始化（用()传递初始值）
int c{30}; // 列表初始化（C++11，用{}，更安全）
Point p(1, 2); // 定义p时调用构造函数初始化（内存分配时设置x=1,y=2）
String s1 = s2;//直接创建新对象 s1，不调用默认构造函数；
//而是调用拷贝构造函数，用 s2 的数据初始化 s1

String c1;//调用 String 类的默认构造函数
c1 = s1;// 调用 String 类的拷贝赋值
```
构造函数没有返回类型，它的任务是初始化新对象，执行完毕后对象就已创建完成，无需返回任何内容。  
而拷贝赋值运算符需要返回 *this ,因为它是有返回类型的普通函数，目的是支持链式操作。这是两种函数的语法和语义决定的本质区别。


The rule of big three：如果类需要自定义析构函数、拷贝构造函数或拷贝赋值运算符中的任意一个，那么通常需要同时定义这三个。

### 3.6 补充
#### 3.6.1 模板 template
模板的定义方式为： template
```cpp
template<typename T>
```
