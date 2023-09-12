#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int maxn=1e5+5;
struct Student{
    int val;
    bool top=false,button=false;
};
Student S[maxn];
int n;
LL cnt[maxn];
inline bool Special(int &id){
    if(S[id].val==S[id+1].val&&S[id].val==S[id-1].val) return true;
    return false;
}
inline void Scan(int &pos){
    int left_p=pos, right_p=pos;
    if(pos!=0&&pos!=n+1) cnt[pos]=max(1ll,cnt[pos]);
    if(pos==0) cnt[pos+1]=max(1ll,cnt[pos+1]);
    if(pos==n+1) cnt[pos-1]=max(1ll,cnt[pos-1]);
    while(true){
        right_p++;
        if(right_p==n+2||right_p==n+1) break;
        if(S[right_p].val==S[right_p-1].val) max(1ll,cnt[right_p]);
        if(S[right_p].val!=S[right_p-1].val) cnt[right_p]=max(cnt[right_p], cnt[right_p-1]+1);
        if(right_p==n||S[right_p].top) break;
    }
    while(true){
        left_p--;
        if(left_p==-1||left_p==0) break;
        if(S[left_p].val==S[left_p+1].val) cnt[left_p]=max(1ll,cnt[left_p]);
        if(S[left_p].val!=S[left_p+1].val) cnt[left_p]=max(cnt[left_p], cnt[left_p+1]+1);
        if(left_p==1||S[left_p].top) break;
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>S[i].val;
    memset(cnt,0,sizeof(cnt));
    S[0].val=0, S[n+1].val=0, S[0].button=true, S[n+1].button=true;
    for(int i=1;i<=n;i++){
        int now=S[i].val;
        if(now<=S[i-1].val&&now<=S[i+1].val&&(!Special(i))) S[i].button=true;
        if(now>=S[i-1].val&&now>=S[i+1].val&&(!Special(i))) S[i].top=true;
    }
    for(int i=0;i<=n+1;i++) if(S[i].button) Scan(i);
    for(int i=2;i<=n;i++) if(S[i].val==S[i-1].val) cnt[i]=max(1ll,(cnt[i]));
    LL sum=0;
    for(int i=1;i<=n;i++) sum+=cnt[i];
    cout<<sum;
    return 0;
}
/*
int main() {
    int n;
    cin >> n;
    vector<int> r(n); // children ratings
    vector<int> c(n); // candies allocated to each child
    
    // take in r[] and parse left to right
    int numcandies=1; // num of candies to give
    c[0]=1;
    cin >> r[0];
    for (int i=1;i<n;i++) {
        cin >> r[i];
        if (r[i]>r[i-1]) numcandies++;
        else if (r[i]<=r[i-1]) numcandies=1;
        c[i]=numcandies;
    }

    // 2nd parse right to left and accumulate total
    numcandies=1;
    long total=c[n-1];
    for (int i=n-2;i>=0;i--) {
        if (r[i]>r[i+1]) numcandies++;
        else if (r[i]<=r[i+1]) numcandies=1;
        c[i]=(numcandies>c[i]?numcandies:c[i]); //use the larger of 2 parses
        total+=c[i];
    }    
    
    cout << total;
    return 0;
}
  for (int i = 1; i < n; i++){
        arr1[i] = arr[i] <= arr[i-1] ? 1 : arr1[i-1] + 1;
        arr2[n-1-i] = arr[n-1-i] <= arr[n-i] ? 1 : arr2[n-i] + 1;
    }
*/ 