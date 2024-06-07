#include<bits/stdc++.h>
/*https://www.luogu.com.cn/problem/UVA1328
UVA1328 Perio
**/
const int MAXN = 1e6 + 6;
using namespace std;
int n, nxt[MAXN], testCase;
char s[MAXN];
inline void calc_next(){
    nxt[1] = 0;
    for(int i = 2, j = 0; i <= n; i++){
        while(j > 0 && s[i] != s[j + 1]) j = nxt[j];
        if(s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }
}
int main(){
    while(cin >> n && n){
        scanf("%s", s + 1);
        calc_next();
        printf("Test case #%d\n", ++testCase);
        for(int i = 2; i <= n; i++){
            if(i % (i - nxt[i]) == 0 && i / (i - nxt[i]) > 1)
                printf("%d %d\n", i, i / (i - nxt[i]));
        }
        putchar('\n');
    }
    return 0;
}