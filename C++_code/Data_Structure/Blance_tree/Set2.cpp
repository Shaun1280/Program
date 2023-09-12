#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1503
//P1503 鬼子进村
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
set<int>s;
stack<int>Stack;
int n, m;
int main(){
	n = read(), m = read();
	s.insert(0), s.insert(n + 1);
	while(m--){
		char type;
		cin >> type;
		if(type == 'D'){
			int x = read();	
			s.insert(x);
			Stack.push(x);
		}
		if(type == 'R'){
			int x = Stack.top();
			Stack.pop();
			s.erase(s.find(x));
		}
		if(type == 'Q'){
			int x = read();
			set<int>::iterator it;
			it = s.lower_bound(x);
			if(*it == x){
				puts("0");
				continue;
			}
			int r = *it, l = *(--it);
			printf("%d\n", r - l - 1);
		}
	}
	return 0;
}