#include <bits/stdc++.h>

using namespace std;
using LL = long long;

string a, b;
int digitA[12], digitB[12];
LL dp[12][10];
int lenA, lenB;

inline LL calculateB(int highestB, LL cnt) {
    for (int i = lenB - 1; i >= 1; i--)
        for (int j = 1; j < 10; j++) cnt += dp[i][j];  //位数小于B
    for (int i = 1; i < (lenB == 1 ? highestB + 1 : highestB); i++)
        cnt += dp[lenB][i];                //位数等于B 最高位小于B
    for (int i = lenB - 1; i >= 1; i--) {  //位数等于B 最高i位 = B;
        for (int j = 0; j < (i == 1 ? digitB[i] + 1 : digitB[i]); j++)
            if (abs(digitB[i + 1] - j) >= 2) cnt += dp[i][j];
        if (abs(digitB[i + 1] - digitB[i]) < 2) break;
    }
    return cnt;
}

inline LL calculateA(int highestA, LL cnt) {
    for (int i = lenA - 1; i >= 1; i--)
        for (int j = 1; j < 10; j++) cnt += dp[i][j];  //位数小于A
    for (int i = 1; i < (lenA == 1 ? highestA + 1 : highestA); i++)
        cnt += dp[lenA][i];                //位数等于A 最高位小于A
    for (int i = lenA - 1; i >= 1; i--) {  //位数等于A 最高位 = A;
        for (int j = 0; j < (i == 1 ? digitA[i] + 1 : digitA[i]); j++)
            if (abs(digitA[i + 1] - j) >= 2) cnt += dp[i][j];
        if (abs(digitA[i + 1] - digitA[i]) < 2) break;
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> a >> b;
    stringstream s;
    LL tmpA;
    s << a, s >> tmpA, tmpA--, s.clear(), s << tmpA, s >> a;
    lenA = a.size(), lenB = b.size();
    for (int i = 0; i < lenA; i++) digitA[i + 1] = a[lenA - i - 1] - 48;
    for (int i = 0; i < lenB; i++) digitB[i + 1] = b[lenB - i - 1] - 48;
    for (int i = 0; i <= 9; i++) dp[1][i] = 1;
    for (int i = 2; i <= 10; i++) {
        for (int cur = 0; cur < 10; cur++) {
            for (int pre = 0; pre < 10; pre++)
                if (abs(cur - pre) >= 2) dp[i][cur] += dp[i - 1][pre];
        }
    }
    int highestA = digitA[lenA], highestB = digitB[lenB];
    // cout << a << endl;
    // cout << calculateB(highestB, 0) << endl;
    // cout << calculateA(highestA, 0) << endl;
    cout << calculateB(highestB, 0) - calculateA(highestA, 0);
    return 0;
}