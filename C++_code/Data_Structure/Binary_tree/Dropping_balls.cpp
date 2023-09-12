#include <bits/stdc++.h>
using namespace std;
// UVA679 小球下落 Dropping Balls https://www.luogu.com.cn/problem/UVA679
int testCase, D, I;
int main() {
    std::ios::sync_with_stdio(false);
    cin >> testCase;
    while (testCase--) {
        cin >> D >> I;
        int u = 1, n = (1 << D) - 1;
        while (true) {
            if (I & 1)
                u = u << 1, I = (I + 1) >> 1;
            else
                u = (u << 1) + 1, I = I >> 1;
            if (u > n) break;
        }
        cout << u / 2 << endl;
    }
    return 0;
}