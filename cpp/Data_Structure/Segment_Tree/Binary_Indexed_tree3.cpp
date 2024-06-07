#include<bits/stdc++.h>
//[l,r] add  && [l,r] sum
//https://www.cnblogs.com/bluefly-hrbust/p/10416808.html
#define LL long long
const int MAXN=5e5+5;
using namespace std;
int n, m;
LL tmp;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-48, ch=getchar();
	return x*f;
}
LL BIT[MAXN], BITc[MAXN];
class Binary_Indexed_tree{
	public:
		inline void Init(){ 
			memset(BIT,0,sizeof(BIT)); 
			memset(BITc,0,sizeof(BITc));
		}
		inline int lowbit(int x){ return x&(-x); }
		inline void add(int x, LL val){
			int Index=x;
			while(x<=n) 
				BIT[x]+=val, BITc[x]+=val*(Index-1), x+=lowbit(x);//维护前缀和c[i]*(n-1)
		}
		inline LL get_sum(int x,LL sum){
			int Index=x;
			while(x>0) sum+=Index*BIT[x]-BITc[x], x-=lowbit(x);//13 12 8
			return sum;
		}  
};
int main(){
	freopen("test.in","r", stdin);
	freopen("test.out","w",stdout);
	n=read(), m=read();
	Binary_Indexed_tree B;
	B.Init();
	for(int i=1; i<=n; i++) 
		scanf("%lld", &tmp), B.add(i, tmp), B.add(i+1, -tmp);
	while(m--){
		int type, l, r;
		LL val;
		type=read();
		switch (type)
		{
			case 1:
				l=read(), r=read(), scanf("%lld", &val);
				B.add(l, val);
				B.add(r+1, -val);
				continue;
			case 2:
				l=read(), r=read();
				cout<<B.get_sum(r,0ll)-B.get_sum(l-1,0ll)<<endl;
				continue;
		}
	}
	return 0;
}