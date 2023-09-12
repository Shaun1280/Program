#include <bits/stdc++.h>
const int maxn = 1e3 + 3;
using namespace std;
class Score
{
private:
    int n, maxtot, mintot;
    int maxscore, minscore, list[maxn];

private:
    inline int read()
    {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9')
            f = (ch == '-') ? -1:1, ch=getchar();
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch=getchar();
        return x * f;
    }

public:
    Score()
    {
        maxtot = 0, mintot = 0;
        memset(list, 0, sizeof(list));
    }
    void INIT()
    {
        n = read();
        for (int i = 1; i <= n; i++)
            list[i] = read();
        maxscore = minscore = list[1];
    }
    void get_tot()
    {
        for (int i = 2; i <= n; i++)
            if (list[i] > maxscore)
                maxscore = list[i], maxtot++;
        for (int i = 2; i <= n; i++)
            if (list[i] < minscore)
                minscore = list[i], mintot++;
    }
    void out_put()
    {
        printf("%d %d", maxtot, mintot);
    }
};
int main()
{
    Score S;
    S.INIT();
    S.get_tot();
    S.out_put();
    return 0;
}