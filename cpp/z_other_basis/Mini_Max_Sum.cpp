#include<bits/stdc++.h>
#define LL long long 
using namespace std;
class Line{
	public:
		vector<LL>vec;
		LL max_sum,min_sum;
		void read_input(){
			for(int i=1;i<=5;i++){
				LL num;
				cin>>num;
				vec.push_back(num);
			}
			sort(vec.begin(),vec.end());
		} 
		LL get_max(){
			LL max_sum=vec[1]+ vec[2]+ vec[3]+ vec[4];
			return max_sum;
		}
		LL get_min(){
			LL min_sum=vec[0]+ vec[1]+ vec[2]+ vec[3];
			return min_sum; 
		}
};
int main(){
	Line l;
	l.read_input();
	cout<<l.get_min()<<" "<<l.get_max()<<endl;
	return 0;
}
