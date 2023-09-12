#include <bits/stdc++.h>

using namespace std;

class own_double_less : public std::binary_function<double, double, bool> {
   public:
    own_double_less(double arg_ = 1e-10) : epsilon(arg_) {}
    bool operator()(const double& left, const double& right) const {
        // you can choose other way to make decision
        // (The original version is: return left < right;)
        return (abs(left - right) > epsilon) && (left < right);
    }
    double epsilon;
};

map<double, int, own_double_less> mp;