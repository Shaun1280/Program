#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4168
//https://www.luogu.com.cn/blog/user48611/p4168-violet-pu-gong-ying
//P4168 [Violet]蒲公英
constexpr int MAXN = 4e4 + 4;
constexpr int MAXT = 36;
using namespace std;
int n, m, x, arr[MAXN], brr[MAXN], belong[MAXN], cntSmall[MAXN];
int cnt[MAXT][MAXT][MAXN], mode[MAXT][MAXT], maxC[MAXT][MAXT], Len;//5e7
unordered_map<int, int>Map;
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
	for (int L = 0; L < vec.size(); L++)
		for (int R = L; R < vec.size(); R++) {
			for (int i = vec[L].l, tmp; i <= vec[R].r; i++) {
				tmp = ++cnt[L][R][arr[i]];
				if (tmp > maxC[L][R] || (tmp == maxC[L][R] && arr[i] < mode[L][R])) 
					maxC[L][R] = tmp, mode[L][R] = arr[i];
                    //get mode and its cnt between block L and block R
			}
		}		
}
inline void compare(int tmp, int & maxCnt, int val) {
	if (tmp > maxCnt || (tmp == maxCnt && val < x)) maxCnt = tmp, x = val;
}
inline void query(int l, int r, int maxCnt) {
	int L = belong[l], R = belong[r];
	if (L == R) {
		for (int i = l, tmp; i <= r; i++) 
			compare(++cntSmall[arr[i]], maxCnt, arr[i]);
		for (int i = l; i <= r; i++) cntSmall[arr[i]]--;//back trace
		return;
	}
	L++, R--, maxCnt = maxC[L][R], x = mode[L][R]; //mode of contiguous L~R blocks
	for (int i = l, tmp; i < vec[L].l; i++) //arr in [l, Block[L].l - 1]
		compare(++cnt[L][R][arr[i]], maxCnt, arr[i]);
	for (int i = vec[R].r + 1, tmp; i <= r; i++) //arr in [Block[R].r, r]
		compare(++cnt[L][R][arr[i]], maxCnt, arr[i]);
	for (int i = l, tmp; i < vec[L].l; i++) cnt[L][R][arr[i]]--; //back trace
	for (int i = vec[R].r + 1, tmp; i <= r; i++) cnt[L][R][arr[i]]--; //back trace
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i], brr[i] = arr[i];//cpy of arr, will be used to discrete
	discretizaton();
	for (int i = 0; i < n; i++) arr[i] = Map[arr[i]]; //change arr into discreted value
	Len = (ceil)(n / pow(n, 1.0 / 3)), Init(); //get block length and init blocks
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