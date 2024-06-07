#include<bits/stdc++.h>
using namespace std;
char B[21]= {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K'};
vector<char>num;
int main(){
    /*故如果余数小于0，则加上|R|转为正数，由于加上了一个|R|，故商要加1*/
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int N, base;
    cin >> N >> base;
    cout << N << "=";
    while(abs(N)){
        int res = N % base;
        N = N / base; 
        if(res < 0) N ++, res -= base;
        num.push_back(B[res]);
    }
    for(int i = num.size()-1; i >= 0; i--)
        cout<<num[i];
    cout << "(base" << base << ")";
    return 0;
}