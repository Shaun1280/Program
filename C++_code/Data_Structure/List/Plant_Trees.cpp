#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1792 P1792 [国家集训队]种树
using namespace std;

constexpr int MAXN = 2e5 + 5;

int n, m, a[MAXN], cnt, ans;

struct ListNode {
    ListNode() = default;
    bool operator<(const ListNode& other) const {
        return this->data == other.data ? this->id < other.id : this->data < other.data;
    }
    ListNode *prev = NULL, *next = NULL, *cur = NULL;
    int data = 0, id = -1;
};
map<int, bool> deleted;
priority_queue<ListNode> q;

struct CycleList {
    CycleList() = default;

    ListNode* insert(int data, int id) {
        auto newNode = new ListNode();
        newNode->data = data, newNode->id = id, newNode->cur = newNode;
        if (head == NULL) head = tail = newNode;
        newNode->prev = tail, tail->next = newNode, tail = newNode;
        tail->next = head, head->prev = tail;
        return newNode;
    }

    ListNode* erase(ListNode* cur) {
        auto prev = cur->prev, next = cur->next;
        int data = prev->data + next->data - cur->data;
        deleted[prev->id] = deleted[cur->id] = deleted[next->id] = true;
        
        auto newNode = new ListNode();
        newNode->data = data, newNode->id = cnt++, newNode->cur = newNode;
        prev->prev->next = newNode, newNode->prev = prev->prev;
        next->next->prev = newNode, newNode->next = next->next;
        return newNode;
    }

    ListNode *head = NULL, *tail = NULL;
} lst;

void calcA(int tot = 0) {
    while (!q.empty() && tot < m) {
        auto cur = q.top();
        q.pop();
        if (deleted[cur.id]) continue;
        ans += cur.data, tot++;
        auto newNode = lst.erase(cur.cur);
        q.push(*newNode);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    if (n / 2 < m) return printf("Error!\n"), 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        auto newNode = i == n - 1 ? lst.insert(a[i], cnt++) : lst.insert(a[i], cnt++);
        q.push(*newNode);
    }
    calcA();
    printf("%d\n", ans);
    return 0;
}