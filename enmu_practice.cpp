 #include<iostream>
 using namespace std;
 enum class Operation {
 	add,subtract,multiply,divide
 };
 enum Color {
 	blue,red=88,black
 }; 
 int calculate(int a,int b,Operation op){
 	switch(op){
 		case Operation::add:
 			return a+b;
 		case Operation::subtract:
 			return a-b;
		case Operation::multiply:
 			return a*b;
		case Operation::divide:
 			return a/b;	 
		default:
		return 0;	
	 }
 }
 int main(){
 	int x,y;
 	cin>>x>>y;
 	cout<<"x+y="<<calculate(x,y,Operation::add)<<endl;
 	cout<<"x-y="<<calculate(x,y,Operation::subtract)<<endl;
 	cout<<"x*y="<<calculate(x,y,Operation::multiply)<<endl;
 	
 	//Operation op=Operation::divide;
 	//cout<<op<<endl; 这样是错误的 强类型枚举不能隐式转换为整数 
 	
 	Operation op=Operation::divide;
 	cout<<"the value of op is:"<<static_cast<int>(op)<<endl; //强类型枚举显式转换为整数 
 	
 	Color co=black;
 	cout<<"the value of co is:"<<co<<endl;
 	
 	Color co2=Color(2);// 2在color的枚举范围中 
 	cout<<"the value of co is:"<<co2<<endl;
 	return 0;
 }
