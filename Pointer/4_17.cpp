#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector<int> a;
	vector<int> b={1,2,3,4,5};
	a=b;
	cout<<"Address of a is: "<<&a<<endl;
	cout<<"Address of b is: "<<&b<<endl;
	
	vector<vector<int>> c ={{5,4},{2,4}};
	vector<vector<int>> d ={{88},{99},{27}};
	cout<<"size1: "<<d.size()<<" size2: "<<d[0].size()<<endl;
	d=c;
	cout<<"size1: "<<d.size()<<" size2: "<<d[0].size()<<endl;
	cout<<"Address of c is:"<<&c<<endl;
	cout<<"Address of c is:"<<&c[0]<<endl;
	cout<<"Address of c is:"<<&c[0][0]<<endl;

	cout<<"Address of d is:"<<&d<<endl;
	cout<<"Address of d is:"<<&d[0]<<endl;
	cout<<"Address of d is:"<<&d[0][0]<<endl;
	return 0;
}
