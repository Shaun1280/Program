#include <bits/stdc++.h>
using namespace std;
struct node
{
    int S, val;
} *House = NULL;
int *sum = NULL, *pre = NULL, *nxt = NULL;
inline bool cmp(const node &a, const node &b)
{
    return a.val > b.val;
}
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    sum = (int *)malloc(n * sizeof(int));
    pre = (int *)malloc(n * sizeof(int));
    nxt = (int *)malloc(n * sizeof(int));
    House = (node *)malloc(n * sizeof(node));
    for (int i = 0; i < n; i++)
        cin >> House[i].S;
    for (int i = 0; i < n; i++)
        cin >> House[i].val;
    sort(House, House + n, cmp); //Sort array a in descending order
    sum[0] = House[0].val;
    pre[0] = 2 * House[0].S, nxt[n - 1] = 2 * House[n - 1].S + House[n - 1].val;
    //Initialize
    for (int i = 1; i < n; i++)
        sum[i] = sum[i - 1] + House[i].val, // get_prefix_sum
            pre[i] = max(pre[i - 1], 2 * House[i].S);
    //get max 2*S[i] before
    for (int i = n - 2; i >= 0; i--)
        nxt[i] = max(nxt[i + 1], 2 * House[i].S + House[i].val);
    printf("%d\n", max(sum[0] + pre[0], nxt[0]));
    //delect the minimum element:a[0],
    //and add one maximum element 2*S+a;
    for (int i = 1; i < n; i++)
        printf("%d\n", max(sum[i] + pre[i], sum[i - 1] + nxt[i]));
    //delect the minimum element and one maximum element 2*S+a;
    free(House), free(nxt), free(pre);
    return 0;
}
/*#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 100010;
int n, s[maxn], a[maxn], curr, maxL, ans;
struct Node
{
    int i, v;
    bool operator<(const Node &a) const { return v < a.v; } //大根堆
} node, maxR;
priority_queue<Node> qR;
priority_queue<int> qL; //默认大根堆
int main()
{

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", s + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        node.i = i, node.v = 2 * s[i] + a[i], qR.push(node);
    for (int x = 1; x <= n; x++) //取左或者取右
    {
        maxL = maxR.v = 0;
        if (!qL.empty())
            maxL = qL.top();
        while (!qR.empty() && qR.top().i <= curr)
            qR.pop();
        if (!qR.empty())
            maxR = qR.top();
        if (maxL < maxR.v - 2 * s[curr]) //当两者相等时取哪边都一样
        {
            ans += maxR.v - 2 * s[curr];
            curr = maxR.i;
            for (int k = curr + 1; k < maxR.i; k++)
                qL.push(a[k]);
            //第一次选了curr，则第二次在第一次的基础上再选出下一个。
            即要么选择curr左边的a，要么选择curr右边的b
            qR.pop();
        }
        else
            ans += maxL, qL.pop();
        printf("%d\n", ans);
    }
    return 0;
}*/
