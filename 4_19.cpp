#include<iostream>
int main(){
	using namespace std;
	double wage[3] = {10000,20000,30000};
	short stack[3] = {3,2,1};
	
	double* pw =wage;
	short* ps = &stack[0];
	
	cout<<"pw = "<<pw<<" *pw = "<< *pw<<endl;
	pw++; 
	cout<<"pw = "<<pw<<" *pw = "<< *pw<<endl;
	cout<<"ps = "<<ps<<" *ps = "<< *ps<<endl;
	ps++;
	cout<<"ps = "<<ps<<" *ps = "<< *ps<<endl;
	
	cout<<"size of wage is:"<<sizeof(wage)<<endl;
	cout<<"size of pw is:"<<sizeof(pw)<<endl;
	return 0;
}

