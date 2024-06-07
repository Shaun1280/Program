#include <bits/stdc++.h>
#define PI acos(-1)
//hdu 2020-1 Leading robots
using namespace std;

constexpr int MAXN = 5e4 + 4;
constexpr double EPS = 1e-10;

int ts, n, st[MAXN], a[MAXN], stk[MAXN], top, tot, ans;

struct Robot {
    Robot() = default;
    Robot(int _st, int _a) : st(_st), a(_a) {}
    int st = -1, a = 0;
} robot[MAXN];

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> ts;
    while (ts--) {
        map<pair<int, int>, int> cnt;
        map<int, int> stMaxA;
        cin >> n;
        top = 0, tot = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> st[i] >> a[i];
            cnt[make_pair(st[i], a[i])]++; //记录是否有st、加速度a相同的机器人
            stMaxA[st[i]] = max(stMaxA[st[i]], a[i]); //记录起点对应最大的ai
            robot[++tot] = Robot(st[i], a[i]);
        }

        sort(robot + 1, robot + tot + 1, [](const Robot& a, const Robot& b) {
            return a.a == b.a ? a.st < b.st : a.a < b.a;
        }); //按加速度升序排序

        stk[++top] = 1;
        for (int i = 2; i <= tot; i++) { //单调栈
            while (top && robot[i].st > robot[stk[top]].st) top--;
            while (top > 1) {
                long long a1 = robot[stk[top]].st - robot[i].st;
                long long b1 = robot[i].a - robot[stk[top]].a;

                long long a2 = -(robot[stk[top]].st - robot[stk[top - 1]].st);
                long long b2 = -(robot[stk[top - 1]].a - robot[stk[top]].a);
                if (a1 * b2 <= a2 * b1) top--;
                else break;
            }
            stk[++top] = i;
        }

        for (int i = 1; i <= top; i++) {
            auto rob = robot[stk[i]];
            if (rob.a < stMaxA[rob.st]) continue; //小于起点st位置的最大加速度 跳过
            if (cnt[make_pair(rob.st, rob.a)] == 1) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}