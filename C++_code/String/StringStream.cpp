#include <iostream>
#include <sstream>/*!*/
#include <vector>
const int N = 1e5 + 5;
int num;
using namespace std;
vector<int> integers;
/*stringstream ss("23,4,56");char ch;
int a, b, c;
ss >> a >> ch >> b >> ch >> c;  // a = 23, b = 4, c = 56
if(ss.fail()) break;
*/
int main() {
    string s;
    stringstream ss;
    cin >> s;
    ss.clear();
    ss.str(s);
    int n = s.size(), k = 0;
    char ch;
    for (int i = 0; i < n; i++)
        if (s[i] == ',') k++;
    for (int i = 0; i < k; i++) {
        ss >> num >> ch;
        integers.push_back(num);
    }
    ss >> num;
    integers.push_back(num);
    for (int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }

    return 0;
}
/*************************************************************************8*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parseInts(string str) {
    stringstream ss(str);
    vector<int> result;
    char ch;
    int tmp;
    while (ss >> tmp) {
        result.push_back(tmp);
        ss >> ch;
    }
    return result;
}
int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for (int i = 0; i < integers.size(); i++) cout << integers[i] << "\n";
    return 0;
}
