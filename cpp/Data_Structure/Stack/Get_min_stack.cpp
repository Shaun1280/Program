#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
typedef long long LL;
using namespace std;
int tot, n, cnt;
string opt;
stack<int>s, minStack;
int main(){
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    while (cin >> opt) {
        if (opt == "add") {
            cin >> n;
            if (s.empty()) s.push(n), minStack.push(n);
            else s.push(n), minStack.push(min(minStack.top(), n));
        }
        if (opt == "del") s.pop(), minStack.pop();
        if (opt == "ask") cout << "min_element:" << minStack.top() << endl;
    }
	return 0;
}