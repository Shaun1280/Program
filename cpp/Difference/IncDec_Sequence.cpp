#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
//https://www.luogu.com.cn/blog/user48611/poetize6-incdec-sequence
typedef long long LL;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
} 
LL Arr[MAXN], dif[MAXN];
LL p, q;
int main(){
    int n;
    n = read();
    for(int i = 1; i <= n; i++) {
        Arr[i] = read(), dif[i] = Arr[i] - Arr[i - 1];
        if(i > 1 && dif[i] > 0) p += dif[i];
        if(i > 1 && dif[i] < 0) q -= dif[i];
    }
    cout << max(p, q) << endl << abs(p - q) + 1 << endl;
    return 0;
}