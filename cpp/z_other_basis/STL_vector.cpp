/*Declaration: vector<int>v; (creates an empty vector of integers)

Size: int size=v.size();

Pushing an integer into a vector:
v.push_back(x);(where x is an integer.The size increases by 1 after this.)

Popping the last element from the vector:
v.pop_back(); (After this the size decreases by 1)

Sorting a vector:
sort(v.begin(),v.end()); (Will sort all the elements in the vector)
*/
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define LL long long
LL N,vi;
vector<LL>v;
inline LL read(){
	LL x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x*f;
}
int main() {
    N=read();
    for(int i=0;i<N;i++){
    	LL x=read();
    	v.push_back(x);	
	}
	sort(v.begin(),v.end());
	for(int i=0;i<N;i++){
		printf("%ld ",v[i]);
	}
    return 0;
}
