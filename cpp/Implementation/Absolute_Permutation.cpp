#include<bits/stdc++.h>
/*
Logic of the question: how can I permute [1,...,n] so that each number is exactly +-k from its original position?

If k == 0, then just leave everything alone.

If k > 0, then obviously 1 goes to 1+k; 
so ask: "What must go to 1?" 
Since there is no smaller # to go up to 1, the answer is 1+k, which can go down to 1.

This begs the question: what about numbers between 1 and 1+k, i.e., [2,...,k]? 
They must go up to [2+k,...,k+k] (note k+k == 2*k), which in turn must go down to [2,...,k].

This results in the crux: n must be a multiple of 2*k, so ((n % (2*k)) == 0). Then you just take it in 2*k chunks.

If those test fail, then you can't do it.

Now just put the algorithm into source code.
*/
using namespace std; 
int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int k;
        cin >> n >> k;
        int temp = k;
        if(k == 0){
            for(int i = 1; i <= n; i++){
                cout << i << " ";
            }
        }else if((n % (2*k)) == 0){
            for(int i = 1; i <= n; i++){
                cout << i + temp << " ";
                if(i % k == 0){
                    temp = temp * -1;
                }
            }        
        }else{
            cout << -1;
        }
        cout << endl;
    }
    return 0;
}