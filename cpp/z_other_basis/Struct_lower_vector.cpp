#include<bits/stdc++.h>
using namespace std;
/*
note:: operator <(const strutc_name &A) const
	   lower_bound:first >=
	   upper_bound:fisrt >
 */
const int maxn=2e5+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();return x*f;}
int n,m;
struct ss{
	int val,rank;
	bool operator < (const ss &s) const{
		return s.val > val;
	}
};
vector<ss>scores;
bool cmp(const ss &A, const ss &B){return A.val<B.val;}
void get_rank(vector<ss> &A){
	int size=A.size(), R(1);
	A[0].rank=1;
	for(int i=1;i<size;i++){if(A[i].val<A[i-1].val) R++;A[i].rank=R;}
}
int main(){
	std::ios::sync_with_stdio(false);
	n=read();
	ss S,Alice;
	for(int i=0;i<n;i++) S.val=read(), S.rank=0, scores.push_back(S);
	get_rank(scores);
	sort(scores.begin(),scores.end(),cmp);
	m=read();
	while(m--){
		Alice.val=read();
		int position=lower_bound(scores.begin(),scores.end(),Alice)-scores.begin();
		if(Alice.val==scores[position].val) cout<<scores[position].rank<<endl;
		else cout<<scores[position].rank+1<<endl;
	}
	return 0;
}