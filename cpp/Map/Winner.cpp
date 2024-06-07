#include <bits/stdc++.h>
// CF2A Winner map
const int MAXN = 1e3 + 1;

using namespace std;

map<string, int> final_score, max_score;
struct node {
    string name;
    int score;
} P[MAXN];

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int n, MAX = -0x3f3f3f3f;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> P[i].name >> P[i].score, final_score[P[i].name] += P[i].score;
    for (int i = 1; i <= n; i++) MAX = max(MAX, final_score[P[i].name]);
    for (int i = 1; i <= n; i++) {
        max_score[P[i].name] += P[i].score;
        if (max_score[P[i].name] >= MAX && final_score[P[i].name] == MAX) {
            //需满足两个条件 P[i]的final_socre为最大值
            //P[i]在这个时刻i的值>=最大值
            cout << P[i].name;
            break;
        }
    }
    return 0;
}