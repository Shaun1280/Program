#include<bits/stdc++.h>
/*******P4783 【模板】矩阵求逆*******/
typedef long long LL;
const LL M = 1e9 + 7;
const int SIZE = 400;
using namespace std;
inline LL qpow(LL a, LL b){
    LL res = 1LL;
    while(b){
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}
int n;
LL A[SIZE][SIZE], E[SIZE][SIZE];
inline void rowSwap(int r1, int r2){
    for(int i = 0; i < n; i++) 
        swap(A[r1][i], A[r2][i]), swap(E[r1][i], E[r2][i]); //对应单位矩阵变换
}
inline void rowDivision(int r){ 
    LL denominator = A[r][r];
    for(int i = r; i < n; i++)
        A[r][i] = A[r][i] * qpow(denominator, M - 2) % M;
    for(int i = 0; i < n; i++)//对应单位矩阵变换
        E[r][i] = E[r][i] * qpow(denominator, M - 2) % M;
}
inline void rowMinus(int r, int c){
    LL mul = A[r][c] * qpow(A[c][c], M - 2) % M;
    for(int i = c; i < n; i++)
        A[r][i] = (A[r][i] - A[c][i] * mul) % M;
    for(int i = 0; i < n; i++) //对应单位矩阵变换
        E[r][i] = (E[r][i] - E[c][i] * mul) % M;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
    for(int i = 0; i < n; i++) E[i][i] = 1;
    for(int i = 0; i < n; i++){
        if(A[i][i] == 0){ 
            for(int j = i + 1; j < n; j++){
                if(A[j][i] != 0){
                    rowSwap(i, j);
                    break;
                }
            }
        }
        if(A[i][i] == 0){ cout << "No Solution" << endl; return 0; } //奇异矩阵 不可逆
        if(A[i][i] % M != 1) rowDivision(i); //将A[i][i] 变为1
        for(int j = i + 1; j < n; j++) rowMinus(j, i); //  j 行 - i 行的(A[j][i] / A[i][i])倍
        for(int j = 0; j < i; j++) rowMinus(j, i); //将A的i列其余元素变为0
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout << (E[i][j] + M) % M<< " ";
        cout << endl;
    }
    return 0;
}