#include<bits/stdc++.h>
const int MAXN = 1e3 + 1;
const double EPSILON = 1e-6;
using namespace std;
double a[MAXN], dp[MAXN];
//设dp[i]为当前选择的奶牛总质量为i时 sigma( (t[i] - Z w[i] ) x[i])最大值多少，
//初始化为-0x3f, dp[0] = 0
int w[MAXN], t[MAXN];
int N, W;
//https://www.luogu.org/problemnew/solution/P4377
inline bool check(double Z){
    memset(dp, -0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i = 1; i <= N; i++)
        a[i] = t[i] - Z * w[i];
    for(int i = 1; i <= N; i++)
        for(int j = W; j >= 0; j--)
            dp[min(W, j + w[i])] = max(dp[min(W, j + w[i])], dp[j] + a[i]);
    return dp[W] >= 0.0;
}
inline void Binary_search(double l, double r){
    while(l + EPSILON < r){
        double mid = (l + r) / 2;
        if(check(mid)) l = mid; //答案小了
        //sigma(t[i] x[i]) >= sigma(w[i] x[i])*Z
        else r = mid; //答案大了
        //sigma(t[i] x[i]) < sigma(w[i] x[i])*Z
    }
    cout << floor(l);
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> N >> W;
    for(int i = 1; i <= N; i++)
        cin >> w[i] >> t[i], t[i] *= 1000; //答案为A*1000 将t*1000即可
    Binary_search(0.0, 1e9);
    return 0;
}