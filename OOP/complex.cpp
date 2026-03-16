#include<iostream>
class Iweapon{
	public:
		Iweapon(){std::cout<<"Iweapon 的构造函数"<<std::endl;}
		~Iweapon(){std::cout<<"Iweapon 的析构函数"<<std::endl;}
		void shoot(){std::cout<<"射击"<<std::endl;};
};
class character{
	public:
		character(){std::cout<<"character 的构造函数"<<std::endl;}
		~character(){std::cout<<"character 的析构函数"<<std::endl;}
	private:
	 
}; 
class Auther:public character{
	public:
		Auther(){std::cout<<"Auther 的构造函数"<<std::endl;}
		~Auther(){std::cout<<"Auther 的析构函数"<<std::endl;}
		void shoot(){weapon.shoot();};
	private:
		Iweapon weapon;
};
int main(){
	Auther auther;
	auther.shoot();
	return 0;
}
