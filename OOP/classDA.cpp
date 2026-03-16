#include <iostream>
#include <cstring>
using namespace std;

class DynamicArray{
	private:
		int *data;
		int size;
	public:
		DynamicArray(int n,int initvalue = 0);
		~DynamicArray();
		DynamicArray(const DynamicArray& other);
		DynamicArray& operator=(const DynamicArray& other);
		int getSize() const;
		int getElement(int index) const;
		void setElement(int index, int value);
		void print() const;
};
DynamicArray::DynamicArray(int n,int initvalue)
{
	if (n==0){
		data = NULL;
		size = n;
	}else{
		size = n;
		data = new int[size];
		for(int i=0;i<size;i++){
			data[i] = initvalue;
		}
	}
}
DynamicArray::~DynamicArray()
{
	delete [] data;
}
DynamicArray::DynamicArray(const DynamicArray& other)
{
	size=other.size;
	data = new int[size];
	for(int i=0;i<size;i++){
		data[i] = other.data[i];
	}
}
DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
	if(this == &other) return *this;
	delete[] data;
	size=other.size;
	data = new int[size];
	for(int i=0;i<size;i++){
		data[i] = other.data[i];
	}
	return *this;
}
int DynamicArray::getSize() const
{
	return this->size; 
}
int DynamicArray::getElement(int index) const
{
	if(index<0||index>=this->size) return false;
	return data[index];
}
void DynamicArray::setElement(int index,int value)
{
	if(index<0||index>=this->size) return;
	data[index]=value;
}
void DynamicArray::print() const
{
	using namespace std;
	if(size==0) cout<<"[]"<<endl;
	cout<<"["; 
	for(int i=0;i<size;i++){
		cout<<data[i];
		if(i != size - 1) { // 不是最后一个元素才加逗号
            cout << ", ";
        }
	}
	cout<<"]"<<endl;
}

// 测试1：基本构造与析构
void testBasic() {
    cout << "=== 测试基本构造与析构 ===" << endl;
    DynamicArray arr1(3, 5); // 3个元素，初始值5
    arr1.print(); // 预期输出 [5, 5, 5]
    cout << "大小: " << arr1.getSize() << endl; // 预期 3

    DynamicArray arr2(0); // 空数组
    arr2.print(); // 预期输出 []
    cout << endl;
}

// 测试2：拷贝构造（深拷贝检测）
void testCopyConstructor() {
    cout << "=== 测试拷贝构造 ===" << endl;
    DynamicArray arr1(4, 2);
    DynamicArray arr2(arr1); // 拷贝构造

    cout << "原数组: ";
    arr1.print(); // [2, 2, 2, 2]
    cout << "拷贝数组: ";
    arr2.print(); // [2, 2, 2, 2]

    // 修改原数组，检查拷贝数组是否受影响（深拷贝应不受影响）
    arr1.setElement(0, 100);
    cout << "修改后原数组: ";
    arr1.print(); // [100, 2, 2, 2]
    cout << "拷贝数组是否变化: ";
    arr2.print(); // 仍为 [2, 2, 2, 2]
    cout << endl;
}

// 测试3：赋值运算符（深拷贝与自赋值检测）
void testAssignment() {
    cout << "=== 测试赋值运算符 ===" << endl;
    DynamicArray arr1(2, 10);
    DynamicArray arr2(3, 20);
    arr2 = arr1; // 赋值

    cout << "原数组: ";
    arr1.print(); // [10, 10]
    cout << "赋值后数组: ";
    arr2.print(); // [10, 10]，且大小应为2

    // 测试自赋值
    arr1 = arr1; // 不应崩溃
    arr1.print(); // 仍为 [10, 10]

    // 修改原数组，检查赋值后的数组是否受影响
    arr1.setElement(1, 200);
    cout << "修改后原数组: ";
    arr1.print(); // [10, 200]
    cout << "赋值数组是否变化: ";
    arr2.print(); // 仍为 [10, 10]
    cout << endl;
}

// 测试4：索引越界处理
void testIndexBound() {
    cout << "=== 测试索引越界 ===" << endl;
    DynamicArray arr(2, 3);
    cout << "获取合法索引(0): " << arr.getElement(0) << endl; // 3
    cout << "获取越界索引(5): " << arr.getElement(5) << endl; // 0，且打印错误

    arr.setElement(1, 99);
    arr.print(); // [3, 99]
    arr.setElement(-1, 10); // 越界，打印错误
    arr.print(); // 仍为 [3, 99]
    cout << endl;
}

int main() {
    char* s1 = "hello";
    char* s2 = "world";
 	char* temp = new char[11];
	int sumLength = 11;
	strcpy(temp,s1);
	for(int i=0 ;i<5;i++){
		temp[i+5] = s2[i];
	}
	temp[10]='\0';
	char* s3 = new char[11];
	strcpy(s3,temp);
	cout<<s3;
	delete [] temp;
	delete [] s3;
    return 0;
}
