#include <bits/stdc++.h>
#define PI acos(-1)
//https://www.luogu.com.cn/problem/P3256 P3256 [JLOI2013]赛车
using namespace std;

constexpr int MAXN = 1e4 + 4;
constexpr double EPS = 1e-8;

int n, st[MAXN], v[MAXN], stk[MAXN], top;

struct Car {
    Car() = default;
    Car(int _st, int _v, int _id) : st(_st), v(_v), id(_id) {}
    int st = -1, v = 0, id = 0;
} car[MAXN];

inline double calcTime(int a, int b) {  // a追上b所需时间
    if (car[a].v == car[b].v) return 2e9;
    return 1.0 * (car[b].st - car[a].st) / (car[a].v - car[b].v);
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> st[i];
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        car[i] = Car(st[i], v[i], i);
    }
    sort(car + 1, car + n + 1, [](const Car& a, const Car& b) {
        return a.v == b.v ? a.st < b.st : a.v < b.v;
    });

    stk[++top] = 1;
    for (int i = 2; i <= n; i++) {
        while (top && car[i].st > car[stk[top]].st) top--;
        while (top > 1 &&
               calcTime(i, stk[top]) < calcTime(stk[top - 1], stk[top]) - EPS)
            top--;
        stk[++top] = i;
    }

    sort(stk + 1, stk + top + 1, [](int a, int b) { return car[a].id < car[b].id; });
    cout << top << endl;
    for (int i = 1; i <= top; i++) cout << car[stk[i]].id << " ";
    return 0;
}