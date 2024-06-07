#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/UVA1205
//https://www.luogu.com.cn/blog/user48611/uva1205-color-a-tree
int n, root;
struct N{
    double c, sum;
    int copyC;
    int nxt, last, cnt, fa, vis;
};
vector<N>node;
inline void colorTree(){
    for(int i = 1; i < n; i++){
        int nodeId;
        double mx = 0;
        for(int j = 1; j <= n; j++){
            if(node[j].vis || j == root) continue;
            if(mx < node[j].c) mx = node[j].c, nodeId = j; 
        }
        int f = node[nodeId].fa;
        while(node[f].vis) node[nodeId].fa = f = node[f].fa;
        node[node[f].last].nxt = nodeId;
        node[f].last = node[nodeId].last;
        node[f].sum += node[nodeId].sum;
        node[f].cnt += node[nodeId].cnt;
        node[f].c = node[f].sum / node[f].cnt;
        node[nodeId].vis = true;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += i * node[root].copyC;
        root = node[root].nxt;
    }
    cout << ans << endl;   
}
int main(){
    std::ios::sync_with_stdio(false);
    while(cin >> n >> root && n && root){
        node.clear(), node.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> node[i].c;
            node[i].copyC = node[i].sum = node[i].c;
            node[i].nxt = node[i].last = i;
            node[i].cnt = 1;
        }
        for(int i = 1; i < n; i++){
            int u, v;
            cin >> u >> v;
            node[v].fa = u;
        }
        colorTree();
    }
    return 0;
}
/*method 2
#include<bits/stdc++.h>
typedef long long LL;
const int MAXN = 5e5 + 5;
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, fa[MAXN], Fa[MAXN], siz[MAXN];
LL W[MAXN];
inline int find(int x){
	return Fa[x] == x ? x : Fa[x] = find(Fa[x]);
}
inline void Union(int a, int b){
	int r1 = find(a), r2 = find(b);
	if(r1 != r2) Fa[r1] = r2;
	else puts("-1"), exit(0);
}
struct node{
	int id, sz;
	LL w;
	node(){}
	node(int _id, int _sz, LL _w){
		id = _id, sz = _sz, w = _w;
	}
	inline friend bool operator < (const node &a, const node &b){
		return a.w * b.sz > b.w * a.sz;
	}
};
priority_queue<node, vector<node>>q;
int main(){
	n = read();
	LL sum = 0;
	for(int i = 0; i <= n; i++) Fa[i] = i, siz[i] = 1;
	for(int i = 1; i <= n; i++)	fa[i] = read(), Union(fa[i], i);
	for(int i = 0; i <= n; i++) Fa[i] = i;
	for(int i = 1; i <= n; i++)
		W[i] = read(), q.push(node(i, siz[i], W[i]));
	int u, p;
	while(!q.empty()){
		int u = q.top().id;
		q.pop();
		if(Fa[u] != u) continue;
		Fa[u] = p = find(fa[u]);
		sum += W[u] * siz[p];
		W[p] += W[u], siz[p] += siz[u];
		if(p) q.push(node(p, siz[p], W[p]));
	}
	cout << sum;
	return 0;
}
*/