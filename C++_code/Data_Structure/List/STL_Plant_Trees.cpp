#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1792 P1792 [国家集训队]种树
using namespace std;

constexpr int MAXN = 2e5 + 5;

int n, m, a[MAXN], ans, cnt;

struct ListNode {
    ListNode() = default;
    ListNode(int _data, int _id) : data(_data), id(_id) {}
    bool operator<(const ListNode &other) const {
        return this->data == other.data ? this->id < other.id : this->data < other.data;
    }
    int data = 0, id = -1;
    list<ListNode>::iterator itr;
};
list<ListNode> lst;
priority_queue<ListNode> q;
map<int, bool> deleted;

inline void calcA(int tot = 0) {
    while (!q.empty() && tot < m) {
        auto cur = q.top();
        q.pop();
        if (deleted[cur.id]) continue;
        ans += cur.data, tot++;
        if (tot == m) break;
        //将相邻三个节点删除 并用新节点替换 带反悔贪心
        int data(0);
        auto itr = --cur.itr;
        if (itr == lst.end()) --itr;

        data += itr->data, deleted[itr->id] = true, itr = lst.erase(itr);
        if (itr == lst.end()) ++itr;

        data -= itr->data, deleted[itr->id] = true, itr = lst.erase(itr);
        if (itr == lst.end()) ++itr;

        if (itr == lst.end()) cout << "err" << endl;
        data += itr->data, deleted[itr->id] = true, itr = lst.erase(itr);
        //将相邻三个节点删除 并用新节点替换 带反悔贪心
        auto newNode = ListNode(data, cnt++);
        newNode.itr = lst.insert(itr, newNode);
        q.push(newNode);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    if (n / 2 < m) return printf("Error!\n"), 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        auto newNode = ListNode(a[i], cnt++);
        newNode.itr = lst.insert(lst.end(), newNode); //末尾插入
        q.push(newNode); //加入优先队列
    } 
    calcA(); //计算美观度sigma_Ai
    printf("%d\n", ans);
    return 0;
}