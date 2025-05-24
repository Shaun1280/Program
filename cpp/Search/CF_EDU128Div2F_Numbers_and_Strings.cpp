#include <bits/stdc++.h>
// https://codeforces.com/contest/2104/problem/F

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

using namespace std;

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7, P = 1e8 + 7;

vector<pair<string, long long>> aux2;
vector<long long> aux;

void init() {
    auto S = [](long long x) -> string {
        string ret = to_string(x) + to_string(x + 1);
        sort(ret.begin(), ret.end());
        return ret;
    };
    auto get_integer = [](string s) -> long long {
        int first_non_zero = 0;
        while (first_non_zero < s.size() && s[first_non_zero] == '0') {
            first_non_zero++;
        }
        swap(s[0], s[first_non_zero]);
        return stoll(s);
    };
    auto dfs = [&](auto &&dfs, string cur, bool flag) -> void {
        if (*max_element(cur.begin(), cur.end()) > '0') {
            long long x = get_integer(cur);
            aux2.emplace_back(S(x), x);
        }
        if (cur.size() < 9) {
            if (flag) {
                dfs(dfs, cur + '9', flag);
            } else {
                for (char c = '0'; c <= '9'; c++) {
                    dfs(dfs, cur + c, c < cur.back());
                }
            }
        }
    };

    for (char c = '0'; c <= '9'; c++) {
        dfs(dfs, string(1, c), false);
    }

    sort(aux2.begin(), aux2.end());
    for (int i{0}; i < aux2.size(); i++) {
        if (i == 0 || aux2[i].first != aux2[i - 1].first) {
            aux.push_back(aux2[i].second);
        }
    }
    sort(aux.begin(), aux.end());
}

void solveOne(int ncase) {
    long long n;
    cin >> n;
    cout << upper_bound(aux.begin(), aux.end(), n) - aux.begin() << '\n';
}

int main() {
    boost;
    init();
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}