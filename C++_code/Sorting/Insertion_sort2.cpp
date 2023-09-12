#include<bits/stdc++.h>
const int maxn=1e3+1;
using namespace std;
inline void Insert_sort(int n, int *Arr){
    static int temp, j, cnt(0);
    for(int i=1; i<n; i++){
        if(Arr[i]<Arr[i-1]){
            temp=Arr[i];
            for(j=i-1; j>=0 && (Arr[j]>temp); j--)
                Arr[j+1]=Arr[j]/*,cnt++*/; 
            /**
             *  1 4 3 5 6 2 
                1 3 4 5 6 2 
                1 3 4 5 6 2 
                1 3 4 5 6 2 
                1 2 3 4 5 6 
            */
            Arr[j+1]=temp/*, cnt++*/;
        }
        /*for(int i=0;i<n;i++) 
            printf("%d ", Arr[i]);
        putchar('\n'); */
    }
    cout<<cnt<<endl;
}
int main(){
    int n, Arr[maxn];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d", &Arr[i]);
    Insert_sort(n, Arr);
    return 0;
}