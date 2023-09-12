#include<bits/stdc++.h>
#define LL long long
using namespace std;
int main(){
    int n;
    LL tmp,Energy(0);
    vector<LL>H;
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0;i<n;i++) cin>>tmp, H.push_back(tmp);
    for(int i=n-1;i>=0;i--) Energy=ceil((H[i]*1.0+Energy*1.0)/2.0);
    cout<<Energy<<endl;
    return 0;
}
/*  Binary Search
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=1e5+5;
ll n,h[maxn],l,r,mid;
inline ll read() {
	char c=getchar();
	ll x=0,f=1;
	while(c<'0'||c>'9') f=(c=='-'? -1:1),c=getchar();
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
inline ll func(int x) {
	ll  e=x;
	for(int i=1; i<=n; i++){
		e=2*e-h[i];
		if(e<0||e>maxn*100000) break;
	}
	return e;
}
int main() {
	n=read();
	for(int i=1; i<=n; i++) h[i]=read();
	l=0,r=maxn;
	while(l!=r) {
		mid=l+r>>1;
		if(func(mid)>=0) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
*/