import numpy as np
import cv2
from numba import jit
from numba.experimental import jitclass
import time

@jit
def notInBound(height, width, x, y):
    return x < 0 or x >= height or y < 0 or y >= width

from numba import int32, float64, uint8
spec = [
    ('N', int32),
    ('R', int32),
    ('_min', int32),
    ('phai', int32),
    ('sample_std', float64[:, :]),
    ('samples', float64[:, :, :]),
    ('I_count', uint8[:, :]),
]

@jitclass(spec)
class ViBe:
    def __init__(self, N=20, R=20, _min=2, phai=16):
        self.N = N
        self.R = R
        self._min = _min
        self.phai = phai

    def init_background(self, I_gray):
        height = I_gray.shape[0]
        width = I_gray.shape[1]

        self.I_count = np.zeros(I_gray.shape).astype(np.uint8)
        self.samples = np.zeros((height, width, self.N))
        self.sample_std = np.zeros((height, width))

        for i in range(height):
            for j in range(width):
                for n in range(self.N):
                    x, y = 0, 0
                    while ((x == 0 and y == 0) or notInBound(height, width, i + x, j + y)):
                        x = np.random.randint(-1, 2)
                        y = np.random.randint(-1, 2)
                    ri = i + x
                    rj = j + y
                    self.samples[i, j, n] = I_gray[ri, rj]
                self.sample_std[i][j] = np.std(self.samples[i][j])

    def update_background(self, I_gray, low, high):
        height = I_gray.shape[0]
        width = I_gray.shape[1]
        segMap = np.zeros((height, width)).astype(np.uint8)

        for i in range(height):
            for j in range(width):
                # if I_gray[i, j] < low or I_gray[i, j] > high:
                #     continue
                count, index, dist = 0, 0, 0
                sigma = self.sample_std[i][j]
                adaptive_thres = min(40.0, max(sigma * 0.5, 20.0))

                while count < self._min and index < self.N:
                    dist = np.abs(I_gray[i, j] - self.samples[i, j, index])
                    if dist < adaptive_thres:
                        count += 1
                    index += 1

                # 大于匹配阈值，为背景 segMap[i, j] = 0
                if count >= self._min:
                    # 1、每个背景像素有 1 / phai几率更新自己的样本集
                    # 更新样本集方式为随机选取该像素样本集中的一个元素，更新为当前像素的值
                    r = np.random.randint(0, self.phai)
                    if r == 0:
                        self.samples[i, j, np.random.randint(0, self.N)] = I_gray[i, j]
                        self.sample_std[i, j] = np.std(self.samples[i][j])
                    # 2、每个背景像素有 1 / phai 几率更新邻域的样本集
                    # 方式为随机选取一个邻域点，并在该邻域点的样本集中随机选择
                    # 一个更新为当前像素值更新自己样本集
                    r = np.random.randint(0, self.phai)
                    if r == 0:
                        x, y = 0, 0
                        while((x == 0 and y == 0) or notInBound(height, width, i + x, j + y)):
                            x = np.random.randint(-1, 2)
                            y = np.random.randint(-1, 2)
                        ri = i + x
                        rj = j + y
                        self.samples[ri, rj, np.random.randint(0, self.N)] = I_gray[i, j]
                        self.sample_std[ri, rj] = np.std(self.samples[ri][rj])
                    # 背景像素的计数设置为0
                    # I_count[i, j] = 0
                else: # 否则为前景
                    segMap[i, j] = 255
                    # 前景像素计数+1
                    # I_count[i, j] = I_count[i, j] + 1
                    # # 如果某个像素连续 50 次被检测为前景
                    # # 则认为一块静止区域被误判为运动，将其更新为背景点
                    # if I_count[i, j] > 50:
                    #     segMap[i, j] = 0

        # 钡餐具有特定的像素值范围
        for i in range(height):
            for j in range(width):
                if I_gray[i, j] < low or I_gray[i, j] > high:
                    segMap[i, j] = 0
        return segMap
    
def run_vibe(images):
    vibe = ViBe()
    vibe.init_background(images[0])

    for f, img in enumerate(images):
        since = time.time()

        segMap = vibe.update_background(img)

        cv2.imshow('img', img)
        cv2.imshow('segMap', segMap)
        print(time.time() - since)
        
        if (cv2.waitKey(30) & 0xff) == ord('q'):
            break

    cv2.destroyAllWindows()
