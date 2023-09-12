#include<bits/stdc++.h>
/*prime coin_change
The victim has an infinite supply of bricks of 
size 4x1 and 1x4 in her house.
calculate the total number of ways 
in which the bricks can be arranged.
calculate the number of prime numbers from 0-ways
*/
const int MAXN=41;
const int MAXP=1e6+1;
using namespace std;
int T, dp[MAXN], n, isprime[MAXP];
vector<int>prime;
inline int Euler_prime(int x){
    isprime[0]=false, isprime[1]=false;
    for(int i=2; i<=x; i++){
        if(isprime[i]) prime.push_back(i);
        for(int j=0; j<prime.size(); j++){
            if( i*prime[j] > x ) break;
            isprime[i*prime[j]]=false;
            if( !(i % prime[j]) ) break;
        }
    }
    return prime.size();
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n;
        memset(dp,0,sizeof(dp));
        memset(isprime,1,sizeof(isprime));
        prime.clear();
        dp[0]=1;
        for(int i=1; i<=n; i++){
            dp[i]+=dp[i-1];
            if(i>=4) dp[i]+=dp[i-4];//
        }//similar to coin change problem
        cout<<Euler_prime(dp[n])<<endl;//get_prime_num
    }
    return 0;
}