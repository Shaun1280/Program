#include <bits/stdc++.h>
#define LL long long
using namespace std;
class Disjoint_set
{
private:
    vector<int> Fa, rank /*秩*/;

public:
    //Initialize
    Disjoint_set(int max_size) : Fa(vector<int>(max_size)),
                                 rank(vector<int>(max_size, 0))
    {
        for (int i = 0; i < max_size; i++)
            Fa[i] = i;
    }
    inline int Find(int x)
    {
        return Fa[x] == x ? x : (Fa[x] = Find(Fa[x]));
    }
    inline void Union(int r1, int r2)
    {
        int f1 = Find(r1), f2 = Find(r2);
        if (rank[f1] > rank[f2])
            Fa[f2] = f1;
        else
        {
            Fa[f1] = f2;
            if (rank[f1] == rank[f2])
                rank[f2]++;
        }
    }
};
int main()
{
    std::ios::sync_with_stdio(false);
    int n, p, r1, r2, tot(0);
    cin >> n >> p;
    Disjoint_set D(n);
    LL sum[n], son[n], cnt[n], pair(0);
    memset(sum, 0, sizeof(sum)), memset(son, 0, sizeof(son));
    for (int i = 0; i < p; i++)
        cin >> r1 >> r2, D.Union(r1, r2);
    for (int i = 0, Fa; i < n; i++)
        Fa = D.Find(i), son[Fa]++;
    for (int i = 0; i < n; i++)
        if (son[i])
            cnt[++tot] = son[i], sum[tot] = sum[tot - 1] + cnt[tot];
    for (int i = 1; i < tot; i++)
        pair += cnt[i] * (sum[tot] - sum[i]);
    cout << pair << endl;
    return 0;
}