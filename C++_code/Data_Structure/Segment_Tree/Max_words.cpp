#include<bits/stdc++.h>
const int MAXN = 5e4 + 1;
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
using namespace std;
struct w{
    string s, lower;
}word[MAXN];
struct Node{
    int l, r, Max; //pos of maximum string
}Tree[MAXN << 2];
inline Node operator + (Node Lson, Node Rson){
    Node tmp;
    tmp.l = Lson.l , tmp.r = Rson.r;
    string s1 = word[Lson.Max].lower;
    string s2 = word[Rson.Max].lower;
    if(s1 < s2) tmp.Max = Rson.Max;
    else if(s1 > s2) tmp.Max = Lson.Max;
    else tmp.Max = max(Lson.Max, Rson.Max);
    return tmp;
}
inline void update(int node){
    Tree[node] = Tree[L(node)] + Tree[R(node)];
}
void build(int Left, int Right, int node){
    if(Left == Right){
        Tree[node].Max = Tree[node].l = Tree[node].r = Left;
        return;
    }
    int mid = (Left + Right) >> 1;
    build(Left, mid, L(node));
    build(mid + 1, Right, R(node));
    update(node);
}
inline Node ask_max(int Left, int Right, int node){
    if(Tree[node].l == Left && Tree[node].r == Right){
        return Tree[node];
    }
    int mid = Tree[node].l + Tree[node].r >> 1;
    if(Right <= mid) return ask_max(Left, Right, L(node));
    else if(Left > mid) return ask_max(Left, Right, R(node));
    else return ask_max(Left, mid, L(node)) + ask_max(mid + 1, Right, R(node));
}
int main(){
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> word[i].s, word[i].lower = word[i].s;
        transform(word[i].lower.begin(), word[i].lower.end(), word[i].lower.begin(), ::tolower);
    }
    build(1, n, 1); 
    while(m--){
        int x, y;
        cin >> x >> y;
        cout << word[ask_max(x, y, 1).Max].s << endl;
    }
    return 0;
}