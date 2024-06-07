#include<bits/stdc++.h>
//sorting Lily's homework
const int maxn=1e5+1;
using namespace std;
struct node{
    int Initial_pos, val;
};
node tmp;
int n,cnt1,cnt2;
vector<node>num1;
vector<node>num2;
inline bool cmp2(const node &a, const node &b){
    return a.val > b.val;
}
inline bool cmp1(const node &a, const node &b){
    return a.val < b.val;
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0; i<n; i++) 
        cin>>tmp.val, tmp.Initial_pos=i, num1.push_back(tmp);
    num2.assign(num1.begin(),num1.end());
    sort(num1.begin(), num1.end(), cmp1);
    //sort the array in ascending order
    sort(num2.begin(), num2.end(), cmp2);
    //sort the array in descending order
    for(int i=0; i<num1.size(); i++){
        while(num1[i].Initial_pos!=i){
            swap(num1[i].Initial_pos, num1[num1[i].Initial_pos].Initial_pos);
            swap(num1[i].val, num1[num1[i].Initial_pos].val);
            cnt1++;//swap & get cnt1
        }
    } 
     for(int i=0; i<num2.size(); i++){
        while(num2[i].Initial_pos!=i){
            swap(num2[i].Initial_pos, num2[num2[i].Initial_pos].Initial_pos);
            swap(num2[i].val, num2[num2[i].Initial_pos].val);
            cnt2++;//swap & get cnt1
        }
    } 
    cout<<min(cnt1,cnt2);//get minimum cnt
    return 0;
}