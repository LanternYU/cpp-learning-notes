#include<iostream>
using namespace std;
int main(){
	int a=10;
	int *p;
	p=&a;
	(*p)++;
	cout<<p<<endl;
	cout<<*p<<endl;
}
