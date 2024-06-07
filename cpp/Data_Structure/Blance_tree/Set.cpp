#include<bits/stdc++.h>
using namespace std;
struct node{
	int w, c;
	inline friend bool operator < (const node &a, const node &b){
		return a.c < b.c;
	}
};
set<node>s;
node tmp;
int main(){
	//freopen("test.in", "r", stdin);
	int type;
	while(scanf("%d", &type) && ~type){
		int w, c;
		switch (type)
		{
		case 1:
			scanf("%d%d", &tmp.w, &tmp.c);
			s.insert(tmp);
			break;
		case 2:
			if(s.size()) s.erase(--s.end());//删除尾部元素 不能end()--
			break;
		case 3:
			if(s.size()) s.erase(s.begin());
			break;
		}
	}
	long long sumW = 0, sumC = 0;
	set<node>::iterator it;
	for(it = s.begin(); it != s.end(); it++)
		sumW += (*it).w, sumC += (*it).c;
	cout << sumW << " " << sumC << endl;
	return 0;
}