#include <bits/stdc++.h>
// https://codeforces.com/gym/103186/problem/K
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 998244353;

int tc, n, sg[11];
string s[11];
int cnt[26];
unordered_map<long long, int> mp;

int SG() {
    int tot = 0, num = 0;
    bool vis[27]; // !don't use global variable
    memset(vis, false, sizeof(vis));
    long long hash = 0;
    sort(cnt, cnt + 26, [](const int& a, const int& b) {
        return a > b;
    });
    int cpyCnt[26];
    for (int i = 0; i < 26; i++) {
        cpyCnt[i] = cnt[i];
        hash = (hash * 41 % MOD + cnt[i]) % MOD;
        if (cnt[i]) tot++, num = cnt[i];
        else break;
    }
    if (mp.count(hash)) return mp[hash];

    if (tot == 1 && !(num & 1)) return mp[hash] = 0;
    else if (tot == 1 && (num & 1)) return mp[hash] = 1;


    for (int i = 0; i < 26; i++) {
        if (cnt[i]) {
            cnt[i]--;
            vis[SG()] = true;
            for (int k = 0; k < 26; k++) {
                if (!cpyCnt[k]) break;
                cnt[k] = cpyCnt[k];
            }

            for (int j = i + 1; j < 26; j++) {
                if (cnt[j]) {
                    cnt[i]--, cnt[j]--;
                    vis[SG()] = true;
                    for (int k = 0; k < 26; k++) {
                        if (!cpyCnt[k]) break;
                        cnt[k] = cpyCnt[k];
                    }
                }
            }
        }
    }

    int mex = 0;
    while (vis[mex]) ++mex;
    return mp[hash] = mex;
}

signed main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 0; i < n; i++) sg[i] = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            for (int i = 0; i < 26; i++) cnt[i] = 0;
            for (auto& c : s[i]) cnt[c - 'a']++;
            sg[i] = SG();
            mp.clear();
        }
        int res = 0;
        for (int i = 0; i < n; i++) res ^= sg[i];
        cout << (res == 0 ? "Bob" : "Alice") << "\n";
        //Alice Bob
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */