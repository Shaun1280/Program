import os
import time
import cv2
import numpy as np
from matplotlib import pyplot as plt
from numba import jit

def hist_img(img, _min=10, _max=140):
    img[img >= _max] = _max
    img[img <= _min] = _min
    img = (1.0 * img - _min) * 255.0 / (_max - _min)
    img = img.astype(np.uint8)
    return img

def hist_gray_level(pixel, _min=10, _max=140):
    if pixel >= _max:
        pixel = _max
    if pixel <= _min:
        pixel = _min
    return int((1.0 * pixel - _min) * 255.0 / (_max - _min))


def read_all_boxes(boxes_dir='result/test.txt'):
    res = []
    if os.path.exists(boxes_dir) == False:
        return False, False
    f = open(boxes_dir, 'r')

    while (True):
        line = f.readline()
        if not line:
            break
        box = np.array(list(map(float, (line.split('\n')[0]).split(','))))
        res.append(box)

    f.close()
    return True, np.array(res)

def clahe(image):
    clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
    image_clahe = clahe.apply(image)
    return image_clahe

def hist(image):
    image_equal = cv2.equalizeHist(image)
    return image_equal

def seg1(img, gray, segMap, colors, N_COLOR=400):
    # 二值化
    ret, thresh = cv2.threshold(segMap, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    # 开运算
    kernel = np.ones((3, 3), np.int8)
    opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations=2)

    # 距离变换
    dist = cv2.distanceTransform(opening, cv2.DIST_L2, 5)
    dist = cv2.normalize(dist, 0.0, 1.0, cv2.NORM_MINMAX)

    # 生成标记
    ret, dist = cv2.threshold(dist, 0.0, 1.0, cv2.THRESH_BINARY)
    dist = cv2.normalize(dist, 0, 255, cv2.NORM_MINMAX)
    dist = dist.astype(np.int32)

    # 标记开始
    contours, hierarchy = cv2.findContours(dist, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
    markers = np.zeros(dist.shape, np.int32)

    num_contours = len(contours)
    for i in range(num_contours):
        cv2.drawContours(markers, contours, i, i + 1, -1, 8, hierarchy)

    print(markers.shape)
    # markers_copy = markers.copy().astype(np.uint8)
    # cv2.imshow('markers', markers_copy)

    cv2.watershed(img, markers)

    skip_contours = np.zeros(N_COLOR, np.int8)
    out = get_out_img(markers, skip_contours, colors)
    return out

def seg2(img, gray, segMap, colors, N_COLOR=400):
    ret, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
    # noise removal
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))
    opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations=2)

    sure_bg = cv2.dilate(opening, kernel, iterations=2)  # sure background area
    sure_fg = cv2.erode(opening, kernel, iterations=2)  # sure foreground area
    unknown = cv2.subtract(sure_bg, sure_fg)  # unknown area

    # Perform the distance transform algorithm
    dist_transform = cv2.distanceTransform(opening, cv2.DIST_L2, 5)
    # Normalize the distance image for range = {0.0, 1.0}
    cv2.normalize(dist_transform, dist_transform, 0, 1.0, cv2.NORM_MINMAX)

    # Finding sure foreground area
    ret, sure_fg = cv2.threshold(dist_transform, 0.5*dist_transform.max(), 255, 0)

    # Finding unknown region
    sure_fg = np.uint8(sure_fg)
    unknown = cv2.subtract(sure_bg,sure_fg)

    # Marker labelling
    ret, markers = cv2.connectedComponents(sure_fg)
    # Add one to all labels so that sure background is not 0, but 1
    markers = markers+1
    # Now, mark the region of unknown with zero
    markers[unknown==255] = 0

    markers = cv2.watershed(img, markers)

    height = markers.shape[0]
    width = markers.shape[1]

    skip_contours = np.zeros(N_COLOR, np.int8)
    out = get_out_img(markers, skip_contours, colors)
    return out

