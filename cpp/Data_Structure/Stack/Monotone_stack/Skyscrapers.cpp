#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/
#define int long long 
constexpr int MAXN = 5e5 + 5;
using namespace std;
int n, m[MAXN], L[MAXN], R[MAXN], f[MAXN], g[MAXN];
stack<int>stL, stR;
signed main(){
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> m[i];
    for (int i = 1; i <= n; i++) { //left monotone stack
        while(!stL.empty() && m[stL.top()] > m[i]) stL.pop();
        if (stL.empty()) L[i] = 0; else L[i] = stL.top(); 
        //L[i] is the pos of closest left val smaller than current height
        f[i] = f[L[i]] + m[i] * (i - L[i]);
        stL.push(i);
    }
    for (int i = n; i >= 1; i--) {
        while(!stR.empty() && m[stR.top()] > m[i]) stR.pop();
        if (stR.empty()) R[i] = n + 1; else R[i] = stR.top();
        //R[i] is the pos of closest right val smaller than current height
        g[i] = g[R[i]] + m[i] * (R[i] - i);
        stR.push(i);
    }
    int maxSum(0), pos(0);
    for (int i = 1; i <= n; i++) 
        if (maxSum < f[i] + g[i] - m[i]) //get maximum peak
            maxSum = f[i] + g[i] - m[i], pos = i;
    int maxR = m[pos], maxL = m[pos];
    for (int i = pos + 1; i <= n; i++) m[i] = min(m[i], maxR), maxR = min(maxR, m[i]);
    for (int i = pos - 1; i >= 1; i--) m[i] = min(m[i], maxL), maxL = min(maxL, m[i]);
    for (int i = 1; i <= n; i++) cout << m[i] << " ";
	return 0;
}