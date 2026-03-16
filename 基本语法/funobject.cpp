#include<iostream>
int main()
{
	using namespace std;
	int x=5,y=6;
	auto add_sum = [](int a,int b)->int {return a+b;};
	cout<<add_sum(x,y)<<endl;
	auto add_sum1 = [&](int a)->int {return a+x;};
	auto add_sum2 = [=](int a)->int {return a+y;};
	x=3;
	y=4;
	cout<<add_sum1(3)<<endl;
	cout<<add_sum2(3)<<endl;
}
