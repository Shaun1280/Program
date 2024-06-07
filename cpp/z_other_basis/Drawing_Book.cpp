#include<bits/stdc++.h>
using namespace std;
int n,p;
int count_start(0);
int count_end(0);
int main(){
    scanf("%d",&n);
    scanf("%d",&p);
    if(n%2==0){
        if(p%2==0) count_start=p/2, count_end=(n-p)/2;
        else count_start=(p-1)/2, count_end=(n-p+1)/2;
    }
    else{
        if(p%2==0) count_start=(p)/2, count_end=(n-p-1)/2;
        else count_start=p/2, count_end=(n-p)/2;
    }
    //std::ios::sync_with_stdio(false);
    cout<<( (count_start<count_end) ? count_start:count_end);
    return 0;
}