#include<bits/stdc++.h>
//point add &&[l,r]sum  not a tree: An array;
//https://www.youtube.com/watch?v=v_wj_mOAlig&t=1s
//https://blog.csdn.net/Yaokai_AssultMaster/article/details/79492190
const int MAXN=1e6+6;
using namespace std;
int n,m;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48, ch=getchar();
	return x*f;
}
class Binary_Indexed_tree{
	private:
		int BIT[MAXN], x; //maxn <5e5+5
	public:
		inline void Init(){
			memset(BIT,0,sizeof(BIT));
		}
		inline int lowbit(int x){
			return x&(-x);
		}
		inline void add(int x, int val){
			while(x<=n) BIT[x]+=val, x+=lowbit(x);//update->father
		}
		inline int get_sum(int x,int sum){
			while(x>0) sum+=BIT[x], x-=lowbit(x);//13 12 8
			return sum;
		}  
};
int main(){
	freopen("test.in","r", stdin);
	freopen("test.out","w",stdout);
	n=read(), m=read();
	Binary_Indexed_tree B;
	for(int i=1,tmp; i<=n; i++) tmp=read(), B.add(i, tmp);
	while(m--){
		int type, l, r, x, val;
		cin>>type;
		switch (type)
		{
			case 1:
				x=read(), val=read();
				B.add(x,val);
				continue;
			case 2:
				l=read(), r=read();
				cout<<B.get_sum(r,0)-B.get_sum(l-1,0)<<endl;
				continue;
		}
	}
	return 0;
}