#include<bits/stdc++.h>
using namespace std;
//P2887 [USACO07NOV]防晒霜Sunscreen
//https://www.luogu.com.cn/problem/P2887
//区间覆盖问题，求线段最多覆盖多少点，线段按右端点排序，防晒霜按防护值排序
int c, L;
struct node{
    int minSpfi, maxSpfi, vis;
};
struct node2{
    int spfi, cnt;
};
vector<node>cow;
vector<node2>lotion;
inline bool cmp1(const node2 &a, const node2 &b){
    return a.spfi < b.spfi;
}
inline bool cmp(const node &a, const node &b){
    return a.maxSpfi < b.maxSpfi;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> c >> L;
    cow.resize(c + 1), lotion.resize(L + 1);
    for(int i = 1; i <= c; i++) cin >> cow[i].minSpfi >> cow[i].maxSpfi;
    for(int i = 1; i <= L; i++) cin >> lotion[i].spfi >> lotion[i].cnt;
    sort(lotion.begin(), lotion.end(), cmp1);
    int cnt = 0;
    sort(cow.begin(), cow.end(), cmp);
    for(int i = 1; i <= L; i++){
        for(int j = 1; j <= c; j++){
            if(cow[j].vis || !lotion[i].cnt) continue;
            if(cow[j].minSpfi <= lotion[i].spfi && cow[j].maxSpfi >= lotion[i].spfi){
                lotion[i].cnt--, cnt++;
                cow[j].vis = 1;
            }
        }
    }
    cout << cnt;
    return 0;
}