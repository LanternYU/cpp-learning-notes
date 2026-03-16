#include<iostream>
#include<vector>
#include<array>
int main(){
	using namespace std;
	double a[4] ={1,2,3,4};
	vector<double> b = {5,6,7,8};
	array<double,4> c ={9,10,11,12};
	array<double,4> d;
	d=c;
	cout<<"a[2]: "<<a[2]<<" at "<<&a[2]<<endl;
	cout<<"b[2]: "<<b[2]<<" at "<<&b[2]<<endl;
	cout<<"c[2]: "<<c[2]<<" at "<<&c[2]<<endl;
	cout<<"d[2]: "<<d[2]<<" at "<<&d[2]<<endl;
	int aa=0,bb=0;
	while(aa++<10){
		cout<<"aa ";
	}
	cout<<"\n";
	while(++bb<10);
	}
	return 0;
}
