#include<bits/stdc++.h>
const int MAXN = 1e6 + 6;
using namespace std;
int heap[MAXN], tot = 1;
struct H{
    inline int top(){
        return heap[1];
    }
    inline void push(int x){
        heap[++tot] = x;
        int u = tot;
        while(u != 1 && heap[u] > heap[u >> 1]){
            swap(heap[u], heap[u >> 1]);
            u >>= 1;
        }
    }
    inline void pop(){
        heap[1] = heap[tot--];
        int u = 1;
        while((u << 1 ) <= tot){
            int lson = u << 1, rson = (u << 1) + 1;
            if(rson <= tot && heap[rson] < heap[lson])  
                lson = rson;
            if(heap[u] <= heap[lson]) break;
            swap(heap[u], heap[lson]);
            u = lson;
        }
    }
};
int a[MAXN], n;
int main(){
    H heap; 
    make_heap(a, a + n, greater<int>());
    int ans = 0;
    for(int i = 0; i < n - 1; i++){
        int u = a[0]; pop_heap(a, a + n - i, greater<int>());
        int v = a[0]; pop_heap(a, a + n - i - 1, greater<int>());
        ans += u + v;
        a[n - i - 2] = u + v;
        push_heap(a, a + n - i - 1, greater<int>());
    }
    return 0;
}