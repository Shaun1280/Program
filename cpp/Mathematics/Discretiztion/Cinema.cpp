#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/cf670c-cinema
//CF670C Cinema
const int MAXN = 2e5 + 5;
using namespace std;
int n, m, cnt[MAXN * 3];
vector<int>A, D;
int sci[MAXN], audio[MAXN], subtitle[MAXN];
inline void discrete(){
    sort(A.begin(), A.end());
    for(int i = 0; i < A.size(); i++){
        if(i == 0)  D.push_back(A[i]);
        else if(A[i] != A[i - 1]) D.push_back(A[i]);
    }
}
inline int find(int x){
    return lower_bound(D.begin(), D.end(), x) - D.begin();
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> sci[i], A.push_back(sci[i]);
    cin >> m;
    for(int i = 0; i < m; i++) cin >> audio[i], A.push_back(audio[i]);
    for(int i = 0; i < m; i++) cin >> subtitle[i], A.push_back(subtitle[i]);
    sort(A.begin(), A.end());
    discrete();
    for(int i = 0; i < n; i++) cnt[find(sci[i])]++;
    int id = 0, preCnt1 = -1, preCnt2 = -1;
    for(int i = 0; i < m; i++){
        int cnt1 = cnt[find(audio[i])], cnt2 = cnt[find(subtitle[i])];
        if(cnt1 > preCnt1 || (cnt1 == preCnt1 && cnt2 > preCnt2)){
            id = i + 1;
            preCnt1 = cnt1;
            preCnt2 = cnt2;
        }
    }
    cout << id;
    return 0;
}