def seg3(img, gray, segMap, colors, N_COLOR=400):
    # 标记开始
    contours, hierarchy = cv2.findContours(segMap, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
    markers = np.zeros(segMap.shape, np.int32)

    # 根据 segMap 去除面积小于 30 的区域
    num_contours = len(contours)
    # print(num_contours)
    skip_contours = np.zeros(N_COLOR, np.int8)
    cnt = 0
    for i in range(num_contours):
        if cv2.contourArea(contours[i]) < 30:
            skip_contours[i] = 1
            continue
        cnt = cnt + 1
        cv2.drawContours(markers, contours, i, i + 1, -1, 8, hierarchy)

    mean_grays, std_grays = get_mean_std_gray(gray, markers)

    # markers = cv2.watershed(img, markers)
    for i, mean_gray in enumerate(mean_grays):
        if i >= num_contours:
            continue
        if (mean_gray >= hist_gray_level(30) and mean_gray <= hist_gray_level(90)) == False :
            skip_contours[i] = 1
            cv2.drawContours(markers, contours, i, 0, -1, 8, hierarchy)
    
    for i in range(num_contours):
        if skip_contours[i] == False:
            print('#', i, mean_grays[i], std_grays[i])

    out = get_out_img(markers, skip_contours, colors)
    return out

def seg4(img, gray, segMap, colors, N_COLOR=400):
    gray[segMap == 0] = 255

    markers = np.zeros(segMap.shape, np.int32)

    # dist_8u = dist.astype('uint8')
    gray = 255 - gray
    cv2.imshow('255_gray', gray)

    contours, hierarchy = cv2.findContours(gray, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

    # 根据 segMap 去除面积小于 25 的区域
    num_contours = len(contours)
    # print(num_contours)
    skip_contours = np.zeros(N_COLOR, np.int8)
    cnt = 0
    for i in range(num_contours):
        if cv2.contourArea(contours[i]) <= 25:
            skip_contours[i] = 1
        #     continue
        cnt = cnt + 1
        cv2.drawContours(markers, contours, i, i + 1, -1, 8, hierarchy)

    mean_grays, std_grays = get_mean_std_gray(gray, markers)
    mean_x = get_mean_x(markers)

    # markers = cv2.watershed(img, markers)
    # for i, mean_gray in enumerate(mean_grays):
    #     if i >= num_contours:
    #         continue
    #     if (mean_gray >= hist_gray_level(30) and mean_gray <= hist_gray_level(90)) == False :
    #         # skip_contours[i] = 1
    #         cv2.drawContours(markers, contours, i, 0, -1)
    
    for i in range(num_contours):
        if i >= N_COLOR:
            continue
        if skip_contours[i] == False:
            print('#', i, mean_grays[i], std_grays[i])

    # cv2.circle(markers, (5,5), 3, (255,255,255), -1)
    # markers_8u = (markers * 40).astype('uint8')
    # cv2.imshow('Markers', markers_8u)

    # cv2.watershed(img_copy, markers)

    out = get_out_img(markers, skip_contours, colors)
    return out

def seg_roi(img, gray, segMap, roi, colors, N_COLOR=400):
    img = img[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]]
    img = cv2.bilateralFilter(src=img, d=0, sigmaColor=100, sigmaSpace=15)
    cv2.imshow('seg_roi_img', img)
    gray = gray[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]]
    segMap = segMap[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]]
    
    # 标记开始
    contours, hierarchy = cv2.findContours(segMap, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
    markers = np.zeros(segMap.shape, np.int32)

    # 根据 segMap 去除面积小于 30 的区域
    num_contours = len(contours)
    # print(num_contours)
    skip_contours = np.zeros(N_COLOR, np.int8)
    # cnt = 0
    for i in range(num_contours):
        if cv2.contourArea(contours[i]) < 30:
            skip_contours[i] = 1
            continue
        # cnt = cnt + 1
        cv2.drawContours(markers, contours, i, i + 1, -1, 8, hierarchy)
        # cv2.drawContours(markers, contours, i, i + 1, 3)

    mean_grays, std_grays = get_mean_std_gray(gray, markers)

    for i in range(num_contours):
        if cv2.contourArea(contours[i]) >= 30:
            print('#', i, 'mean_gray = {}'.format(mean_grays[i]), 'std_gray = {}'.format(std_grays[i]))

    for i, mean_gray in enumerate(mean_grays):
        if i >= num_contours:
            continue
        if (mean_gray >= hist_gray_level(60 - 25) and mean_gray <= hist_gray_level(60 + 25)) == False:
            skip_contours[i] = 1
            # cv2.drawContours(markers, contours, i, 0, -1, 8, hierarchy)

    # markers = select_markers(markers, skip_contours)

    # markers = np.zeros(segMap.shape, np.int32)
    # markers = cv2.watershed(img, markers)
    out = get_out_img(markers, skip_contours, colors)
    return out

@jit
def select_markers(markers, skip_contours, N_COLOR=400):
    height = markers.shape[0]
    width = markers.shape[1]

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < N_COLOR:
                if skip_contours[contour_id] == 1:
                    continue
                random_int = np.random.randint(0, 10)
                if random_int > 3:
                    markers[i, j] = 0
    return markers

@jit
def get_mean_std_gray(gray, markers, N_COLOR=400):
    height = markers.shape[0]
    width = markers.shape[1]

    mean_gray = np.zeros(N_COLOR, np.int32)
    std_gray = np.zeros(N_COLOR, np.int32)
    area = np.zeros(N_COLOR, np.int32)

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < N_COLOR:
                mean_gray[contour_id] += gray[i, j]
                area[contour_id] += 1
    
    for i in range(N_COLOR):
        if area[i] != 0:
            mean_gray[i] = int(1.0 * mean_gray[i] / area[i])

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < N_COLOR:
                std_gray[contour_id] += np.square(mean_gray[contour_id] - gray[i, j])

    for i in range(N_COLOR):
        if area[i] != 0:
            std_gray[i] = int(np.sqrt(std_gray[i] / area[i]))
    return mean_gray, std_gray

@jit
def get_mean_x(markers, N_COLOR=400):
    height = markers.shape[0]
    width = markers.shape[1]

    mean_x = np.zeros(N_COLOR, np.int32)
    area = np.zeros(N_COLOR, np.int32)

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < N_COLOR:
                mean_x[contour_id] += j
                area[contour_id] += 1
    
    for i in range(N_COLOR):
        if area[i] != 0:
            mean_x[i] = int(1.0 * mean_x[i] / area[i])
    return mean_x

@jit
def get_out_img(markers, skip_contours, colors, N_COLOR=400):
    height = markers.shape[0]
    width = markers.shape[1]
    out = np.zeros((height, width, 3), np.uint8)
    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < N_COLOR:
                # print(contour_id)
                if skip_contours[contour_id] == 1:
                    continue
                out[i, j] = colors[contour_id]
    return out

def get_colors(N_COLOR=400):
    colors = np.zeros((N_COLOR, 3), np.int32)

    for i in range(N_COLOR):
        r = np.random.randint(127, 256)
        g = np.random.randint(127, 256)
        b = np.random.randint(127, 256)
        colors[i] = [b, g, r]
    
    return colors

def get_2box(box):
    _, roi = read_all_boxes(os.path.join(os.path.dirname(__file__), '../result/test_roi.txt'))
    roi = roi[0]

    ret = np.array([
        int(box[0] - roi[0]),
        int(box[1] - roi[1]),
        int(box[2]),
        int(3 * box[3])
    ], np.int32)
    return ret


if __name__ == '__main__':
    # open 93 101 171 223 227 257
    img_id = 257
    img = cv2.imread(os.path.join(os.path.dirname(__file__), 'res_seg', '{}.jpg'.format(str(img_id).zfill(5))))
    _, boxes = read_all_boxes(os.path.join(os.path.dirname(__file__), './result/test.txt'))

    if _ == False:
        print("_ = {}".format(_))
        exit(0)

    cv2.imshow('img', img)

    ret = np.split(img, 2, axis=1)
    # print(len(ret))

    colors = get_colors()

    # init data
    img = ret[0]
    # cv2.bilateralFilter(src=img, d=0, sigmaColor=100, sigmaSpace=15)
    # cv2.imshow('img_meanshift', img)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # c = 1
    gray = hist_img(gray)
    # c = 3
    img = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
    # c = 1
    segMap = cv2.cvtColor(ret[1], cv2.COLOR_BGR2GRAY)

    segMap[segMap <= 127] = 0
    segMap[segMap > 127] = 255
    segMap32 = segMap.astype(np.int32)
    #########################################
    since = time.time()
    # out = seg3(img, gray, segMap, colors)
    # out = seg_roi(img, gray, segMap, get_2box(boxes[img_id]), colors)
    out_seg4 = seg4(img, gray, segMap, colors)
    print(time.time() - since)
    # plt.imshow(dist, cmap='gray')
    # plt.show()
    # exit()

    cv2.imshow("gray", gray)
    # cv2.imshow("out", out)
    cv2.imshow("out_seg4", out_seg4)
    # cv2.imshow("markers_copy", markers_copy)
    # cv2.imshow("gray", gray)
    cv2.imshow("segMap", segMap)
    cv2.waitKey(0)