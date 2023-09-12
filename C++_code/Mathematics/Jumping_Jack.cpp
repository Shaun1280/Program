#include<bits/stdc++.h>
using namespace std;
int main(){
    int x, cnt(0);
    cin >> x;
    if(x < 0) x = -x;
    for(int i = 1, dis = 1; x && !cnt; i++, dis += i)
        if(dis == x || (dis > x && ! ((dis - x) % 2)))
            cnt = i;
    cout << cnt;
    return 0;
}