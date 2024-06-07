#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define PI acosl(-1)
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

#define double long double
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
        Complex operator*(double num) {
            return Complex(x * num, y * num);
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
            Complex wm(cosl(2.0 * PI / m), type * sinl(2.0 * PI / m));
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
        if (type == -1) for (int i = 0; i < sz; i++) a[i].x /= sz, a[i].y /= sz;
    }
}

namespace Polynomial {
    using namespace FFT;
    constexpr int Base = 1 << 15;

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

    void Convolution(int n, int m, int p, int a[], int b[], int c[]) { // mtt
        int N = n + m + 1;
        init(N);
        Complex a0[N], a1[N], b0[N], b1[N], P[N], Q[N], I(0, 1);
        for (int i = 0; i <= n; i++) a0[i].x = (a[i] % p) / Base, a1[i].x = (a[i] % p) % Base;
        for (int i = 0; i <= m; i++) b0[i].x = (b[i] % p) / Base, b1[i].x = (b[i] % p) % Base;

        auto connectFFT = [&](Complex a[], Complex b[]) {
            for (int i = 0; i < N; i++) a[i].y = b[i].x; // Ax + iBx
            dft(a, N, 1);
            b[0] = Complex(a[0].x, -a[0].y); // conjugate of a[0]
            for (int i = 1; i < N; i++) b[i] = Complex(a[N - i].x, -a[N - i].y);
            Complex x1, x2;
            for (int i = 0; i < N; i++) {
                x1 = a[i], x2 = b[i];
                a[i] = (x1 + x2) * 0.5;
                b[i] = (x2 - x1) * I * 0.5;
            }
        };

        connectFFT(a0, a1), connectFFT(b0, b1);
        Complex x1, x2;
        for (int i = 0; i < N; i++) {
            x1 = a0[i] * b0[i], x2 = I * a1[i] * b0[i], P[i] = x1 + x2;
            x1 = a0[i] * b1[i], x2 = I * a1[i] * b1[i], Q[i] = x1 + x2;
        }
        dft(P, N, -1), dft(Q, N, -1);
        for (int i = 0; i <= n + m; i++)
            c[i] = (1LL * Base * Base % p * (llround(P[i].x) % p) % p + 1LL * Base
                    * (llround(Q[i].x + P[i].y) % p) % p + (llround(Q[i].y) % p)) % p;
    }
};

int a[MAXN], b[MAXN], c[MAXN * 2];

int main() {
    int n, m, p;
    read(n, m, p);
    for (int i = 0; i <= n; i++) read(a[i]);
    for (int i = 0; i <= m; i++) read(b[i]);
    Polynomial::Convolution(n, m, p, a, b, c);
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