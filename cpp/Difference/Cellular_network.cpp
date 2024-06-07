#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
#define int long long 
using namespace std;
const int Inf = 1e9 + 9;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, m; // n cities, m cellular towers
vector<int>city, tower;
int delta[MAXN];
inline bool check(int x){
	for(auto pTower : tower){
		//pTower - x < -1e9    pTower + x > 1e9
		int L = (pTower < x - Inf) ? -Inf : pTower - x;
		int R = (pTower > Inf - x) ? Inf : pTower + x;
		int pos1 = lower_bound(city.begin(), city.end(), L) - city.begin();
		if(pos1 == n) continue; 
		int pos2 = upper_bound(city.begin(), city.end(), R) - city.begin();
		delta[pos1]++, delta[pos2]--;
	}
	int cnt = delta[0];
	if(cnt <= 0) return false;
	for(int i = 1; i < n; i++){
		cnt += delta[i];
		if(cnt <= 0) return false; // mid偏小
	}
	return true; // ans
}
signed main(){
	n = read(), m = read();
	city.resize(n), tower.resize(m);
	for(int i = 0; i < n; i++) city[i] = read();
	for(int i = 0; i < m; i++) tower[i] = read();
	int l = 0, r = 1e18, Min;
	while(l <= r){
		int mid = (l + r) >> 1;
		memset(delta, 0, sizeof(delta));
		if(check(mid)){
			Min = mid;
			r = mid - 1;
		}else l = mid + 1;
	}
	cout << Min << endl;
	return 0;
}