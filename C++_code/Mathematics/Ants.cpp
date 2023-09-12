#include<bits/stdc++.h>
//https://onlinejudge.org/external/107/p10714.pdf
/*
两只蚂蚁相遇反向运动相当于沿原方向继续运动
因此全部掉落的
最短时间为 min(l - x[i], x[i])的最大值
最长时间为 max(l - x[i], x[i])的最大值
*/
using namespace std;
int T;
int l, n, x;
int maxt = 0, mint = 0;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> T;
    while(T--){
        int maxt = 0, mint = 0;
        cin >> l >> n;
        for(int i = 0; i < n; i++){
            cin >> x;
            maxt = max(maxt, max(x, l - x));
            mint = max(mint, min(x, l - x));
        }
        cout << mint <<" "<< maxt <<endl;
    }
    return 0;
}