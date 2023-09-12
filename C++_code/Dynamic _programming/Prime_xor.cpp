#include <bits/stdc++.h>
/*needed to be more readable*/
const int MAXV = 2 << 13 - 1;
const int M = 1e9 + 7;
using namespace std;
int isprime[MAXV + 1];
vector<int> prime, val;
inline void Euler_prime()
{
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = false, isprime[1] = false;
    for (int i = 2; i <= MAXV; i++)
    {
        if (isprime[i])
            prime.push_back(i);
        for (int j = 0; j < prime.size(); j++)
        {
            if (i * prime[j] > MAXV)
                break;
            isprime[i * prime[j]] = false;
            if (!(i % prime[j]))
                break;
        }
    }
} //get prime number
long long dp[1002][MAXV + 1], cnt[4501];
/*
*dp[i][j]  the count of subsets that can be formed 
*with the first i elements,  
*such that the xor-sum of the elements in the subset is j.
*/
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int q, n;
    Euler_prime();
    cin >> q;
    while (q--)
    {
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));
        val.clear();
        cin >> n;
        for (int i = 0, tmp; i < n; i++)
            cin >> tmp, cnt[tmp]++;
        for (int i = 3500; i <= 4500; i++)
            if (cnt[i])
                val.push_back(i);
        dp[1][0] = cnt[val[0]] + 2 >> 1;
        dp[1][val[0]] = cnt[val[0]] + 1 >> 1;
        //cnt=2k-1 val^=num[i]
        //cnt=2k val doesn't change, cnt=0 if also a way
        /*if cnt=0, dp=1 or 0*/
        for (int i = 2; i <= val.size(); i++)
            //enum every num from 3500-4500 -3500
            for (int j = 0; j <= MAXV; j++)                               //enum present val
                dp[i][j] = (dp[i - 1][j] * (cnt[val[i - 1]] + 2 >> 1) % M /*cnt[i]%2==0*/
                            + dp[i - 1][j ^ val[i - 1]] * (cnt[val[i - 1]] + 1 >> 1) % M) %
                           M; /*cnt[i]%2!=0*/
        /*1^i^i=1 get previous, then use multipul theory */
        long long ans = 0;
        for (auto i : prime)
            ans = (ans + dp[val.size()][i]) % M;
        cout << ans << endl;
    }
    return 0;
}
/*
  mem[0][0]=1;
    int flag=1;
    int k = v.size();
    for(int i=1;i<=k;i++) {
        for(int j=0;j<8192;j++) {
            mem[flag][j] = (mem[flag^1][j]*(1+(a[v[i-1]])/2))%mod + (mem[flag^1][j^v[i-1]]*((a[v[i-1]]+1)/2))%mod;
            if(mem[flag][j]>=mod)
                mem[flag][j]%=mod;
        }
        flag = flag^1; //save memeory

    }
    long long ans=0;
    long long res=0;
    for(int i=1;i<8192;i++) {
        if(prime[i]){

            res+= mem[flag^1][i];
            res%=mod;
        }
    }
    cout << res << endl;
*/