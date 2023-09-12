#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    std::ios::sync_with_stdio(false);
    cin >> T;
    cin.ignore();
    while (T--) {
        string s;
        getline(cin, s);
        for (int i = 0; i < s.length(); i += 2) cout << s[i];
        cout << " ";
        for (int i = 1; i < s.length(); i += 2) cout << s[i];
        cout << endl;
    }
    return 0;
}