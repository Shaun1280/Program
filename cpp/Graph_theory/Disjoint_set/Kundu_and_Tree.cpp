#include<bits/stdc++.h>
#define LL long long
#define M 1000000007
/*
https://math.stackexchange.com/questions/838792/counting-triplets-with-red-edges-in-each-pair?newreg=60eee35f0b3844de852bda39f6dfec88
*/
using namespace std;
int N, *Fa = NULL, *Size = NULL, *vis = NULL;
inline void Init(){
    Fa = (int *)malloc((N + 1) * sizeof(int));
    Size = (int *)malloc((N + 1) * sizeof(int));
    vis = (int *)malloc((N + 1) * sizeof(int));
    for(int i = 0; i <= N; i++) 
        Fa[i] = i, vis[i] = 0, Size[i] = 1; 
}
/*******Disjoint_set**************/
inline int find(int x){
    return Fa[x] == x? x : Fa[x] = find(Fa[x]);
}
inline void Union(int a, int b){
    int r1 = find(a), r2 = find(b);
    if(r1 != r2) 
        Fa[r1] = r2, Size[r2] += Size[r1]; //get size of black trees
}
/*******************************/
vector<int>black_tree;
inline void Get_black_tree(){
    for(int i = 1; i <= N; i++){
        int root = find(i);
        if(Size[root] == 1) continue; //a vectex in red tree continue
        if(!vis[root]) black_tree.push_back(Size[root]);
        vis[root] = true;
    }
}
inline void get_cnt(){
    LL total = 1LL* N * (N - 1) * (N-2) / 6;
    LL cnt_black_triplets = 0LL;
    for(int i = 0; i < black_tree.size(); i++){
        int val = black_tree[i];
        cnt_black_triplets += 1LL * val * (val - 1) * (val - 2) / 6;
        cnt_black_triplets += 1LL * val * (val - 1) / 2 * (N - val);
    }//mathematics 
    cout<< (total - cnt_black_triplets) % M;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> N;
    Init();
    int node1, node2;
    char color;
    for (int i = 0; i < N - 1; i++){
        cin >> node1 >> node2 >> color;
        if(color == 'b' && find(node1) != find(node2) ) 
            Union(node1, node2);
    }
    Get_black_tree();
    get_cnt();
    return 0;
}
/* 0(N^3->k*N)
  B[n-1] = count1[n];
    for(i=n-2;i>=0;i--) B[i] = (B[i+1] + count1[i+1])%MOD;
    for(i=1;i<n-1;i++) C[i] = (count1[i+1]*B[i+1])%MOD;

    D[n-2] = C[n-2];
    for(i=n-3;i>=1;i--) D[i] = (D[i+1] + C[i])%MOD;

    for(i=0;i<n-2;i++) sum = (sum + count1[i+1]*D[i+1])%MOD;
*/