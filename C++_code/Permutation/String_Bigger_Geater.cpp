#include <bits/stdc++.h>
using namespace std;
int T;
inline int get_closest_p(int pos, string s) {
    int p = s.size(), minval = 0x7fffffff;
    for (int i = pos + 1; i < s.size(); i++)
        if (s[i] - s[pos] < minval && s[i] - s[pos] > 0)
            minval = s[i] - s[pos], p = i;
    if (minval != 0) return p;
    return s.size();
}
inline void swap_string(string &s) {
    bool Swap = false;
    int Index;
    for (int i = s.size() - 2; i >= 0; i--) {
        int pos = get_closest_p(i, s);
        /*To make our string the smallest, we start from (end-1)
         */
        if (pos != s.size()) {
            swap(s[pos], s[i]), Swap = true, Index = i;
            break;
        }
        if (Swap) break;
    }
    if (!Swap) {
        cout << "no answer" << endl;
        return;
    }
    sort(s.begin() + Index + 1,
         s.end());  // sort the rest of string to make it the smallest
    cout << s << endl;
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> T;
    cin.ignore();
    while (T--) {
        string s;
        getline(cin, s);
        swap_string(s);
    }  // initalize
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    int test;
    cin >> test;
    while(test--) {
        string inp;
        cin >> inp;
        if (next_permutation(inp.begin(), inp.end()) == false ) {
prev_permutation 前一个全排列 cout << "no answer" << endl;
        }
        else {
            cout << inp << endl;
        }
    }
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[] = {5,4,3,2,1};
    vector <int> b(a,a+5); //initialised b using elements of a.
    sort(a,a+5);
    sort(b.begin(),b.end());
    for (auto i :a) {
        cout<<i<<" ";
    }
    cout<<endl;
    for (auto i:b) {
        cout<<i<<" ";
    }
    cout<<endl;
}
*/