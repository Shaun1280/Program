#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, k;

    cin >> n >> k;
    vector<string> _map(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> _map[i];
        _map[i].insert(_map[i].begin(), ' ');
    }

    vector<pair<int, int>> q;
    vector<vector<int>> sum_a(n + 1, vector<int>(n + 1));
    vector<vector<int>> vis(n + 1, vector<int>(n + 1));

    int longest = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            sum_a[i][j] =
                max(sum_a[i - 1][j], sum_a[i][j - 1]) + (_map[i][j] == 'a');
            // cout << sum_a[i][j] << " ";
            if (i + j - 1 <= sum_a[i][j] + k) {
                longest = max(longest, i + j - 1);
            }
        }
        // cout << "\n";
    }

    // cout << longest << "\n";

    string s;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i + j - 1 <= sum_a[i][j] + k && i + j - 1 == longest) {
                q.push_back({i, j});
            }
        }
    }

    // cout << "ok" << "\n";

    if (longest == 0) {
        s.push_back(_map[1][1]);
        q.push_back({1, 1});
    }

    while (q.size()) {
        decltype(q) tmp;
        char mn = 'z' + 1;
        for (const auto& [i, j] : q) {
            if (i + 1 <= n && _map[i + 1][j] < mn)
                mn = _map[i + 1][j];
            if (j + 1 <= n && _map[i][j + 1] < mn)
                mn = _map[i][j + 1];
        }

        if (mn != 'z' + 1)
            s.push_back(mn);
        for (const auto& [i, j] : q) {
            if (i + 1 <= n && _map[i + 1][j] == mn && !vis[i + 1][j]) 
                tmp.push_back({i + 1, j}), vis[i + 1][j] = 1;
            if (j + 1 <= n && _map[i][j + 1] == mn && !vis[i][j + 1])
                tmp.push_back({i, j + 1}), vis[i][j + 1] = 1;
        }

        q = std::move(tmp);
    }

    for (int i = 0; i < longest; ++i)
        cout << "a";
    cout << s << "\n";

    return 0;
}