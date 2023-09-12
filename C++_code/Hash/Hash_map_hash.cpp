#include<bits/stdc++.h>
#include<hash_map>
const int M=1e5+3;
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-48, ch=getchar();
    return x*f;
}
unordered_map<int, int>m(M);
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    int T, n;
    T=read();
    while(T--){
        n=read();
        m.clear();
        for(int i=0, tmp; i<n; i++){
            tmp=read();
            if(!m[tmp]) printf("%d ",tmp);
            m[tmp]=1;
        }
        printf("\n");
    }
    return 0;
}
/*
vector<int>h[p];//哈希表村的房子们
inline int Hash(int x){//一个找到权值为x的人应该住的房子的函数
    return x>0?x%p:(-x)%p;//注意负数的取模
}
int main(){
    t=read();//读入t
    while(t--){
        for(int i=0;i<p;i++){//注意每次操作之前都要清空房子
            h[i].clear();
        }
        n=read();//读入n
        while(n--){
            a=read();//读入外星人a的权值
            int mod=Hash(a);//mod为a应该住的房子的编号
            if(h[mod].empty()){//如果这个房子没有住外星人
                printf("%d ",a);//输出a
                h[mod].push_back(a);//注意要给a开个房间哟
            }
            else{//如果已经住了人了
                bool fl=0;//fl=1表示a可以与房子里的人合并，反之则反
                for(int i=0;i<h[mod].size();i++){//枚举这个房子的房间里的人
                    if(a==h[mod][i]){//如果这个人与a权值相等
                        fl=1;//标记为可以合并了
                        break;//跳出循环
                    }
                }
                //如果找到了，那么a和找到的就会合并，我们啥都不用做
                if(fl==0){//如果没找到
                    printf("%d ",a);//输出a
                    h[mod].push_back(a);//给a开房
                }
            }
        }
        putchar('\n');//记得换行哦
    }
    return 0;
}//拒绝抄袭
*/