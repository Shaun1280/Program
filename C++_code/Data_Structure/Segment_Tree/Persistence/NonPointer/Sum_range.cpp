#include <bits/stdc++.h>
// 美味佳肴，区间内的数不能相加得到的最小数
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7, INF = 1e9 + 9;

struct SegTree {
    int lson, rson, sum;
} tree[MAXN * 64];

int& Lson(int root) { return tree[root].lson; }
int& Rson(int root) { return tree[root].rson; }
int newNode(int& root) { static int tot; return root = ++tot; }

void modify(int pre, int root, int L, int R, int pos) {
    tree[root] = tree[pre];
    if (L == pos && R == pos) {
        tree[root].sum += pos; // 在 pos 处插入，总和加上 pos
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) modify(Lson(pre), newNode(Lson(root)), L, mid, pos);
    else modify(Rson(pre), newNode(Rson(root)), mid + 1, R, pos);
    tree[root].sum = tree[Lson(root)].sum + tree[Rson(root)].sum;
}

int qSum(int pre, int root, int L, int R, int qL, int qR) { // 求值域 qL <= x <= qR 的 x 的和
    if (qL <= L && R <= qR) return tree[root].sum - tree[pre].sum;
    int mid = (L + R) >> 1, res = 0;
    if (qL <= mid) res += qSum(Lson(pre), Lson(root), L, mid, qL, qR);
    if (qR > mid) res += qSum(Rson(pre), Rson(root), mid + 1, R, qL, qR);
    return res;
}

int root[MAXN], n, m;

int main() {
    boost;
    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
        cin >> tmp;
        modify(root[i - 1], newNode(root[i]), 0, 1e9, tmp);
    }
    cin >> m;
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        int x = 1;
        while (true) {
            int sum = qSum(root[l - 1], root[r], 0, 1e9, 0, x); // 查询 <= x 的数的和
            if (sum < x) break;
            x = sum + 1;
        }
        cout << x << "\n";
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */