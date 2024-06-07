#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/11257/A
// 链表 + 优先队列维护 面积关于时间的二次系数
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define double long double 

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;
constexpr double EPS = 1e-10;

struct Vec2 {
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {}

    friend inline Vec2 intersect(const Vec2&, const Vec2&, const Vec2&, const Vec2&);

    friend inline bool operator<(const Vec2& a, const Vec2& b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    friend inline Vec2 operator+(const Vec2& a, const Vec2& b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }

    friend inline double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  
    }

    friend inline Vec2 operator*(const Vec2& a, double num) {
        return Vec2(a.x * num, a.y * num);
    }

    friend inline Vec2 operator/(const Vec2& a, double num) {
        return Vec2(a.x / num, a.y / num);
    }

    friend inline double norm(const Vec2& a) {
        return sqrtl(a.x * a.x + a.y * a.y);
    }

    friend inline double normSquare(const Vec2& a) {
        return a.x * a.x + a.y * a.y;
    }
    friend inline Vec2 rotate(const Vec2& a, double theta) {
        double sin0 = sinl(theta), cos0 = cosl(theta); // sinl sin
        return Vec2(cos0 * a.x - sin0 * a.y, sin0 * a.x + cos0 * a.y);
    }

    double x = 0, y = 0;
};

/*@return intersect point of two Seg*/
inline Vec2 intersect(const Vec2& s1, const Vec2& t1,
                        const Vec2& s2, const Vec2& t2) {
    double ratio = ((s1 - s2) * (t2 - s2)) / ((t2 - s2) * (t1 - s1));
    return s1 + (t1 - s1) * ratio;
}


struct coef { double ct2, ct, c; } coefs[MAXN]; // 二次系数

struct Ver {
    Ver() = default;
    Ver(Vec2 _v, int _id, Vec2 _speed = Vec2(0, 0)) : p(_v), id(_id), speed(_speed) {}
    Vec2 p, speed;
    int id;
};

struct QNode {
    QNode() = default;
    QNode(double _t, int _id, list<Ver>::iterator _itr) : t(_t), id(_id), itr(_itr) {}
    bool operator<(const QNode& other) const { return this->t > other.t; }

    double t;
    int id;
    list<Ver>::iterator itr;
};

int n, Q, tot;
pair<double, int> t[MAXN];
list<Ver> lst;

void update(int i, const Ver& vcur, const Ver& vnxt, double sign) {
    coefs[i].c += sign * (vcur.p.x * vnxt.p.y);
    coefs[i].ct += sign *(vcur.p.x * vnxt.speed.y + vnxt.p.y * vcur.speed.x);
    coefs[i].ct2 += sign * (vcur.speed.x * vnxt.speed.y);

    coefs[i].c -= sign * (vnxt.p.x * vcur.p.y);
    coefs[i].ct -= sign * (vnxt.p.x * vcur.speed.y + vcur.p.y * vnxt.speed.x);
    coefs[i].ct2 -= sign * (vnxt.speed.x * vcur.speed.y);
} // (x + ut, y + vt)

void init(priority_queue<QNode>& q) {
    list<Ver>::iterator itr, pre, nxt;
    for (itr = lst.begin(); itr != lst.end(); ++itr) {
        pre = itr, nxt = itr;
        if ((--pre) == lst.end()) --pre;
        if ((++nxt) == lst.end()) ++nxt;
        Ver& vcur = *itr, vpre = *pre, vnxt = *nxt;

        Vec2 v1 = vnxt.p - vcur.p, v2 = vpre.p - vcur.p; // 两直线
        double norm1 = norm(v1), norm2 = norm(v2);
        v1 = v1 / norm1, v2 = v2 / norm2; // 单位化求角平分线
        vcur.speed = (v1 + v2) / (v1 * v2); // 速度通过三角函数求 = 1 / sin0
    }
    for (itr = lst.begin(); itr != lst.end(); ++itr) {
        nxt = itr;
        if ((++nxt) == lst.end()) ++nxt;
        auto vcur = *itr, vnxt = *nxt;

        update(0, vcur, vnxt, 1.0); // 初始化系数

        Vec2 vcur2 = vcur.p + vcur.speed, vnxt2 = vnxt.p + vnxt.speed;
        Vec2 its = intersect(vcur.p, vcur2, vnxt.p, vnxt2);// 角平分线交点
        double tim = norm(its - vcur.p) / norm(vcur.speed);
        q.emplace(tim, itr->id, itr); // 放入优先队列
    }
}

