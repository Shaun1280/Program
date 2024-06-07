#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/P2114
int n, m;
vector<pair<string, int> >opt;
inline int calculatBit(int bit, int cur){
    for(int i = 0; i < n; i++){
        int x = opt[i].second >> bit & 1; //求第bit位
        if(opt[i].first == "AND") cur &= x;
        else if(opt[i].first == "OR") cur |= x;
        else cur ^= x;
    }
    return cur;
}
int main(){
    scanf("%d%d", &n, &m);
    opt.resize(n);
    for(int i = 0; i < n; i++){
        char str[5]; int x;
        scanf("%s%d", str, &x);
        opt[i] = make_pair(str, x);
    }
    int val = 0, ans = 0;
    for(int bit = 29; bit >= 0; bit--){
        int res0 = calculatBit(bit, 0), res1 = calculatBit(bit, 1);
        //填0,1后的该位的值
        if(val + (1 << bit) <= m && res0 < res1)
            val += 1 << bit, ans += res1 << bit;//填1
        else ans += res0 << bit; //填0
    }
    cout << ans << endl;
    return 0;
}