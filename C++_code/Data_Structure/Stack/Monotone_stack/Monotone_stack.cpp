#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/SP1805
//SP1805 HISTOGRA - Largest Rectangle in a Histogram
constexpr int MAXN = 1e5 + 5;
typedef long long LL;
using namespace std;
int n, h[MAXN];
int main(){
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    while (cin >> n && n) {
        LL ans = 0;
        stack<pair<int, int>>s; //hight width
        for (int i = 1; i <= n; i++) cin >> h[i];
        h[n + 1] = 0;
        // add an rectangle whose hight is 0 
        // to deal with monotone increasing hight
        for (int i = 1; i <= n + 1; i++) {
            int width = 0;
            while (!s.empty() && h[i] < s.top().first) {
                width += s.top().second; //total width of higher rectangle
                ans = max(ans, 1LL * width * s.top().first); //get area
                cout << "pop" << endl;
                s.pop();
            }
            s.push({h[i], width + 1}); //total width + 1 * current hight
        }
        cout << ans << endl;
    }
	return 0;
}