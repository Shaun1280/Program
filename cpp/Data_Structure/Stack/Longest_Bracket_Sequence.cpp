#include<bits/stdc++.h>
/*longest Regular Bracket Sequence*/
const int MAXN = 1e6 + 1;;
using namespace std;
int Stack[MAXN], C[MAXN], cnt[MAXN], top;
string s;
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    /*
    C[i] 以i位 close blacket 为结尾的长度
    */
    cin >> s;
    for(int i = 0; i < (signed int)s.size(); i++){
        if(s[i] == '(') Stack[++top] = i;
        else if(top){ // s[i] == ')'
            C[i] = i - Stack[top] + 1 + C[Stack[top] - 1];
            /*  (())(()  (())()  ->  加上上符合条件的能相连的close blacket对应的长度 */
            cnt[C[i]]++;
            top --;
        }
    }
    for(int i = s.size(); i >=0; i--)
        if(cnt[i]){
            printf("%d %d", i, cnt[i]);
            return 0;
        }
    printf("0 1");
    return 0;
}