#include<bits/stdc++.h>
//P1337 [JSOI2004]平衡点 / 吊打XXX
//https://www.luogu.com.cn/problem/P1337
using namespace std;

constexpr int MAXN = 1e3 + 3;
constexpr double down = 0.996;

int n;
pair<pair<int, int>, int> obj[MAXN];
double x, y, Ep;

inline double energy(double x, double y) { //重力势能越小越稳定
    double E = 0;
    for (int i = 0; i < n; i++) {
        double dx = x - obj[i].first.first;
        double dy = y - obj[i].first.second;
        E += sqrt(dx * dx + dy * dy) * obj[i].second;
    }
    return E;
}

inline void SA() { //SimulateAnneal
    double T = 3000;
    while (T > 1e-14) {
        double randx = x + (rand() * 2 - RAND_MAX) * T;
        double randy = y + (rand() * 2 - RAND_MAX) * T;
        double E = energy(randx, randy);
        double delta = E - Ep;
        if (delta < 0) { //E更小 答案更优
            x = randx, y = randy, Ep = E;
        }
        else if (exp(-delta / T) * RAND_MAX > rand()) { //根据多项式概率接受
            x = randx, y = randy;
        }
        T *= down;
    }
}

int main() {
    //cout << RAND_MAX << endl;
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> obj[i].first.first >> obj[i].first.second >> obj[i].second;
        x += obj[i].first.first, y += obj[i].first.second;
    }
    x /= n, y /= n, Ep = energy(x, y);
    for (int i = 0; i < 4; i++) SA();
    cout << setprecision(3) << fixed << x << " " << y << endl;
    return 0;
}