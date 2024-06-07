#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m;
LL total_p(0),maxx(0);
struct City{ 
    LL pos; LL population;
    bool operator <(const City &a )const{
        return pos<a.pos;
    }
};
City tmp_city_l,tmp_city_r;
struct Cloud{ 
    LL left, right, c, range;
    bool operator <(const Cloud &a)const{
        return right<a.right;//lower_bound use (<) //in priority_queue use (>)
    }
};
Cloud tmp_cloud;
inline bool cmpc(const City &a, const City &b){return a.pos<b.pos;}
inline bool cmpp(const LL &a, const LL &b){return a>b;}
inline bool cmpcl(const Cloud &a, const Cloud &b){return a.right<b.right;}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n;
    /********************Init*/
    vector<City>city, Tmp_1(n); 
    LL Delta[n+2], cnt(0);
    memset(Delta,0,sizeof(Delta));
    for(int i=0;i<n;i++) cin>>Tmp_1[i].population;
    for(int i=0;i<n;i++) 
        cin>>Tmp_1[i].pos, city.push_back(Tmp_1[i]);
    cin>>m;
    LL total[m+1];
    memset(total,0,sizeof(total));
    vector<Cloud>cloud, Tmp_2(m);
    for(int i=0;i<m;i++) cin>>Tmp_2[i].c;
    for(int i=0;i<m;i++) {
        cin>>Tmp_2[i].range;
        Tmp_2[i].left=Tmp_2[i].c-Tmp_2[i].range;
        Tmp_2[i].right=Tmp_2[i].c+Tmp_2[i].range;
        cloud.push_back(Tmp_2[i]);
    }
    sort(city.begin(),city.end(),cmpc);
    sort(cloud.begin(),cloud.end(),cmpcl);
    /********************Init*/
    for(int i=0;i<m;i++) {//2*m*log(n)
        tmp_city_l.pos=cloud[i].left, tmp_city_r.pos=cloud[i].right;
        int Indexl=lower_bound(city.begin(),city.end(),tmp_city_l)-city.begin();//>=
        int Indexr=upper_bound(city.begin(),city.end(),tmp_city_r)-city.begin();//>
        /*Find cities coverd by cloud[i]*/
        if(city[Indexl].pos>cloud[i].right||Indexl==n) continue;
        Delta[Indexl]++, Delta[Indexr]--;//Similar method in Array Manipulation
    }
    for(int i=0;i<n;i++) {
        cnt+=Delta[i];
        if(cnt==0) total_p+=city[i].population;
        if(cnt==1){
            tmp_cloud.right=city[i].pos;
            int Index=lower_bound(cloud.begin(),cloud.end(),tmp_cloud)-cloud.begin();
            while(cloud[Index].left>city[i].pos&&Index<m) Index++;
            total[Index]+=city[i].population;
            /*Get the population covered by cloud[i]*/
        }
    }
    for(int i=0;i<m;i++) maxx=max(maxx,total[i]);
    cout<<maxx+total_p;
    return 0;
}