void getCoefs() {
    priority_queue<QNode> q;
    unordered_map<int, bool> del;
    init(q);
    for (int i = 1; i <= Q; i++) {
        int id = t[i].second;
        double lim = t[i].first;
        coefs[id] = coefs[t[i - 1].second]; // t[0].second = 0
        list<Ver>::iterator itr, pre, nxt, nxtnxt;
        while (!q.empty() && q.top().t < lim + EPS && lst.size() > 3) {
            // error(id, q.top().t);
            itr = q.top().itr;
            int itrId = q.top().id;
            q.pop();

            if (del[itrId]) continue;

            pre = itr, nxt = itr;
            if ((--pre) == lst.end()) --pre;
            if ((++nxt) == lst.end()) ++nxt;
            nxtnxt = nxt;
            if ((++nxtnxt) == lst.end()) ++nxtnxt;

            Vec2 s1 = pre->p, t1 = itr->p;
            Vec2 s2 = nxtnxt->p, t2 = nxt->p;

            double cross = (t1 - s1) * (t2 - s2);
            if (fabs(cross) < EPS) { // 矩形收缩为 0
                lst.clear();
                coefs[id].c = coefs[id].ct = coefs[id].ct2 = 0;
                break;
            }

            update(id, *pre, *itr, -1);
            update(id, *itr, *nxt, -1);
            update(id, *nxt, *nxtnxt, -1); // 删除相邻三条边

            Vec2 its = intersect(s1, t1, s2, t2);
            del[itr->id] = true, del[nxt->id] = true;
            lst.erase(itr), lst.erase(nxt);

            Ver vnew = Ver(its, tot++);
            auto v1 = (*nxtnxt).p - vnew.p, v2 = (*pre).p - vnew.p;
            v1 = v1 / norm(v1), v2 = v2 / norm(v2);
            vnew.speed = (v1 + v2) / (v1 * v2);  // 速度通过三角函数求

            update(id, *pre, vnew, 1);
            update(id, vnew, *nxtnxt, 1);
            auto newitr = lst.insert(nxtnxt, vnew);

            s1 = vnew.p, t1 = vnew.p + vnew.speed;
            s2 = (*nxtnxt).p, t2 = (*nxtnxt).p + (*nxtnxt).speed;
            its = intersect(s1, t1, s2, t2);  // 角平分线交点
            double tim = norm(its - s1) / norm(vnew.speed);
            q.emplace(tim, newitr->id, newitr); // 新加节点

            del[pre->id] = true;
            s1 = (*pre).p, t1 = (*pre).p + (*pre).speed;
            s2 = vnew.p, t2 = vnew.p + vnew.speed;
            its = intersect(s1, t1, s2, t2);  // 角平分线交点
            tim = norm(its - s1) / norm(pre->speed);
            auto data = *pre;
            data.id = tot++;
            lst.erase(pre);
            pre = lst.insert(newitr, data);
            q.emplace(tim, pre->id, pre); // 修改节点 延迟删除
        }
        if (lst.size() < 3) coefs[id].c = coefs[id].ct = coefs[id].ct2 = 0;
        else if (lst.size() == 3) {
            double endt;
            while (!q.empty()) {
                double t = q.top().t;
                int itrId = q.top().id;
                itr = q.top().itr;
                q.pop();
                if (del[itrId]) continue;
                endt = t;
                break;
            }
            if (lim > endt) coefs[id].c = coefs[id].ct = coefs[id].ct2 = 0;
        }
    }
}

int main() {
    freopen("test.in", "r", stdin);
    boost;
    cout << setprecision(6) << fixed;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        double x, y;
        cin >> x >> y;
        lst.insert(lst.end(), Ver(Vec2(x, y), tot++)); // 末尾插入
    }
    cin >> Q;
    for (int i = 1; i <= Q; i++) cin >> t[i].first, t[i].second = i;
    sort(t + 1, t + Q + 1, [](const pair<double, int>& a, const pair<double, int>& b) {
        return a.first < b.first;
    });

    getCoefs();

    sort(t + 1, t + Q + 1, [](const pair<double, int>& a, const pair<double, int>& b) {
        return a.second < b.second;
    });

    for (int i = 1; i <= Q; i++) {
        // error(coefs[i].c, coefs[i].ct, coefs[i].ct2);
        double ti = t[i].first;
        cout << max((double)0.0, (coefs[i].c + coefs[i].ct * ti + coefs[i].ct2 * ti * ti) / 2.0) << "\n";
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */