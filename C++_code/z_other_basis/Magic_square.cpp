#include<bits/stdc++.h>
using namespace std;
int main(){
int magic_mat[8][3][3] = {
    {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}},
    {{6, 1, 8}, {7, 5, 3}, {2, 9, 4}},
    {{4, 9, 2}, {3, 5, 7}, {8, 1, 6}},
    {{2, 9, 4}, {7, 5, 3}, {6, 1, 8}}, 
    {{8, 3, 4}, {1, 5, 9}, {6, 7, 2}}, 
    {{4, 3, 8}, {9, 5, 1}, {2, 7, 6}}, 
    {{6, 7, 2}, {1, 5, 9}, {8, 3, 4}}, 
    {{2, 7, 6}, {9, 5, 1}, {4, 3, 8}},  
};

int A[3][3];
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
        scanf("%d", &A[i][j]);
}

int min_cost = 81;
for (int k = 0; k < 8; k++) {
    int crt_cost = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            crt_cost += abs( A[i][j] - magic_mat[k][i][j] );
    }
    if (crt_cost < min_cost)
        min_cost = crt_cost;
}

printf("%d", min_cost);
return 0;
}
/*
#include <algorithm>
#include <iostream>
#include <valarray>

int main()
{
    const std::valarray<int> magicSquares[] = {
        { 8, 1, 6, 3, 5, 7, 4, 9, 2 },
        { 6, 1, 8, 7, 5, 3, 2, 9, 4 },
        { 8, 3, 4, 1, 5, 9, 6, 7, 2 },
        { 4, 3, 8, 9, 5, 1, 2, 7, 6 },
        { 6, 7, 2, 1, 5, 9, 8, 3, 4 },
        { 2, 7, 6, 9, 5, 1, 4, 3, 8 },
        { 4, 9, 2, 3, 5, 7, 8, 1, 6 },
        { 2, 9, 4, 7, 5, 3, 6, 1, 8 }
    };

    std::valarray<int> broken(9);

    for (auto & i : broken)
        std::cin >> i;

    int cost(99);

    for (auto && magicSquare : magicSquares)
        cost = std::min(cost, std::abs(magicSquare - broken).sum());

    std::cout << cost << std::endl;
    return 0;
}
 */