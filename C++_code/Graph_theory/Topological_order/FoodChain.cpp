#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
//https://www.luogu.com.cn/problem/P3183
//topologicalsort and dp
using namespace std;
int in[MAXN], out[MAXN], n, m, f[MAXN];
vector<vector<int>>E;
inline void topoOrder(){
	int ans(0);
	queue<int>q;
	vector<int>topo;
	for(int i = 1; i <= n; i++)
		if(in[i] == 0 && E[i].size()) q.push(i), f[i] = 1;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		if(!E[cur].size()) ans += f[cur];
		for(auto to : E[cur]){
			f[to] += f[cur];
			if(!(--in[to])) q.push(to);	
		}	
	}
	cout << ans << endl;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin >> n >> m;
	E.resize(n + 1);
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		E[u].push_back(v);
		in[v]++;
		out[u]++;
	}
	topoOrder();
	return 0;
}