#include <bits/stdc++.h>
const int MAXM = 26;
const int MAXN = 1e4 + 1;
using namespace std;
long long dp[MAXN];
int coin[MAXM];
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, m;
    std::ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        cin >> coin[i];
    dp[0] = 1;
    for (int i = 1; i <= m; i++)
        /*for m first: because 1 2 2 1 = 1 1 2 2 to make dp in order*/
        for (int j = coin[i]; j <= n; j++)
            dp[j] += dp[j - coin[i]]; //get cnt of ways
    cout << dp[n];
    return 0;
}

/*
//recursion
1.Take coin , making the next state, solve(i, make - c[i])
2.Go on to the next coin, making the next state, solve(i+1, make)
Don't forget to eliminate the overlapping subproblems 
using memoization, or your solution will time out. 
//
#include <bits/stdc++.h>

using namespace std;

int c[52];
int numCoins;
long long table[52][252];
bool calculated[52][252];
long long solve(int i, int make)
{
    if(make<0) return 0;
    if(make==0)return 1;
    if(i > numCoins) return 0;
    if(calculated[i][make] == false){ //eliminating overlap
        table[i][make] = solve(i, make - c[i]) + solve(i+1, make);
        calculated[i][make] = true;
    }
    return table[i][make];
}
int main(){

    int make;
    cin>>make>>numCoins;
    for(int i=1;i<=numCoins;i++){
        cin>>c[i];
    }
    cout<<solve(1, make)<<endl;
    return 0;
}
*/