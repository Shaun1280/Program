#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
//https://www.luogu.com.cn/problem/SP4354
const int P = 99991;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int n;
int snow[MAXN][6];
vector< vector<int> >H;//存储下标
inline int Hash(int * s){
    int sum = 0, mul = 1;
    for(int i = 0; i < 6; i++){
        sum = (sum + s[i]) % P;
        mul = (long long)mul * s[i] % P;
    }
    return (sum + mul) % P;
}
inline bool equal(int * s1, int *s2){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            bool eq = true;
            for(int k = 0; k < 6; k++)
                if(s1[(i + k) % 6] != s2[(j + k) % 6]) eq = 0;
            if(eq) return true;
            eq = true;
            for(int k = 0; k < 6; k++)
                if(s1[(i + k) % 6] != s2[(j - k + 6) % 6]) eq = 0;
            if(eq) return true;
        }
    }
    return false;
}
inline bool insert(int * s, int cnt){
    int val = Hash(s);
    for(auto i : H[val]){
        if(equal(snow[i], s)) return true;
    }
    H[val].push_back(cnt);
    return false;
}
int main(){
    n = read();
    H.resize(P);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 6; j++) snow[i][j] = read();
        if(insert(snow[i], i)){
            puts("Twin snowflakes found.");
            return 0;
        }
    }
    puts("No two snowflakes are alike.");
    return 0;
}