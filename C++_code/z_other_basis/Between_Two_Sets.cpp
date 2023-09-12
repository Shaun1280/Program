#include<bits/stdc++.h>
using namespace std;
class FACTOR{
    private:
        int n,m;
        bool SIGN1[101];
        bool SIGN2[101];
        vector<int>a;
        vector<int>b;
        vector<int>ans;
    public:
        FACTOR(){
            n=0,m=0;
            memset(SIGN1,false,sizeof(SIGN1));
            memset(SIGN2,false,sizeof(SIGN2));
        }
        void In_put(){
            scanf("%d%d",&n,&m);
            for(int i=0;i<n;i++){
                int temp;
                scanf("%d",&temp);
                a.push_back(temp);
            }
            for(int i=0;i<m;i++){
                int temp;
                scanf("%d",&temp);
                b.push_back(temp);
            }
            sort(a.begin(),a.end());
            sort(b.begin(),b.end());
            return;
        }
        void get(){
            for(int i=a[0];i<=b[0];i++){
                for(int j=1;j<=a.size();j++) {
                    if(i%a[j-1]==0) SIGN1[i]=true; 
                    else {SIGN1[i]=false;break;}
                }
                for(int j=1;j<=b.size();j++) {
                    if(b[j-1]%i==0) SIGN2[i]=true;
                    else {SIGN2[i]=false;break;}
                }
                if(SIGN1[i]==true&&SIGN2[i]==true) ans.push_back(i);
            }
            return;
        }
        void out_put(){
            //for(int i=0;i<ans.size();i++) cout<<ans[i]<<" ";
            printf("%d\n",ans.size());
            return;
        }
};
int main(){
    FACTOR F;
    F.In_put();
    F.get();
    F.out_put();
    return 0;
}