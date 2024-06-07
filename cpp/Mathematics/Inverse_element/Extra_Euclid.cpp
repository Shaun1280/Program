#include<bits/stdc++.h>
typedef long long LL;
//https://www.luogu.com.cn/problem/CF7C
//CF7C Line
using namespace std;
LL a, b, c;
void ex_gcd(LL a, LL b, LL &x , LL &y){
    if(!b){
        x = 1, y = 0;
        return;
    }
    ex_gcd(b, a % b, y, x), y -= a / b * x;
    //ex_gcd(b, a % b, x, y)
    //LL X = x, Y = y;
    //x = Y, y = X - (a / b) * Y;
} 
int main(){
    std::ios::sync_with_stdio(false); 
    cin >> a >> b >> c;
    LL x = 0, y = 0, gcd;
    c = -c;
    ex_gcd(a, b, x, y); //ax + by = gcd(a, b);
    gcd = a * x + b * y; //gcd(a, b)
    if(c % gcd != 0) { //有整数解的充要条件：c % gcd(a, b) = 0
        puts("-1");
        return 0;
    }
    x = c / gcd * x, y = c / gcd * y; 
    cout << x << " " << y << endl;
    return 0;
}