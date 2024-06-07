#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/P3879
//P3879 [TJOI2010]阅读理解
int n, m;
map<string, vector<int> >M;
string tmp;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++){
        int Len;
        cin >> Len;
        while(Len--){
            cin >> tmp;
            M[tmp].push_back(i);
        }
    }
    cin >> m;
    while(m--){
        cin >> tmp;
        for(int i = 0; i < M[tmp].size(); i++){
            int id = M[tmp][i];
            if(!i) cout << id << " ";
            if(i && id != M[tmp][i - 1]) cout << id<< " ";
        }
        cout << endl;
    }
    return 0;
}