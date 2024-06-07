#include<bits/stdc++.h>
/*
https://www.hackerrank.com/challenges/game-of-stones-1/editorial
dp[0] = 0; //where 0 means a losing position
dp[1] = 0;
dp[2] = 1;
dp[3] = 1;
dp[4] = 1;
for i >= 5
dp[i] = 1 if (dp[i-2] = 0 || dp[i-3] = 0 || dp[i-5] = 0)
dp[i] = 0 otherwise
*/
using namespace std;
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T, n;
    cin >> T;
    while(T--){
        cin >> n;
        if( (n % 7) <=1 ) cout<<"Second"<<endl;
        else cout<<"First"<<endl;
    }
    return 0;
}