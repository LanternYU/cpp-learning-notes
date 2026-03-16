#include<iostream>
#include<vector>
using namespace std;
int maxProfit(vector<int>& prices){
        int p = 0;
        int q = prices.size()-1;
        int profit = 0;
        while(p<q){
           while(prices[p]>prices[p+1]&&p<q){
                p++;
           }
           while(prices[q]<prices[q-1]&&p<q){
                q--;
           }
           cout<<"p: "<<p<<" q:"<<q<<endl;
           profit=max(prices[q]-prices[p],profit);
           cout<<prices[q]-prices[p]<<endl;
           p++;
           q--;
           if(p>=q) break;
        }
        return profit;
    }
int main(){
	vector<int> vec = {7,1,5,3,6,4};
	int sum = maxProfit(vec);
	cout<<sum<<endl;
	return 0;
} 
