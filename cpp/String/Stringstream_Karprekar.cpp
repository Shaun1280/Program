#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL p, q;
bool Range = false;
inline void Kaprekar(LL A) {
    string s_left, s_right, s;
    LL D, Left, Right;
    stringstream ss, ss_left, ss_right;
    ss << A, ss >> s, D = s.size();
    ss.clear(), s.clear();
    ss << (A * A), ss >> s;
    s_right = s.substr(s.size() - D, D);
    s_left = s.substr(0, s.size() - D);
    ss_left << s_left, ss_left >> Left;
    ss_right << s_right, ss_right >> Right;
    if (Left + Right == A) cout << A << " ", Range = true;
    if (A == q && !Range) cout << "INVALID RANGE";
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> p >> q;
    for (LL i = p; i <= q; i++) Kaprekar(i);
    return 0;
}