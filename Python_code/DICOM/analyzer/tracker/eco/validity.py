import numpy as np
from numba import jit

@jit
def calc_mean(score, K, top_k_idx):
    mean_score = 0
    for id in top_k_idx:
        x, y = id // score.shape[1], id % score.shape[1]
        mean_score += score[x, y]
    mean_score /= K
    return mean_score

@jit
def calc2(score, K, top_k_idx, mean_score):
    std_score = 0
    for id in top_k_idx:
        x, y = id // score.shape[1], id % score.shape[1]
        std_score += (score[x, y] - mean_score) ** 2
    std_score = np.sqrt(std_score / K)

    return std_score

def validity_check(score, K=10):
    top_k_idx = np.argsort(score, None)[::-1][0:K]

    mean_score = calc_mean(score, K, top_k_idx)

    return calc2(score, K, top_k_idx, mean_score)

if __name__ == '__main__':
    arr = np.array([
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [11, 12, 13, 14],
        [9, 10, 15, 16]
    ])
    print(arr)
    std_score = validity_check(arr)
    print(std_score)