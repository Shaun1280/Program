#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    string removeOccurrences(string s, string part) {
        int n(s.size()), m(part.size());
        vector<int> pi_part(m), match(n);

        for (int i = 1; i < m; ++i) {
            int j = pi_part[i - 1];
            while (j > 0 && part[i] != part[j])
                j = pi_part[j - 1];
            if (part[i] == part[j])
                ++j;
            pi_part[i] = j;
        }

        string ret;
        for (int i = 0, j = 0; i < n; ++i) {
            ret += s[i];
            while (j > 0 && s[i] != part[j]) {
                j = j ? pi_part[j - 1] : 0;
            }
            if (s[i] == part[j]) {
                ++j;
            }
            match[ret.size() - 1] = j;
            if (j == m) {
                for (int t = 0; t < m; ++t)
                    ret.pop_back();
                j = ret.size() ? match[ret.size() - 1] : 0;
            }
        }

        return ret;
    }
};