/**
#include<bits/stdc++.h>

using namespace std;

vector<int> serviceLane(vector<int> width, vector<vector<int>> cases)
{
    vector<int> result;
    int start, end, min;
    for(auto i = 0; i < cases.size(); i++)
    {
        start = cases[i][0];
        end = cases[i][1];
        min = width[start];

        for(int j = start + 1 ; j <= end ; j++)
            if(width[j] < min) min = width[j];
        result.push_back(min);
    }
    return result;
}
int main()
{
    int n, t, item;
    vector <vector<int>> cases;
    vector <int> width, result, temp;

    cin >> n >> t;

    for(auto i = 0 ; i < n ; i++)
     cin >> item, width.push_back(item);

    for(auto i = 0 ; i < t ; i++)
    {
        cin >> item, temp.push_back(item);
        cin >> item, temp.push_back(item);
        cases.push_back(temp);
        temp.clear();
    }
    result = serviceLane(width, cases);

    for(auto i = 0 ; i < result.size() ; i++)
    {
        cout << result[i];
        if(i != result.size() - 1) cout << endl;
    }
    return 0;
}
**/
#include <bits/stdc++.h>
const int maxn = 1e5 + 5;
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
using namespace std;
vector<int> Lane;
class Seg_tree {
   private:
    struct S {
        int min;
        int l, r;
    } Tree[maxn << 2];

   public:
    inline void update(int node) {
        Tree[node].min = min(Tree[L(node)].min, Tree[R(node)].min);
        return;
    }
    inline void build(int left, int right, int node) {
        Tree[node].l = left, Tree[node].r = right;
        if (left == right) {
            Tree[node].min = Lane[left];
            return;
        }
        int mid = (Tree[node].l + Tree[node].r) >> 1;
        build(left, mid, L(node));
        build(mid + 1, right, R(node));
        update(node);
        return;
    }
    inline int ask_min(int left, int right, int node) {
        if (Tree[node].l == left && Tree[node].r == right) {
            return Tree[node].min;
        }
        int mid = (Tree[node].l + Tree[node].r) >> 1;
        if (right <= mid)
            return ask_min(left, right, L(node));
        else if (left > mid)
            return ask_min(left, right, R(node));
        else
            return min(ask_min(left, mid, L(node)),
                       ask_min(mid + 1, right, R(node)));
    }
} Tr;
int T, n, lane1, lane2;
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> T;
    for (int i = 0, tmp; i < n; i++) cin >> tmp, Lane.push_back(tmp);
    Tr.build(0, n - 1, 1);
    while (T--) {
        cin >> lane1 >> lane2;
        cout << (Tr.ask_min(lane1, lane2, 1)) << endl;
    }
    return 0;
}