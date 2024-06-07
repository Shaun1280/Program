#include <bits/stdc++.h>
// 2dkmp + 循环节 + dual hash
#define debug(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

#define pll pair<unsigned long long, unsigned long long>

const int MAXN = 2E3 + 5;
const int MOD = 1E9 + 7;
const int P1 = 1331;
const int P2 = 113;
int n, m, T;
char c[MAXN][MAXN];
pll hr[MAXN][MAXN], hc[MAXN][MAXN], p[MAXN], tmp[MAXN];
int nxt[MAXN];

void Hash() {
    p[0].first = p[0].second = 1;
    for (int i = 1; i <= n; i++) {
        p[i].first = p[i - 1].first * P1;
        p[i].second = p[i - 1].second * P2;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            hr[i][j].first = hr[i][j - 1].first * P1 + c[i][j];
            hr[i][j].second = hr[i][j - 1].second * P2 + c[i][j];
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            hc[i][j].first = hc[i][j - 1].first * P1 + c[j][i];
            hc[i][j].second = hc[i][j - 1].second * P2 + c[j][i];
        }
}

pll getHash(pll* h, int l, int r) {
    return {h[r].first - h[l - 1].first * p[r - l + 1].first,
            h[r].second - h[l - 1].second * p[r - l + 1].second};
}

int calc(int n) {
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && tmp[i] != tmp[j + 1]) j = nxt[j];
        if (tmp[i] == tmp[j + 1]) j++;
        nxt[i] = j;
    }
    return n - nxt[n];
}

signed main() {
    // freopen("1.in", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    cin.ignore();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> c[i][j], c[i][j] = c[i][j] - 'a' + 1;
    Hash();
    for (int i = 1, x, y, x2, y2; i <= m; i++) {
        cin >> x >> y >> x2 >> y2;
        int ans = 1;
        for (int j = 1; j <= y2 - y + 1; j++)
            tmp[j] = getHash(hc[j + y - 1], x, x2);
        ans *= calc(y2 - y + 1);

        for (int j = 1; j <= x2 - x + 1; j++)
            tmp[j] = getHash(hr[j + x - 1], y, y2);
        ans *= calc(x2 - x + 1);
        
        cout << ans << endl;
    }
    return 0;
}