#include<bits/stdc++.h>
//P1219 八皇后
int cnt, arrangement[15];
bool line[15 << 1]; //列
bool oblique1[15 << 1], oblique2[15 << 1]; //两条斜线
int n;
void search(int row){
    if(row > n){
        if(++cnt > 3) return;
        for(int i = 1; i <= n; i++) std::cout << arrangement[i] << " ";
        std::cout << std::endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(line[i] || oblique1[row + i] || oblique2[row - i + n]) continue;
        line[i] = oblique1[row + i] = oblique2[row - i + n] = true;
        arrangement[row] = i;
        search(row + 1);
        line[i] = oblique1[row + i] = oblique2[row - i + n] = false;
    }
}
int main(){
    std::cin >> n;
    search(1);
    std::cout << cnt << std::endl;
    return 0;
}