#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/SP16254
//SP16254 RMID2 - Running Median Again
int tmp, testCase;
priority_queue<int, vector<int>, greater<int> >q2; //small top
priority_queue<int, vector<int>, less<int> >q1; //
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> testCase;
    for(int i = 1; i <= testCase; i++){
        while(~scanf("%d", &tmp)){
            if(tmp == 0) {
                while(!q1.empty()) q1.pop();
                while(!q2.empty()) q2.pop();
                cout << endl;
                continue;
            }
            if(tmp == -1){
                int Min;
                if(q1.size() == q2.size()){
                    if(q1.top() <= q2.top()) Min = q1.top(), q1.pop();
                    else Min = q2.top(), q2.pop();       
                }
                else if(q1.size() + 1 == q2.size()) Min = q2.top(), q2.pop();
                else if(q1.size() == q2.size() + 1) Min = q1.top(), q1.pop();   
                printf("%d\n", Min);
                continue;
            }
            if(q1.empty()) 
                q1.push(tmp);
            else{
                if(tmp <= q1.top()) q1.push(tmp);
                else q2.push(tmp);
                if(q1.size() > q2.size() + 1) q2.push(q1.top()), q1.pop();
                else if(q1.size() + 1< q2.size()) q1.push(q2.top()), q2.pop();
            }
        }
    }
    return 0;
}