#include <bits/stdc++.h>
/*sliding window*/
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') f = (ch == '-') ? -1 : 1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
// http://www.cplusplus.com/reference/deque/deque/
/*mydeque.push_back(1); //Pushes element at the end
mydeque.push_front(2); //Pushes element at the beginning
Pop

mydeque.pop_back(); //Pops element from the end
mydeque.pop_front(); //Pops element from the beginning*/
deque<int> q;
vector<int> vec, num;

int testcase, n, k, nn;
int main() {
    testcase = read();
    while (testcase--) {
        n = read(), k = read();
        q.clear(), num.clear(), vec.clear();
        for (int i = 1; i <= n; i++) nn = read(), num.push_back(nn);
        for (int i = 0; i < n; i++) {
            if (q.front() <= i - k) q.pop_front();
            while (!q.empty() && num[q.back()] < num[i]) q.pop_back();
            q.push_back(i);
            if (i >= k - 1) vec.push_back(q.front());
        }
        int length = vec.size();
        for (int i = 0; i < length; i++) printf("%d ", num[vec[i]]);
        printf("\n");
    }
    return 0;
}
