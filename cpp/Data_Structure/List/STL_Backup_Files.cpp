#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3620 P3620 [APIO/CTSC 2007]数据备份
using namespace std;
using LL = long long;

constexpr int MAXN = 1e5 + 5;
constexpr LL INF = 1e15;

LL n, k, dis[MAXN], ans, cnt;

struct ListNode {
    ListNode() = default;
    ListNode(LL _data, LL _id) : data(_data), id(_id) {}
    bool operator<(const ListNode &other) const {
        return this->data == other.data ? this->id > other.id : this->data > other.data;
    }
    LL data = INF, id = -1;
    list<ListNode>::iterator itr;
};
list<ListNode> lst;
priority_queue<ListNode> q;
map<LL, bool> deleted;

inline void calcLen(int tot = 0) {
    while (!q.empty() && tot < k) {
        auto cur = q.top();
        q.pop();
        if (deleted[cur.id]) continue;
        ans += cur.data, tot++;
        //删除
        auto itr = cur.itr;
        --itr; //得到cur->prev的迭代器
        LL data = itr->data; deleted[itr->id] = true, itr = lst.erase(itr);
        data -= itr->data, deleted[itr->id] = true, itr = lst.erase(itr);
        data += itr->data, deleted[itr->id] = true, itr = lst.erase(itr);
        //删除
        auto newNode = ListNode(data, cnt++);
        newNode.itr = lst.insert(itr, newNode);
        q.push(newNode);
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> dis[i];
    lst.emplace_back(ListNode(INF, cnt++)); //防止越界 简化边界判断
    for (int i = 0; i < n - 1; ++i) {
        auto newNode = ListNode(dis[i + 1] - dis[i], cnt++);
        newNode.itr = lst.insert(lst.end(), newNode); //末尾插入
        q.push(newNode);
    }
    lst.emplace_back(ListNode(INF, cnt++)); //防止越界 简化边界判断
    calcLen();
    cout << ans << endl;
    return 0;
}