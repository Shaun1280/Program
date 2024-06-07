#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/p4168-violet-pu-gong-ying
constexpr int MAXN = 4e4 + 4;
constexpr int MAXT = 800;
using namespace std;
int n, m, x, arr[MAXN], brr[MAXN], belong[MAXN], cntSmall[MAXN];
int mode[MAXT][MAXT], maxC[MAXT][MAXT], Len;//5e7
unordered_map<int, int>Map;
vector<int>P[MAXN];
struct block { 
	int l, r;
	block(){}
	block(int _l , int _r) : l(_l), r(_r){}
};
vector<block>vec;
inline void discretizaton() {
	sort(brr, brr + n);
	int tot = unique(brr, brr + n) - brr;
	for (int i = 0; i < tot; i++) Map[brr[i]] = i;
}
inline void Init() {
	for (int i = 0; i < n; i += Len)	
		vec.push_back(block(i, min(i + Len - 1, n - 1)));
	for (int i = 0; i < vec.size(); i++)
	 	for (int j = vec[i].l; j <= vec[i].r; j++) belong[j] = i;	
	for (int L = 0; L < vec.size(); L++) {
		int val = 0, cnt = 0;
		for (int i = vec[L].l; i < n; i++) {
			int tmp = ++cntSmall[arr[i]], R = belong[i];
			if (tmp > cnt || (tmp == cnt && arr[i] < val))
				cnt = tmp, val = arr[i];
			maxC[L][R] = cnt, mode[L][R] = val;
		}
		for (int i = vec[L].l; i < n; i++) --cntSmall[arr[i]];
	}
}
inline int getCnt(int val, int l, int r) {
	return upper_bound(P[val].begin(), P[val].end(), r) - lower_bound(P[val].begin(), P[val].end(), l);
}
inline void compare(int cnt, int & maxCnt, int val) {
	if (cnt > maxCnt || (cnt == maxCnt && val < x)) maxCnt = cnt, x = val;
}
inline void query(int l, int r, int maxCnt) {
	int L = belong[l], R = belong[r];
	if (L == R) {
		for (int i = l; i <= r; i++) 
			compare(getCnt(arr[i], l, r), maxCnt, arr[i]);
		return;
	}
	L++, R--, maxCnt = maxC[L][R], x = mode[L][R];
	for (int i = l; i < vec[L].l; i++) compare(getCnt(arr[i], l, r), maxCnt, arr[i]);
	for (int i = vec[R].r + 1; i <= r; i++) compare(getCnt(arr[i], l, r), maxCnt, arr[i]);
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i], brr[i] = arr[i];
	discretizaton();
	for (int i = 0; i < n; i++) arr[i] = Map[arr[i]], P[arr[i]].push_back(i);
	Len = 1.0 * n / sqrt(log(n) / log(2) * n), Init();
	while (m--) {
		int l, r;
		cin >> l >> r;
		l = (l + x - 1) % n, r = (r + x - 1) % n;
		if (l > r) swap(l, r);
		query(l, r, 0);
		cout << (x = brr[x]) << endl;
	}
	return 0;
}