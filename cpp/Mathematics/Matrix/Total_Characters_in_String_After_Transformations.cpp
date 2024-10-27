#include <bits/stdc++.h>

class Matrix {
  private:
    static constexpr int SIZE = 26;
    std::array<std::array<int, SIZE>, SIZE> m{};

  public:
    static constexpr int MOD = 1'000'000'007;
    Matrix() = default;

    const std::array<int, SIZE>& operator[](int i) const { return m[i]; }

    std::array<int, SIZE>& operator[](int i) { return m[i]; }

    static Matrix identity() {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            result[i][i] = 1;
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                long long sum = 0;
                for (int k = 0; k < SIZE; ++k) {
                    sum = (sum + (1LL * m[i][k] * other[k][j]) % MOD) % MOD;
                }
                result[i][j] = static_cast<int>(sum);
            }
        }
        return result;
    }

    Matrix pow(int64_t exponent) const {
        if (exponent == 0)
            return identity();
        if (exponent == 1)
            return *this;

        Matrix result = identity();
        Matrix base = *this;

        while (exponent > 0) {
            if (exponent & 1) {
                result = result * base;
            }
            base = base * base;
            exponent >>= 1;
        }
        return result;
    }
};

class Solution {
  public:
    int lengthAfterTransformations(std::string_view s, int t,
                                   const std::vector<int>& nums) {
        Matrix transform;

        for (int i = 0; i < 26; ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                transform[(i + j) % 26][i] = 1;
            }
        }

        Matrix initial;
        for (char c : s)
            initial[c - 'a'][0]++;

        Matrix final = transform.pow(t) * initial;

        int result = 0;
        for (int i = 0; i < 26; ++i) {
            result = (result + final[i][0]) % Matrix::MOD;
        }

        return result;
    }
};