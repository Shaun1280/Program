#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define PI acos(-1)
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

constexpr int MAXN = 1e6 + 6;

namespace FFT {
    struct Complex {
        double x, y;
        Complex(double _x = .0, double _y = .0) : x(_x), y(_y) {}
        Complex operator*(Complex &other) {
            return Complex(x * other.x - y * other.y, x * other.y + y * other.x);
        }
        Complex operator+(Complex &other) {
            return Complex(x + other.x, y + other.y);
        }
        Complex operator-(Complex &other) {
            return Complex(x - other.x, y - other.y);
        }
    };

    int R[4000001];
    void init(int& sz) {
        if (__builtin_popcount(sz) != 1) sz = 1 << (1 + (int)log2(sz));
        for (int i = 0; i < sz; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (sz >> 1) : 0);
    }


    void dft(Complex a[], int sz, int type) {
        for (int i = 0; i < sz; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int m = 2; m <= sz; m <<= 1) {
            Complex wm(cos(2 * PI / m), type * sin(2 * PI / m));
            for (int k = 0; k < sz; k += m) {
                Complex w(1);
                for (int j = 0; j < m / 2; j++) {
                    Complex t = w * a[k + j + m / 2];
                    Complex u = a[k + j];
                    a[k + j] = u + t;
                    a[k + j + m / 2] = u - t;
                    w = w * wm;
                }
            }
        }
        if (type == -1) for (int i = 0; i < sz; i++) a[i].x /= sz;
    }
}

namespace Polynomial {
    using namespace FFT;

    void Convolution(int n, int m, int a[], int b[], int c[]) { // a[0, n] b[0, m]
        int N = n + m + 1;
        init(N);
        Complex f[N], g[N];
        for (int i = 0; i <= n; i++) f[i].x = a[i];
        for (int i = 0; i <= m; i++) g[i].x = b[i];
        dft(f, N, 1), dft(g, N, 1);
        Complex res[N];
        for (int i = 0; i < N; i++) res[i] = f[i] * g[i];
        dft(res, N, -1);
        for (int i = 0; i <= n + m; i++) c[i] = lround(res[i].x);
    }
};

int a[MAXN], b[MAXN], c[MAXN * 2];

int main() {
    int n, m, N;
    read(n, m);
    for (int i = 0; i <= n; i++) read(a[i]);
    for (int i = 0; i <= m; i++) read(b[i]);
    Polynomial::Convolution(n, m, a, b, c);
    for (int i = 0; i <= n + m; i++) printf("%d ", c[i]);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */