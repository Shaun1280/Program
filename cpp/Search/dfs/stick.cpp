#include<bits/stdc++.h>
const int MAXN = 6e1 + 6;
int n, sum, maxL, L[MAXN], used[MAXN];
int nStick, Len, tot;
using namespace std;
inline bool search(int cnt, int curLen, int preId){//preId初始值为0
    if(cnt >= nStick) return true; //
    if(curLen == Len) return search(cnt + 1, 0, 0); 
    int fail = 0;
    for(int i = preId + 1; i <= tot; i++){//向后枚举
        if(!used[i] && L[i] != fail && curLen + L[i] <= Len){
            used[i] = true;
            if(search(cnt, curLen + L[i], i)) return true; //选择该木棍
            used[i] = false; //回溯
            fail = L[i]; //L[i]不能满足条件 相同的值也不能满足条件
            if(curLen == 0 || curLen + L[i] == Len) return false; //后面全部的都不能用
        }
    }
    return false;
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n;
    sum = 0, maxL = 0;
    for(int i = 1, tmp; i <= n; i++){
        cin >> tmp;
        if(tmp > 50) continue;
        L[++tot] = tmp;
        sum += L[tot], maxL = max(maxL, L[tot]);
    }
    sort(L + 1, L + tot + 1), reverse(L + 1, L + tot + 1);//降序
    for(Len = maxL; Len <= sum; Len++){
        memset(used, 0, sizeof(used));
        if(sum % Len) continue; // 不能等分
        nStick = sum / Len; 
        if(search(0, 0, 0)){
            cout << Len << endl;
            break;
        } 
    }
    return 0;
}