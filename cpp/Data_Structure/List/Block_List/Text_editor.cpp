#include <bits/stdc++.h>
//P4008 [NOI2003]文本编辑器 https://www.luogu.com.cn/problem/P4008
using namespace std;

constexpr int MAXS = 4000;

int n, x, cursor, preSz;
char opt[20];
list<vector<char>> lst;
list<vector<char>>::iterator itr;
time_t tDel, tIns, tUpdate;

inline void merge() { //合并较小的块
    decltype(lst.begin()) tmpItr;
    for (auto itr = lst.begin(); itr != lst.end(); ++itr) {
        tmpItr = itr, ++tmpItr;
        if (tmpItr == lst.end()) break;
        if (itr->size() + tmpItr->size() <= MAXS) {
            for (auto c : *tmpItr) itr->push_back(c);
            lst.erase(tmpItr);
        }
    }
}
/*合并，更新光标所处节点信息*/
inline void update() {
    merge();
    for (itr = lst.begin(), preSz = 0; itr != lst.end(); ++itr) {
        if (preSz + itr->size() > cursor) break;
        preSz += itr->size();
    }
    if (itr == lst.end()) --itr;
}
/*将光标移动到第k个字符后*/
inline void move(int k) { cursor = k, update(); }
/*在光标处插入s*/
inline void insert(int len, const vector<char>& s) {
    vector<char> vec(itr->begin() + cursor - preSz, itr->end()); //将块分为两部分
    for (int i = 0; i < vec.size(); i++) itr->pop_back();  //将块分为两部分
    vector<char> tmp;
    for (int i = 0; i < s.size(); i += MAXS) { //分块依次插入
        tmp.clear();
        for (int j = i; j < min(i + MAXS, (int)s.size()); j++)
            tmp.push_back(s[j]);
        itr = lst.insert(++itr, tmp);
    }
    lst.insert(++itr, vec); //将之前的第二块插入
    update();
}
/*删除光标后len个字符*/
inline void del(int len) {
    int tmp = cursor - preSz;
    auto tmpItr(itr);
    if (tmp + len <= tmpItr->size()) {  //删除的范围在块内
        vector<char> vec(tmpItr->begin() + tmp + len, tmpItr->end());
        for (int i = 0; i < vec.size() + len; i++) tmpItr->pop_back();
        lst.insert(++tmpItr, vec);
        update();
        return;
    }
    tmp = tmpItr->size() - tmp; //删除itr后tmp个字符
    for (int i = 0; i < tmp; i++) tmpItr->pop_back();
    len -= tmp, ++tmpItr;
    while (len > tmpItr->size()) //删除整个块
        len -= tmpItr->size(), tmpItr = lst.erase(tmpItr);
    vector<char> vec(tmpItr->begin() + len, tmpItr->end()); //处理剩余的块
    tmpItr = lst.erase(tmpItr), lst.insert(tmpItr, vec);
    update();
}

inline void get(int n) {
    int tmp = cursor - preSz;
    auto tmpItr(itr);
    while (n-- && tmpItr != lst.end()) {
        putchar(tmpItr->at(tmp++));
        if (tmp == tmpItr->size()) tmp -= tmpItr->size(), ++tmpItr;
    }
    putchar('\n');
}

inline void prev() {
    if (cursor-- == preSz) --itr, preSz -= itr->size();
}

inline void next() {
    if (++cursor == preSz + itr->size()) preSz += itr->size(), ++itr;
    if (itr == lst.end()) --itr, preSz -= itr->size();
}

int main() {
    scanf("%d", &n);
    static vector<char> vec; //先插入空节点
    lst.insert(lst.end(), vec), update();
    while (n--) {
        scanf("%s", opt), vec.clear();
        if (opt[0] == 'I') {
            scanf("%d", &x);
                for (int i = 1; i <= x; i++) {
                    char c = getchar();
                    if (32 <= c && c <= 126) vec.push_back(c);
                    else i--;
                }
            insert(0, vec);
        }
        if (opt[0] == 'M') scanf("%d", &x), move(x);
        if (opt[0] == 'D') scanf("%d", &x), del(x);
        if (opt[0] == 'P') prev();
        if (opt[0] == 'N') next();
        if (opt[0] == 'G') scanf("%d", &x), get(x);
    }
    return 0;
}