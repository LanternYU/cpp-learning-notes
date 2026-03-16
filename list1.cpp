#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
    int less(vector<int>::iterator it1,vector<int>::iterator it2){
        return (*it1)>(*it2) ? (*it2):(*it1);
    }

    
    int maxArea(vector<int>& height) {
        vector<int>::iterator begin=height.begin();
        vector<int>::iterator end=height.end() - 1;
        int length = height.size() - 1;
        int max = (less(begin,end))*length;
        while(begin!=end){
        	
            if(max< (less(begin+1,end))*(length -1) ){
                begin++;
                length--;
                max = (less(begin,end))*length;
            }
            else if(max< (less(begin,end-1))*(length -1)){
                end--;
                length--;
                max = (less(begin,end))*length;
            }
            else{
                break;
            }
        }
        return max;
    }


};

int main()
{
	vector<int> arr = {1,8,6,2,5,4,8,3,7};
	Solution s;
    cout<< s.maxArea(arr) <<endl;
	return 0;
} 
