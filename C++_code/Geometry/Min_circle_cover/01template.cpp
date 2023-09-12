#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e6 + 6;
constexpr double EPS = 1e-12;

struct Vec2 {
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {}

    friend inline double dis(const Vec2& lhs, const Vec2& rhs) {
        return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2));
    }
    double x, y;
} vec[MAXN], o;

int n;
double radius;

inline void getCircle(int i, int j, int k) {
    double a = vec[i].x - vec[j].x;
    double b = vec[i].y - vec[j].y;
    double c = vec[i].x - vec[k].x;
    double d = vec[i].y - vec[k].y;
    double e = (pow(vec[i].x, 2) - pow(vec[j].x, 2) + pow(vec[i].y, 2) -
                pow(vec[j].y, 2)) / 2;
    double f = (pow(vec[i].x, 2) - pow(vec[k].x, 2) + pow(vec[i].y, 2) -
                pow(vec[k].y, 2)) / 2;
    o.x = (d * e - b * f) / (a * d - b * c);
    o.y = (a * f - c * e) / (a * d - b * c);
    radius = dis(vec[i], o);
}

inline void calc() {
    random_shuffle(vec + 1, vec + n + 1);
    o = vec[1];
    for (int i = 2; i <= n; i++) {
        if (dis(vec[i], o) > radius + EPS) {
            o = vec[i], radius = 0;
            for (int j = 1; j <= i - 1; j++) {
                if (dis(vec[j], o) > radius + EPS) {
                    o.x = (vec[i].x + vec[j].x) / 2;
                    o.y = (vec[i].y + vec[j].y) / 2;
                    radius = dis(o, vec[j]);
                    for (int k = 1; k <= j - 1; k++)
                        if (dis(vec[k], o) > radius + EPS) getCircle(i, j, k);
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(2) << fixed;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> vec[i].x >> vec[i].y;
    calc();
    cout << o.x << " " << o.y << " " << radius << endl;
    return 0;
}