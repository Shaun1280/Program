#include <bits/stdc++.h>
//询问1个点能与给定的点组成多少直角三角形 hash
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2003, MOD = 1e9 + 7;

int n, q;
pair<int, int> p[MAXN], a[MAXN];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pair_hash {
    inline size_t operator()(const pair<int, int>& p) const {
        return p.first * p.second + p.first + p.second;
    }
};

unordered_map<pair<int, int>, int, pair_hash> mp[MAXN], mq[MAXN];

pair<int, int> process(const pair<int, int>& tmp) {
    if (tmp.first == 0) return {0, 1};
    else if (tmp.second == 0) return {1, 0};
    else {
        int gcd = __gcd(tmp.first, tmp.second);
        return {tmp.first / gcd, tmp.second / gcd};
    }
}

void initp() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            int dx = p[j].first - p[i].first;
            int dy = p[j].second - p[i].second;
            mp[i][process({dx, dy})]++;
        }
    }
}

int main() {
    boost;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
    initp();
    for (int i = 1; i <= q; i++) {
        cin >> a[i].first >> a[i].second;
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            int dx = p[j].first - a[i].first;
            int dy = p[j].second - a[i].second;
            auto tmp = process({dx, dy});
            if (mp[j].count({-tmp.second, tmp.first}))
                ans += mp[j][{-tmp.second, tmp.first}];
            if (mp[j].count({tmp.second, -tmp.first}))
                ans += mp[j][{tmp.second, -tmp.first}];
        }
        // 0 // 2
        for (int j = 1; j <= n; j++) {
            int dx = p[j].first - a[i].first;
            int dy = p[j].second - a[i].second;
            auto tmp = process({dx, dy});
            mq[i][tmp]++;
        }

        for (int j = 1; j <= n; j++) {
            int dx = p[j].first - a[i].first;
            int dy = p[j].second - a[i].second;
            auto tmp = process({dx, dy});
            if (mq[i].count({-tmp.second, tmp.first}))
                ans += mq[i][{-tmp.second, tmp.first}]; //有方向
        }

        cout << ans << "\n";
    }
    return 0;
}