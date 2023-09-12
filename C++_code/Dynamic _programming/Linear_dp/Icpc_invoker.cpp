#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

using namespace std;

string skill[10][6] = {
    "QQQ", "QQQ", "QQQ", "QQQ", "QQQ", "QQQ", "QQW", "QQW", "QWQ", "QWQ",
    "WQQ", "WQQ", "QQE", "QQE", "QEQ", "QEQ", "EQQ", "EQQ", "WWW", "WWW",
    "WWW", "WWW", "WWW", "WWW", "QWW", "QWW", "WQW", "WQW", "WWQ", "WWQ",
    "WWE", "WWE", "WEW", "WEW", "EWW", "EWW", "EEE", "EEE", "EEE", "EEE",
    "EEE", "EEE", "QEE", "QEE", "EQE", "EQE", "EEQ", "EEQ", "WEE", "WEE",
    "EWE", "EWE", "EEW", "EEW", "QWE", "QEW", "EQW", "WQE", "WEQ", "EWQ"};
map<char, int> m;
int dp[MAXN][6];  //位置为i 技能释放顺序为j的最小按键数

inline int getNum(string pre, string cur) {
    if (pre == cur) return 0;
    if (pre[1] == cur[0] && pre[2] == cur[1]) return 1;
    if (pre[2] == cur[0]) return 2;
    return 3;
}

int main() {
    string s;
    m['Y'] = 0, m['V'] = 1, m['G'] = 2, m['C'] = 3;
    m['X'] = 4, m['Z'] = 5, m['T'] = 6;
    m['F'] = 7, m['D'] = 8, m['B'] = 9;
    while (cin >> s) {
        memset(dp, 0x3f, sizeof(dp));
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < 6; i++) dp[0][i] = 4;
        for (int i = 1; i < s.size(); i++)
            for (int s1 = 0; s1 < 6; s1++)
                for (int s2 = 0; s2 < 6; s2++) {
                    dp[i][s1] = min(
                        dp[i][s1],
                        dp[i - 1][s2] +
                            getNum(skill[m[s[i - 1]]][s2], skill[m[s[i]]][s1]) +
                            1);
                    if (i + 1 == s.size()) ans = min(ans, dp[i][s1]);
                }
        cout << ans << endl;
    }
    return 0;
}