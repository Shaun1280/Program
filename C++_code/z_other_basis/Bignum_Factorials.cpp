#include <bits/stdc++.h>
const int maxn = 100000;
using namespace std;
int n, Big_num[maxn], add, position = maxn;
int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n;
    memset(Big_num, 0, sizeof(Big_num));
    Big_num[1] = 1;
    for (int Num = 2; Num <= n; Num++)
    {
        add = 0;
        for (int pos = 1; pos <= maxn; pos++)
        {
            Big_num[pos] = Big_num[pos] * Num + add;
            add = Big_num[pos] / 10;
            Big_num[pos] = Big_num[pos] % 10;
        }
    }
    while (Big_num[position] == 0)
    {
        position--;
    }
    for (int pos = position; pos >= 1; pos--)
        cout << Big_num[pos];
    return 0;
}