#include <bits/stdc++.h>
const int maxn = 1e6 + 6;
using namespace std;
struct H
{
    int height;
    char left, right;
} hiker[maxn];
class Hiker
{
public:
    int n, h, tot;
    string s;
    vector<int> valley;
    Hiker(int initialn);
    void get_data();
    void get_vec();
};
Hiker::Hiker(int initialn) { n = initialn, h = tot = 0, hiker[0].height = h, hiker[n + 1].height = h; }
void Hiker::get_data()
{
    cin >> s, s = "-" + s;
    hiker[0].right = s[1];
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'U')
            h++;
        else if (s[i] == 'D')
            h--;
        hiker[i].height = h, hiker[i].left = s[i], hiker[i].right = s[i + 1];
    }
    return;
}
void Hiker::get_vec()
{
    for (int i = 0; i <= n - 1; i++)
        if (hiker[i].height == 0)
            valley.push_back(i);
    valley.push_back(n);
    for (int i = 0; i < valley.size() - 1; i++)
        if (hiker[valley[i]].right == 'D' && hiker[valley[i + 1]].left == 'U')
            tot++;
    cout << tot;
}
int main()
{
    int n;
    scanf("%d", &n);
    Hiker H(n);
    H.get_data();
    H.get_vec();
    return 0;
}
/*
int main() {
    int l;
    string str; cin>>l>>str;
    int height = 0;
    int count = 0;
    for(int i=0;i<l;i++){
        if (str[i]=='U') height++;
        else {
            if (height==0) count++;
            height--;
        }
    }
    if (height<0) count--;
    cout<<count<<endl;
    //Enter your code here. Read input from STDIN. Print output to STDOUT    
    return 0;
}
 */