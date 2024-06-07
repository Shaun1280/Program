#include <bits/stdc++.h>

const int MAXN = 1e5 + 1;

using namespace std;

int T, n, dp_arr[MAXN], max_arr, max_seq, dp_seq[MAXN][1];
vector<int> Arr;

int main() {
    std::ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        memset(dp_arr, -0x7f, sizeof(dp_arr));
        memset(dp_seq, -0x7f, sizeof(dp_seq));
        Arr.clear();
        max_arr = -0x7fffffff, max_seq = -0x7fffffff;
        cin >> n;
        for (int i = 0, tmp; i < n; i++) cin >> tmp, Arr.push_back(tmp);
        /*boundary condition*/
        dp_arr[0] = Arr[0], dp_seq[0][1] = Arr[0];
        for (int i = 1; i < n; i++)
            /**************get subarray*************************/
            dp_arr[i] = max(dp_arr[i - 1] + Arr[i], Arr[i]),
            /**************get subsequence*************************/
                dp_seq[i][0] = max(dp_seq[i - 1][1], dp_seq[i - 1][0]),
            dp_seq[i][1] = max(Arr[i] /*!*/, max(dp_seq[i - 1][1] + Arr[i],
                                                 dp_seq[i - 1][0] + Arr[i]));
        /*get max_arr max_seq*/
        for (int i = 0; i < n; i++)
            max_arr = max(max_arr, dp_arr[i]),
            max_seq = max(dp_seq[i][0], dp_seq[i][1]);
        /* print*/
        printf("%d %d\n", max_arr, max_seq);
    }
    return 0;
}