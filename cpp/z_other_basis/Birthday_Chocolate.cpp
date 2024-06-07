#include<bits/stdc++.h>
using namespace std;
vector<int>L;
class birthday{
    private:
        int num,day,month,tot;
    public:
        birthday(int n,int d,int m){
            num=n,day=d,month=m;
            tot=0;
        }
        inline int get_day(int start){
            int total=0;
            for(int i=start;i<=start+month-1;i++) total+=L[i];
            return total;
        }
        inline int Find(){
            for(int i=0;i<num&&i+month<=num;i++){
                int total=get_day(i);
                if(total==day) tot++;
            }
            return tot;
        }
};
int main(){
    int n,d,m,temp;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&temp), L.push_back(temp);
    scanf("%d%d",&d,&m);
    birthday B(n,d,m);
    printf("%d\n",B.Find());
    return 0;
}