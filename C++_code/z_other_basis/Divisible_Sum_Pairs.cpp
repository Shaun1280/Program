#include<bits/stdc++.h>
using namespace std;
vector<int> vec;
class Division{
    private:
        int num,div_num,temp,tot;
    public:
        Division(){tot=0;}
        Division(int n,int k){num=n,div_num=k;}
        void get_seq(){for(int i=1;i<=num;i++) scanf("%d",&temp),vec.push_back(temp);}
        int get_tot(){
            for(int i=0;i<num-1;i++)
                for(int j=i+1;j<num;j++)
                    if((vec[i]+vec[j])%div_num==0)
                        tot++;
            return tot;
        }
};
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    Division D(n,k);
    D.get_seq();
    printf("%d",D.get_tot());
    return 0;
}