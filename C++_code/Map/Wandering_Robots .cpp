#include <bits/stdc++.h>
//https://vjudge.net/contest/262550#problem/M
using namespace std;
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e3 + 3, MOD = 1e9 + 7;

struct pair_hash {
    inline size_t operator()(const pair<int, int>& p) const {
        return p.first * p.second + p.first + p.second;
    }
};

int tc, n, k;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
unordered_map<pair<int, int>, int, pair_hash> del, sub;
vector<pair<int, int>> vec;
array<pair<int, int>, MAXN> p;

void Sub(const pair<int, int>& p) {
    for (int i = 0; i < 4; i++) {
        int tox = p.first + dx[i], toy = p.second + dy[i];
        if (tox < 1 || tox > n || toy < 1 || toy > n) continue;
        if (del[{tox, toy}]) continue;
        sub[{tox, toy}]++;
    }
}

int val(const pair<int, int>& p) {
    if (p == make_pair(1, n) || p == make_pair(n, 1) || p == make_pair(n, n)
        || p == make_pair(1, 1)) return 3;
    if (p.first == 1 || p.first == n || p.second == 1 || p.second == n) return 4;
    return 5;
}

int main() {
    boost;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        del.clear(), vec.clear(), sub.clear();
        cin >> n >> k;
        int numerator = 9 + 8 * (n - 2) + 5 * (n - 1) * (n - 2) / 2;
        int denominator = 5 * n * n - 4 *n;
        if (n == 1) numerator = 1, denominator = 1;
        else if (n == 2) numerator = 9, denominator = 12;
        //error(numerator, denominator);
        int updel(0), totdel(0);
        for (int i = 1; i <= k; i++) {
            cin >> p[i].first >> p[i].second;
            p[i].first++, p[i].second++;
            del[p[i]] = true;
            totdel += val(p[i]);
            if (p[i].first + p[i].second >= n + 1) updel += val(p[i]);
        }
        for (int i = 1; i <= k; i++) Sub(p[i]);

        for (auto& i : sub) {
            auto p = i.first;
            int cnt = i.second;
            totdel += cnt;
            if (p.first + p.second >= n + 1) updel += cnt;
        }
        numerator -= updel;
        denominator -= totdel;
        cout << "Case #" << cs << ": " << numerator / __gcd(numerator, denominator) 
            << "/" << denominator / __gcd(numerator, denominator) << "\n";
    }
    return 0;
}