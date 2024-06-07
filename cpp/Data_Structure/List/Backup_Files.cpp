#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3620 P3620 [APIO/CTSC 2007]数据备份
using namespace std;
using LL = long long;

constexpr int MAXN = 1e5 + 5;
constexpr LL INF = 1e18;

LL n, k, dis[MAXN], ans, cnt;

struct ListNode {
    ListNode() = default;
    bool operator<(const ListNode &other) const {
        return this->data == other.data ? this->id > other.id : this->data > other.data;
    }
    ListNode *prev = NULL, *next = NULL, *cur = NULL;
    LL data = 0, id = -1;
};
map<int, bool> deleted;

struct List {
    List() { //构造函数
        this->head = new ListNode(), this->tail = new ListNode();
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    ListNode *insert(LL data) { //插入值，返回节点指针
        ListNode *cur = new ListNode();
        cur->data = data, cur->id = cnt++, cur->cur = cur;
        tail->prev->next = cur, cur->prev = tail->prev;
        cur->next = tail, tail->prev = cur;
        return cur;
    }

    ListNode *erase(ListNode *cur) { //删除节点，返回新节点指针
        LL data = cur->prev->data + cur->next->data - cur->data;
        ListNode *newListNode = new ListNode();
        newListNode->cur = newListNode;
        newListNode->data = data, newListNode->id = cnt++;

        ListNode *prev = cur->prev, *next = cur->next;
        prev->prev->next = newListNode, newListNode->prev = prev->prev;
        next->next->prev = newListNode, newListNode->next = next->next;

        deleted[prev->id] = deleted[next->id] = deleted[cur->id] = true;
        return newListNode;
    }

    ~List() {}
    ListNode *head = NULL, *tail = NULL;
} lst;

priority_queue<ListNode> q;
inline void calcLen(int tot = 0) {
    while (!q.empty() && tot < k) {
        ListNode* cur = q.top().cur;
        q.pop();
        if (deleted[cur->id]) continue;
        ans += cur->data, tot++;
        ListNode *newListNode = lst.erase(cur);
        q.push(*newListNode); //插入新节点
    }
}

int main() {
    scanf("%lld %lld", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%lld", dis + i);
    lst.insert(INF); //防止越界 简化边界判断
    for (int i = 0; i < n - 1; ++i) q.push(*lst.insert(dis[i + 1] - dis[i]));
    lst.insert(INF); //防止越界 简化边界判断
    calcLen(); //计算总长度
    printf("%lld\n", ans);
    return 0;
}