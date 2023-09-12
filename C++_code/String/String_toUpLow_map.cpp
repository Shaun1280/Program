#include <bits/stdc++.h>
using namespace std;
map<char, int> Tot;
bool pangram = true;
int main() {
    string s;
    getline(cin, s);
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    for (char c = 'a'; c <= 'z'; c++) Tot[c] = 0;
    for (auto c : s) Tot[c]++;
    for (char c = 'a'; c <= 'z'; c++)
        if (Tot[c] < 1) pangram = false;
    cout << (pangram ? "pangram" : "not pangram");
    return 0;
}