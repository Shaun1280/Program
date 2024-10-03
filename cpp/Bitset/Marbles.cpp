#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1537
using namespace std;
//能否凑出 sum / 2
#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n;
array<int, 7> num;
bitset<MAXN> dp;

int main() {
    boost;
    for (int tc = 1; tc; tc++) {
        int sum = 0;
        for (int i = 1; i <= 6; i++)
            cin >> num[i], sum += i * num[i];
        if (!sum) break;

        cout << "Collection #" << tc << ":\n";

        if (sum & 1) {
            cout << "Can't be divided.\n";
            cout << "\n";
            continue;
        }

        dp.reset(), dp.set(0, true); //dp[i] denotes value i can be reached
        bool judge = false;
        for (int i = 1; i <= 6; i++) { //val = i
            for (int j = 1; j <= num[i]; j++) {
                dp |= (dp << i); //for all pos, dp[pos + i] can be reached
                if (dp[sum / 2]) {
                    judge = true;
                    break;
                }
            }
            if (judge) break;
        }
        judge ? cout << "Can be divided.\n" : cout << "Can't be divided.\n";
        cout << "\n";
    }
    return 0;
}
