#include <bits/stdc++.h>
//#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int tc, n, q;
array<int, MAXN> l, r, a;
string s, f;

struct SegTree {
    SegTree *lson, *rson;
    int sum, l, r;
    int tag = -1;
} *root, tree[MAXN << 1];

void update(SegTree *root) {
    root->sum = root->lson->sum + root->rson->sum;
}

void build(SegTree*& root, int l, int r) {
    static int tot;
    root = tree + (tot++), root->l = l, root->r = r;
    if (l == r) return root->sum = f[l], void();
    int mid = (l + r) >> 1;
    build(root->lson, l, mid);
    build(root->rson, mid + 1, r);
    update(root);
}

void pushTag(SegTree* root) {
    if (root->tag == -1) return;
    root->lson->tag = root->rson->tag = root->tag;
    root->lson->sum = (root->lson->r - root->lson->l + 1) * root->tag;
    root->rson->sum = (root->rson->r - root->rson->l + 1) * root->tag;
    root->tag = -1;
}

void change(SegTree* root, int l, int r, int val) {
    if (l <= root->l && root->r <= r) {
        root->tag = val;
        root->sum = (root->r - root->l + 1) * val;
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (l <= mid) change(root->lson, l, r, val);
    if (r > mid) change(root->rson, l, r, val);
    update(root);
}

int query(SegTree* root, int l, int r) {
    if (l <= root->l && root->r <= r) return root->sum;
    pushTag(root);
    int mid = (root->l + root->r) >> 1, sum(0);
    if (l <= mid) sum += query(root->lson, l, r);
    if (r > mid) sum += query(root->rson, l, r);
    return sum;
}

signed main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n >> q;
        cin >> s >> f;
        for (int i = 0; i < s.size(); i++) s[i] -= '0', f[i] -= '0';
        build(root, 0, s.size() - 1);
        for (int i = 1; i <= q; i++) cin >> l[i] >> r[i], l[i]--, r[i]--;
        bool judge = true;
        for (int i = q; i; i--) {
            int sum = query(root, l[i], r[i]);
            if (sum == (r[i] - l[i] + 1) / 2 && (r[i] - l[i] + 1) % 2 == 0) {
                judge = false;
                break;
            }
            if (sum < (r[i] - l[i] + 2) / 2)
                change(root, l[i], r[i], 0);
            else change(root, l[i], r[i], 1);
        }
        for (int i = 0; i < s.size(); i++)
            if (s[i] != query(root, i, i)) {
                judge = false;
                break;
            }
        judge ? cout << "yes\n" : cout << "no\n";
    }
    return 0;
}
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

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int tc, n, q;
array<int, MAXN> l, r, a;
string s, f;

struct SegTree {
    SegTree *lson, *rson;
    int sum, l, r;
    int tag = -1;
} *root, tree[MAXN << 1];

void update(SegTree *root) {
    root->sum = root->lson->sum + root->rson->sum;
}

void build(SegTree*& root, int l, int r) {
    static int tot;
    root = tree + (tot++), root->l = l, root->r = r;
    if (l == r) return root->sum = f[l], void();
    int mid = (l + r) >> 1;
    build(root->lson, l, mid);
    build(root->rson, mid + 1, r);
    update(root);
}

void pushTag(SegTree* root) {
    if (root->tag == -1) return;
    root->lson->tag = root->rson->tag = root->tag;
    root->lson->sum = (root->lson->r - root->lson->l + 1) * root->tag;
    root->rson->sum = (root->rson->r - root->rson->l + 1) * root->tag;
    root->tag = -1;
}

void change(SegTree* root, int l, int r, int val) {
    if (l <= root->l && root->r <= r) {
        root->tag = val;
        root->sum = (root->r - root->l + 1) * val;
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (l <= mid) change(root->lson, l, r, val);
    if (r > mid) change(root->rson, l, r, val);
    update(root);
}

int query(SegTree* root, int l, int r) {
    if (l <= root->l && root->r <= r) return root->sum;
    pushTag(root);
    int mid = (root->l + root->r) >> 1, sum(0);
    if (l <= mid) sum += query(root->lson, l, r);
    if (r > mid) sum += query(root->rson, l, r);
    return sum;
}

signed main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n >> q;
        cin >> s >> f;
        for (int i = 0; i < s.size(); i++) s[i] -= '0', f[i] -= '0';
        build(root, 0, s.size() - 1);
        for (int i = 1; i <= q; i++) cin >> l[i] >> r[i], l[i]--, r[i]--;
        bool judge = true;
        for (int i = q; i; i--) {
            int sum = query(root, l[i], r[i]);
            if (sum == (r[i] - l[i] + 1) / 2 && (r[i] - l[i] + 1) % 2 == 0) {
                judge = false;
                break;
            }
            if (sum < (r[i] - l[i] + 2) / 2)
                change(root, l[i], r[i], 0);
            else change(root, l[i], r[i], 1);
        }
        for (int i = 0; i < s.size(); i++)
            if (s[i] != query(root, i, i)) {
                judge = false;
                break;
            }
        judge ? cout << "yes\n" : cout << "no\n";
    }
    return 0;
}