#include<bits/stdc++.h>
using namespace std;
int n;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x*f;
}
class candle{
	public:
		vector<int>height;
	    void sort_height(){
			sort(height.begin(),height.end());
	    }
		void input_n(){
			n=read();
		}
		void input_h(){
			for(int i=1;i<=n;i++){
				int h=read();
				height.push_back(h);
			} 
		}
		int count(){
			int maxh=height[n-1],tot=0;
			for(int i=n-1;i>=0&&height[i]==maxh;i--) tot++;
			return tot;
		}	
};
int main(){
	candle c;
	c.input_n();
	c.input_h();
	c.sort_height();
	cout<<c.count();
	return 0;
} 
