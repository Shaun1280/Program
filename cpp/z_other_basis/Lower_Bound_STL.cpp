#include<bits/stdc++.h>
const int maximum=1e5+5;
using namespace std;
int n, integers[maximum],Qnumber; 
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x*f;
}
int main(){
	n=read();
	for(int i=0;i<n;i++) integers[i]=read();
	Qnumber=read();
	for(int i=1;i<=Qnumber;i++){
		int num, position;
		num=read();
		position=lower_bound(integers,integers+n-1,num)-integers;
		if(integers[position]==num) printf("Yes %d\n",position+1);
		else printf("No %d\n",position+1);
	}
	return 0;
} 
