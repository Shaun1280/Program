#include <bits/stdc++.h>
/*
print the number of (a,b,c,d) tuples 
where a = d, b = c;
*/
#define uLL unsigned long long
#define M 1000000007
using namespace std;
uLL dp4[26][26][26][26];
uLL dp3[26][26][26];
uLL dp2[26][26];
uLL dp1[26];
uLL sum = 0ull;
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        int cur = s[i] - 'a';
        for (int pre = 0; pre < 26; pre++)
        {
            dp4[cur][pre][pre][cur] += dp3[cur][pre][pre];
            dp4[cur][pre][pre][cur] %= M;
            dp3[pre][cur][cur] += dp2[pre][cur];
            dp3[pre][cur][cur] %= M;
            dp2[pre][cur] += dp1[pre];
            dp2[pre][cur] %= M;
        }
        dp1[cur]++; //$
    }
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            sum = (sum + dp4[i][j][j][i]) % M;
    cout << sum;
    return 0;
}