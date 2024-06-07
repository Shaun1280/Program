import os
import time
import cv2
import numpy as np
from numba import jit

def get_markers_roi(img, gray, segmap, roi, box):
    gray[segmap == 0] = 255
    gray = 255 - gray
    # cv2.imshow('255_gray', gray)

    # print('gray.shape', gray.shape)

    markers = np.zeros(segmap.shape, np.int32)

    contours, hierarchy = cv2.findContours(gray, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

    num_contours = len(contours)
    # print(num_contours)

    skip_contours = np.zeros(num_contours, np.int8)
    for i in range(num_contours):
        if cv2.contourArea(contours[i]) <= 15:
            skip_contours[i] = 1
        else:
            cv2.drawContours(markers, contours, i, i + 1, -1, 8, hierarchy)

    # mean_grays, std_grays = get_mean_std_gray(gray, markers, num_contours)
    mean_x, mean_y = get_mean_x_y(markers, num_contours)

    for i in range(num_contours):
        if abs(gray.shape[1] - mean_x[i]) <= 16 or abs(mean_x[i]) <= 16:
            skip_contours[i] = 1
        if abs(gray.shape[0] - mean_y[i]) <= 16 or abs(mean_y[i]) <= 16:
            skip_contours[i] = 1

    # for i in range(num_contours):
    #     if skip_contours[i] == 0:
    #         print('#', i, 'area = {}'.format(cv2.contourArea(contours[i])))
    #         print('mean_gray = {}'.format(mean_grays[i]), 'std_gray = {}'.format(std_grays[i]))
    #         print('mean_x = {}'.format(mean_x[i]), 'mean_y = {}'.format(mean_y[i]))
    #         print('\n')

    markers_out, markers_out_rgb = get_markers_out(markers, skip_contours)
    markers_ret = np.zeros(markers_out.shape, np.uint8)

    box1 = np.array([int(box[0] - roi[0]), int(box[1] - roi[1]), 
                    int(box[2]), int(2.0 * box[3] / 3)])
    markers_ret[box1[1]:box1[1] + box1[3], box1[0]:box1[0] + box1[2]] \
        = markers_out[box1[1]:box1[1] + box1[3], box1[0]:box1[0] + box1[2]]
    
    box2 = np.array([int(box[0] - roi[0]), int(box[1] - roi[1] + box[3]), 
                    int(box[2]), int(2.0 * box[3])])
    markers_box2 = markers_out[box2[1]:box2[1] + box2[3], box2[0]:box2[0] + box2[2]]
    x_width = get_region_width(markers_box2)

    if x_width > 0.35 * markers_box2.shape[1]:
        markers_box2[markers_box2 > 0] = 2
        markers_ret[box2[1]:box2[1] + box2[3], box2[0]:box2[0] + box2[2]] \
            = markers_box2

    return markers_ret, markers_out_rgb

@jit
def get_mean_std_gray(gray, markers, num_contours):
    height = markers.shape[0]
    width = markers.shape[1]

    mean_gray = np.zeros(num_contours, np.int32)
    std_gray = np.zeros(num_contours, np.int32)
    area = np.zeros(num_contours, np.int32)

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < num_contours:
                mean_gray[contour_id] += gray[i, j]
                area[contour_id] += 1
    
    for i in range(num_contours):
        if area[i] != 0:
            mean_gray[i] = int(1.0 * mean_gray[i] / area[i])

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < num_contours:
                std_gray[contour_id] += np.square(mean_gray[contour_id] - gray[i, j])

    for i in range(num_contours):
        if area[i] != 0:
            std_gray[i] = int(np.sqrt(std_gray[i] / area[i]))
    return mean_gray, std_gray

@jit
def get_mean_x_y(markers, num_contours):
    height = markers.shape[0]
    width = markers.shape[1]

    mean_x = np.zeros(num_contours, np.int32)
    mean_y = np.zeros(num_contours, np.int32)
    area = np.zeros(num_contours, np.int32)

    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < num_contours:
                mean_x[contour_id] += j
                mean_y[contour_id] += i
                area[contour_id] += 1
    
    for i in range(num_contours):
        if area[i] != 0:
            mean_x[i] = int(1.0 * mean_x[i] / area[i])
            mean_y[i] = int(1.0 * mean_y[i] / area[i])
    return mean_x, mean_y

@jit
def get_region_width(markers):
    height = markers.shape[0]
    width = markers.shape[1]

    ret = 0
    for i in range(width):
        ok = False
        for j in range(height):
            if markers[j, i] > 0:
                ok = True
                break
        if ok:
            ret += 1
    return ret

@jit
def get_markers_out(markers, skip_contours):
    height = markers.shape[0]
    width = markers.shape[1]
    markers_out = np.zeros((height, width), np.uint8)
    markers_out_rgb = np.zeros((height, width, 3), np.uint8)
    for i in range(height):
        for j in range(width):
            contour_id = markers[i, j] - 1
            if 0 <= contour_id and contour_id < len(skip_contours):
                # print(contour_id)
                if skip_contours[contour_id] == 1:
                    continue
                markers_out[i, j] = 1
                markers_out_rgb[i, j] = (min(255, contour_id * 30), 0, min(255, contour_id * 30))
    return markers_out, markers_out_rgb


if __name__ == '__main__':
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

    def get_image_with_box(img, box):
        pt1 = (int(box[0]), int(box[1]))
        pt2 = (int(box[0] + box[2]), int(box[1] + box[3]))
        img_with_box = img.copy()
        img_with_box = cv2.rectangle(img_with_box, pt1, pt2, (255, 255, 0), thickness=1)
        return img_with_box

    def show_result(images, boxes_path='analyzer/result/test.txt'):
        _, boxes = read_all_boxes(boxes_path)

        assert(_ == True)

        for i in range(images.shape[0]):
            img_with_box = get_image_with_box(images[i], boxes[i])
            winname = 'show_image_with_box'.format()
            cv2.imshow(winname, img_with_box)
            cv2.waitKey(int(1000 / 30))

    def read_all_boxes(boxes_dir='analyzer/result/test.txt'):
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

    def record(record_file, boxes, times):
        # record bounding boxes
        record_dir = os.path.dirname(record_file)
        if not os.path.isdir(record_dir):
            os.makedirs(record_dir)
        np.savetxt(record_file, boxes, fmt='%.3f', delimiter=',')
        print('  Results recorded at', record_file)

        # record running times
        time_dir = os.path.join(record_dir, 'times')
        if not os.path.isdir(time_dir):
            os.makedirs(time_dir)
        time_file = os.path.join(time_dir, os.path.basename(
            record_file).replace('.txt', '_time.txt'))
        np.savetxt(time_file, times, fmt='%.8f')

    # open 93 101 171 223 227 257
    img_id = 171
    img = cv2.imread(os.path.join(os.path.dirname(__file__), 'res_seg', '{}.jpg'.format(str(img_id).zfill(5))))
    _, boxes = read_all_boxes(os.path.join(os.path.dirname(__file__), './result/test.txt'))
    _, roi = read_all_boxes(os.path.join(os.path.dirname(__file__), './result/test_roi.txt'))
    roi = roi[0]

    if _ == False:
        print("_ = {}".format(_))
        exit(0)

    cv2.imshow('img', img)

    ret = np.split(img, 2, axis=1)

    # init data
    img = ret[0]
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # c = 1
    gray = hist_img(gray)
    # c = 3
    img = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
    # c = 1
    segmap = cv2.cvtColor(ret[1], cv2.COLOR_BGR2GRAY)

    segmap[segmap <= 127] = 0
    segmap[segmap > 127] = 255
    segMap32 = segmap.astype(np.int32)
    #########################################
    since = time.time()
    _, out_seg4 = get_markers_roi(img, gray, segmap, roi, boxes[img_id])
    print(time.time() - since)

    cv2.imshow("gray", gray)
    # cv2.imshow("out", out)
    cv2.imshow("out_seg4", out_seg4)
    # cv2.imshow("markers_copy", markers_copy)
    # cv2.imshow("gray", gray)
    cv2.imshow("segmap", segmap)
    cv2.waitKey(0)