#include <bits/stdc++.h>
#define LL long long

const int MAXN = 1e5 + 5;

using namespace std;

int n, m;
int fa[MAXN << 1];
LL sz[MAXN << 1], sum[MAXN << 1];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n << 1; i++)
        fa[i] = (i <= n ? i + n : i), sz[i] = 1, sum[i] = (i > n ? i - n : i);
    while (m--) {
        int type, a, b, r1, r2;
        cin >> type;
        switch (type) {
            case 1:
                cin >> a >> b;
                r1 = find(a), r2 = find(b);
                if (r1 != r2) fa[r1] = r2, sz[r2] += sz[r1], sum[r2] += sum[r1];
                break;
            case 2:
                cin >> a >> b;
                r1 = find(a), r2 = find(b);
                if (r1 != r2)
                    fa[a] = r2, sz[r2]++, sz[r1]--, sum[r2] += a, sum[r1] -= a;
                break;
            case 3:
                cin >> a;
                r1 = find(a);
                cout << sz[r1] << " " << sum[r1] << endl;
                break;
        }
    }
    return 0;
}