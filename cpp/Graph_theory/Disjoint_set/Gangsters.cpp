#include <cstdio>
//[BOI2003]Gangsters
const int maxn = 1e3+10;
//friend of my friend is also my friend.
//An enemy of my enemy is my friend.
//input is consistent :two gangsters cannot be 
//both friends and enemies of each other.
int n, m;
int fa[maxn], enemy[maxn], ssc = 0;

void Init() {
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    ssc = n;
}

int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Union(int x, int y) {
    if (Find(x) != Find(y)) {
        ssc--;
        fa[Find(x)] = Find(y);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    Init();
    while (m--) {
        char o[10];
        int x, y;
        scanf("%s%d%d", o, &x, &y);
        if (o[0] == 'F')
            Union(x, y);
        else {
            //int fx = Find(x), fy = Find(y);
            if(enemy[y])
                Union(x, enemy[y]);
            else 
                enemy[y] = x;
            if (enemy[x])
                Union(y, enemy[x]);
            else
                enemy[x] = y;
        }
    }
    printf("%d", ssc);
    return 0;

/*#include <bits/stdc++.h>
using namespace std;
int ans, n, m, p, q, Fa[2001];
char c;
int find(int x){
    if (Fa[x] != x) Fa[x] = find(Fa[x]);
    return Fa[x];
}
void Union(int a, int b){
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) Fa[r2] = r1;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= 2 * n; i++)Fa[i] = i;
    for (int i = 1; i <= m; i++){
        cin >> c >> p >> q;
        if (c == 'F') Union(p, q);
        if (c == 'E')
            Union(q, p + n), Union(p, q + n);
    //敌人的所有敌人是朋友
    //p+n表示敌人
    //a,b是敌人，则合并b和a+n,a和b+n
    //a,c是敌人 ，合并a和c+n，c和a+n
    //这样就可以把a和c合并在一个集合，实现敌人的敌人是朋友 
    }
    for (int i = 1; i <= n; i++)
        if (Fa[i] == i)
            ans++;
    cout << ans;
}*/