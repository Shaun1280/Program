#include <bits/stdc++.h>
const int MAXB = 1e3;
using namespace std;
int N, M, *belong = NULL, *seq = NULL;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
class Block {
   private:
    int cnt, Length;
    struct s {
        int L, R, sum[2], Xor;
    } block[MAXB];

   public:
    inline void Init() {
        Length = sqrt(N);
        for (int i = 0; i < N; i += Length)
            block[++cnt].L = i, block[cnt].R = min(i + Length - 1, N - 1);
        for (int i = 1; i <= cnt; i++)
            for (int j = block[i].L; j <= block[i].R; j++)
                belong[j] = i, block[i].sum[seq[j]]++;
    }
    inline void Point_update(int x) {
        block[belong[x]].sum[seq[x]]--;
        seq[x] ^= 1;
        block[belong[x]].sum[seq[x]]++;
    }
    inline void Range_update(int x, int y) {
        int l = belong[x], r = belong[y];
        if (l == r) {
            for (int i = x; i <= y; i++) Point_update(i);
            return;
        }
        for (int i = x; i <= block[l].R; i++) Point_update(i);
        for (int i = block[r].L; i <= y; i++) Point_update(i);
        for (int i = l + 1; i < r; i++) block[i].Xor ^= 1;
    }
    inline int Query(int x, int y, int ans) {
        int l = belong[x], r = belong[y];
        if (l == r) {
            for (int i = x; i <= y; i++)
                if (seq[i] ^ block[l].Xor) ans++;
            return ans;
        }
        for (int i = x; i <= block[l].R; i++)
            if (seq[i] ^ block[l].Xor) ans++;
        for (int i = block[r].L; i <= y; i++)
            if (seq[i] ^ block[r].Xor) ans++;
        for (int i = l + 1; i < r; i++) ans += block[i].sum[1 ^ block[i].Xor];
        return ans;
    }
};
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string s;
    N = read(), M = read();
    cin >> s;
    belong = (int *)malloc((N + 1) * sizeof(int));
    seq = (int *)malloc((N + 1) * sizeof(int));
    for (int i = 0; i < N; i++) seq[i] = s[i] - 48;
    Block B;
    B.Init();
    int type, l, r;
    while (M--) {
        type = read(), l = read(), r = read();
        if (type == 0)
            B.Range_update(l - 1, r - 1);
        else
            printf("%d\n", B.Query(l - 1, r - 1, 0));
    }
    free(belong), free(seq);
    return 0;
}