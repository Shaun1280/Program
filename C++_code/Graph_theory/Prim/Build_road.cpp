#include <bits/stdc++.h>
/*prime n^2 n < 5000 memory < 128MB*/
#define Inf 0x7fffffff
using namespace std;
struct node {
    int x, y;
} *point = NULL;
double *dis = NULL;
bool *in_tree = NULL;
int n, cur;
inline double calculate_dis(int x1, int x2, int y1, int y2) {
    return sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
}
inline double prime(double ans) {
    for (int i = 1; i < n; i++) dis[i] = Inf;
    for (int cnt = 0; cnt < n; cnt++) {
        double min_dis = Inf;
        for (int i = 0; i < n; i++)
            if (!in_tree[i] && dis[i] < min_dis) min_dis = dis[i], cur = i;
        ans += min_dis, in_tree[cur] = true;
        for (int i = 0; i < n; i++) {
            double d = calculate_dis(point[cur].x, point[i].x, point[cur].y,
                                     point[i].y);
            if (!in_tree[i] && d < dis[i]) dis[i] = d;
            //更新生成树点到非生成树点i的最小距离
        }
    }
    return ans;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n;
    point = (node *)malloc(n * sizeof(node));
    dis = (double *)malloc(n * sizeof(double));
    in_tree = (bool *)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) cin >> point[i].x >> point[i].y;
    printf("%.2f", prime(.0));
    return 0;
}