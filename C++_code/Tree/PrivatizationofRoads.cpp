#include<bits/stdc++.h>
using namespace std;
//CF1141G Privatization of Roads in Treeland
//It is easy to show that D colors is always enough 
//to paint a tree in such a way that all the vertices are proper, 
//where D is the maximum vertex degree. 
//Actually, it is always the truth do any bipartite graph.
/*
Indeed, if number of colors is less than the maximum degree, 
such vertices will have at least two edges of the same color 
(Dirichlet's principle)
*/
int n, k, r;
vector< vector<pair<int/*u*/, int/*i*/>> >G; 
// storage the ith Edge from u
vector<int>degree, E;
inline void dfs(int cur, int fa, int color){
    for(auto e : G[cur]){
        if(e.first != fa){
            E[e.second] = color;
            color = (color + 1) % r;   
            dfs(e.first, cur, color);
        }
    }
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> k;
    G.resize(n), degree.resize(n), E.resize(n);
    int u, v;
    for(int i = 0; i < n- 1; i++){
        cin >> u >> v;
        degree[--u]++, degree[--v]++;
        G[u].push_back({v, i});
        G[v].push_back({u, i});
    }
    sort(degree.begin(), degree.end()); // greedy
    r = degree[n - k - 1]; 
    cout << r <<endl;
    dfs(0, 0, 0);
    for(int i = 0; i < E.size() - 1; i++)
        cout << E[i] + 1 << " ";
    return 0;
}