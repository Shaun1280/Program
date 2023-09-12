#include <bits/stdc++.h>
/*P1016 旅行家的预算*/
const int MAXN = 10;
using namespace std;
double D, C, D2, cost_start;
int N, Index;
/*
1如果可以直达下一个油价更低的节点就加满够到此节点的油，开过去（中间的不用管）
2如果不能直达就加满油（因为中转节点的油更贵要少加），开到能到范围内油价最低的加油站
*/
struct node{
    double pos, cost;
    friend bool operator < (const node &a, const node &b){
        return a.pos < b.pos;
    }
}tmp, oil[10];
double max_car_dis, total_cost, cur_oil = .0;
inline void find(int p){ //不能直接从起点到终点的情况
    if(p == N + 1) return;
    tmp.pos = oil[p].pos + max_car_dis;
    int next = upper_bound(oil + 1, oil + N + 2, tmp)- oil - 1;
    for(int i = p + 1; i <= next && i <= N + 1; i++)
        if(oil[i].cost < oil[p].cost){
            /*寻找油价低于当前起点的点*/
            total_cost += ((oil[i].pos - oil[p].pos) / D2 - cur_oil) * oil[p].cost; 
                //计算花费 要的油量为 dis/D2 - 当前油量
            if(p != 0)  cur_oil -= (oil[i].pos - oil[p].pos) / D2; 
                //计算到达下一个点的油量
            find(i);  //情况1    
            return;
        }
    tmp.cost = 501;
    for(int i = p + 1; i <= next && i <= N + 1; i++)
        if(oil[i].cost <= tmp.cost) 
            tmp.pos = oil[i].pos, tmp.cost = oil[i].cost , Index = i;
    /*寻找后面价格最低的点*/
    total_cost += ( C - cur_oil ) * oil[p].cost;  
    /*所加油量为总容量 - 当前油量 */
    cur_oil = C - ((tmp.pos - oil[p].pos) / D2); // 计算到达下一个点的油量
    find(Index); //情况2
}
int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%lf%lf%lf%lf%d", &D, &C, &D2, &cost_start, &N);
    max_car_dis = C * D2;
    oil[0].pos = 0, oil[0].cost = cost_start, oil[N + 1].pos = D;
    for (int i = 1; i <= N; i++)
        scanf("%lf%lf", &oil[i].pos, &oil[i].cost);
    sort(oil + 1, oil + N + 1);
    for (int i = 1; i <= N; i++){
        if (oil[i].pos - oil[i - 1].pos > max_car_dis || D - oil[N].pos > max_car_dis)
        {
            printf("No Solution");
            return 0; //特判 无法到达
        }
    }
    find(0);
    printf("%.2f", total_cost);
    return 0;
}