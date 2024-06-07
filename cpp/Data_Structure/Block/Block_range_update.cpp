#include <bits/stdc++.h>
#define LL long long

const int Maxn = 5e5 + 1;
const int Maxb = 1e3;

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') f = (ch == '-') ? -1 : 1, ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
    return x * f;
}

inline void write(LL x) {
    if (x < 0) x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int n, m, num[Maxn], belong[Maxn];
class Block {
   private:
    int cnt, Length;
    struct s {
        int L, R, sum, delta;
    } block[Maxb];

   public:
    inline void Init() {
        Length = sqrt(n);
        for (int i = 0; i < n; i += Length)
            block[++cnt].L = i, block[cnt].R = min(i + Length - 1, n - 1);
        for (int i = 1; i <= cnt; i++)
            for (int j = block[i].L; j <= block[i].R; j++)
                belong[j] = i, block[i].sum += num[j];
    }

    inline void Point_update(int x, int val) {
        num[x] += val, block[belong[x]].sum += val;
    }

    inline void Range_update(int x, int y, int val) {
        int l = belong[x], r = belong[y];
        if (l == r && block[l].L == x && block[r].R == y) {
            block[l].delta = val;
            return;
        }
        for (int i = x; i <= block[l].R; i++) Point_update(i, val);
        for (int i = block[r].L; i <= y; i++) Point_update(i, val);
        for (int i = l + 1; i < r; i++) block[i].delta += val;
    }

    inline int get_sum(int x, int y, LL Sum) {
        int l = belong[x], r = belong[y];
        if (l == r) {
            for (int i = x; i <= y; i++) Sum += num[i] + block[l].delta;
            return Sum;
        }
        for (int i = x; i <= block[l].R; i++) Sum += num[i] + block[l].delta;
        for (int i = block[r].L; i <= y; i++) Sum += num[i] + block[r].delta;
        for (int i = l + 1; i < r; i++)
            Sum +=
                block[i].sum + block[i].delta * (block[i].R - block[i].L + 1);
        return Sum;
    }
};

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    n = read(), m = read();
    for (int i = 0; i < n; i++) num[i] = read();
    Block B;
    B.Init();
    while (m--) {
        int type, x, y, val;
        type = read();
        switch (type) {
            case 1:
                x = read(), y = read(), val = read();
                B.Range_update(x - 1, y - 1, val);
                break;
            case 2:
                x = read();
                write(B.get_sum(x - 1, x - 1, 0ll));
                putchar('\n');
                break;
        }
    }
    return 0;
}