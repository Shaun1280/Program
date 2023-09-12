#include<bits/stdc++.h>
/*P1250 */
const int MAXN=3e4+1;
using namespace std;
struct node{
    int L, R, min_num; 
};
int n,h,total(0), Tree[MAXN];
node tmp;
vector<node>H;
/*Greedy plant tree from right to left*/
inline bool cmp(const node &a, const node &b){
    if(a.R==b.R) return a.L > b.L;
    return a.R < b.R;
}
inline void cnt_tree(){
    for(int i=0; i<H.size(); i++){
        int present_tree=0, needed_tree, cnt=0;
        for(int p=H[i].L; p<=H[i].R; p++)
            if(Tree[p]) present_tree++;
        /*get num of trees should be plant*/
        needed_tree=max(0, H[i].min_num-present_tree);
        if(!needed_tree) continue;
        for(int p=H[i].R; p>=H[i].L; p--){
            if(!Tree[p]) Tree[p]=1, cnt++;
            if(cnt>=needed_tree){
                total+=cnt; 
                break;
            }
        }
    }   
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin>>n>>h;
    for(int i=0; i<h; i++){
        cin>> tmp.L >> tmp.R >> tmp.min_num;
        H.push_back(tmp);
    }
    /*Greedy plant tree from right to left*/
    sort(H.begin(),H.end(),cmp);
    cnt_tree();
    cout<<total;
    return 0;
}