#include<bits/stdc++.h>
/*
https://ac.nowcoder.com/acm/contest/1010/A
https://github.com/lydrainbowcat/tedukuri
*/
const int SIZE = 1e6 + 6;
using namespace std;
int trie[SIZE][26], End[SIZE], tot = 1, cnt[SIZE];
inline void insert(string str){
    int len = str.size(), p = 1;
    for(int i = 0; i < len; i++){
        int ch = str[i] - 'a';
        if(trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    /*End[p] = true,*/ cnt[p]++;
}
inline int /*bool*/ search(string str){
    int len = str.size(), p = 1, ans = 0;
    for(int i = 0; i < len; i++){
        int ch = str[i] - 'a';
        p = trie[p][ch];
        //if(p == 0) return false; //指针为空 该字符未被插入Trie
        if(p == 0) return ans;
        ans += cnt[p];
    }
    //return End[p]; //是否为已标记字符串的末尾
    return ans;
}
int N, M;
vector<string>vec;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> N >> M;
    vec.resize(N);
    for(int i = 0; i < N; i++) cin >> vec[i], insert(vec[i]);
    while(M--){
        string T;
        cin >> T;
        cout << search(T) << endl;
    }
    return 0;
}