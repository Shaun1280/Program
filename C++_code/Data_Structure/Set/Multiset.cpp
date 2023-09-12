#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
//CF6E Exposition
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, k;
array<int, MAXN>h;
vector< pair<int, int> >vec;
multiset<int>s; //有序 可重复
int main() {
	n = read(), k = read();
	int l = 0, ans = 0;
	for (int r = 0;  r < n; r++) {
		h[r] = read();
		s.insert(h[r]);
		while (*s.crbegin() - *s.cbegin() > k) { //区间最大值为*s.crbegin() const 最小值s.cbegin()
			s.erase(s.find(h[l])); //删除区间左端点对应元素
			l++;
		}
		if (r - l + 1 > ans) {
			vec.clear(); //有更大的区间长度vec清空
			ans = r - l + 1;
			vec.push_back({l + 1, r + 1});
		} else if (r - l + 1 == ans) { //相同的区间长度  继续插入
			vec.push_back({l + 1, r + 1});
		}
	}
	cout << ans << " " << vec.size() << endl;
	for (const auto & i : vec) {
		cout << i.first << " " << i.second << endl;
	}
	return 0;
}