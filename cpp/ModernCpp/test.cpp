#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 10;
    vector<vector<int>> matrix(n, vector<int>(n));
    int x = 0, y = n - 1;
    int num = 1;
    while (num <= n * n) {
        if (((y - x) & 1) != ((n - 1) & 1)) {
            while (x <= n - 1 && y <= n - 1)
                matrix[x++][y++] = num++;
            if (x > n - 1)
                y -= 2, x -= 1;
            else
                y -= 1;
        } else {
            while (x >= 0 && y >= 0)
                matrix[x--][y--] = num++;
            if (y < 0)
                x += 2, y += 1;
            else
                x += 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}

/*
1
10
1 -1 2 2 3 -3 4 -4 5 -5

*/