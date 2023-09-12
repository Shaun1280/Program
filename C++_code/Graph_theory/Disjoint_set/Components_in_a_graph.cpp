#include<bits/stdc++.h>
using namespace std;
// print the number of vertices in the smallest 
//and the largest connected components of the graph
int *Fa = NULL, *Size = NULL, max_size=0, min_size=0x7fffffff;
inline int find(int x){
    return Fa[x] == x? x:Fa[x]=find(Fa[x]);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int N;
    std::ios::sync_with_stdio(false);
    cin >> N;
    Fa = (int *)malloc((2 * N + 1) * sizeof(int));
    Size = (int *)malloc((2 * N + 1) * sizeof(int));
    for(int i=1 ; i<= 2 * N; i++) Fa[i] = i, Size[i] =1;
    for(int i=0, g, b; i< N; i++){
        cin >> g >> b;
        int r1 = find(g), r2 = find(b);
        if(r1 != r2) {
            Fa[r1] = r2;
            Size[r2] += Size[r1];
        }
    }
    for(int i=1 ; i<= 2 * N; i++)
        if(Size[find(i)]>1) //！！！
            max_size = max(max_size, Size[find(i)]), 
            min_size = max(2, min(min_size, Size[find(i)]));
    cout<< min_size << " " << max_size <<endl;
    free(Fa), free(Size);
    return 0;
}