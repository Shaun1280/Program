#include<bits/stdc++.h>
using namespace std;
struct A{
	int val,pos;
	bool operator <(const A &a) const{return pos<a.pos;}
};
bool cmp(const A &v1, const A &v2){return v1.pos<v2.pos;}
int N,K,Q,X;
vector<A> vec;
int main(){
	A temp;
	std::ios::sync_with_stdio(false);
	cin>>N>>K>>Q;
	for(int i=0;i<N;i++) cin>>temp.val, temp.pos=i,vec.push_back(temp);
	for(int i=0;i<N;i++) vec[i].pos+=K,vec[i].pos=vec[i].pos%N; //(vec[i].pos%N==0)? N:vec[i].pos%N;
	sort(vec.begin(),vec.end(),cmp);
	while(Q--){
		cin>>X;
		temp.pos=X;
		int position=lower_bound(vec.begin(),vec.end(),temp)-vec.begin();
		cout<<vec[position].val<<endl;
	}
	return 0;
}