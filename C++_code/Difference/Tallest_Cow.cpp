#include<bits/stdc++.h>
const int MAXN = 1e4 + 4;
using namespace std;
int n, I, R, h;
map<pair<int, int>,bool>vis;
int delta[MAXN];
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> I >> h >> R;
    while(R--){
        int A, B; //cow A see cow B
        cin >> A >> B;
        if(A > B) swap(A, B);
        pair<int, int> P = make_pair(A, B);
        if(vis[P]) continue;
        delta[A + 1]--, delta[B]++;
        vis[P] = true;
    }
    for(int i = 1; i <= n; i++){
        delta[i] += delta[i - 1];
        cout << h + delta[i] << endl;
    }
    return 0;
}