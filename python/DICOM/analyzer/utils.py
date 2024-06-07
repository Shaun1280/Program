import os
import numpy as np
import cv2

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
    img_with_box = cv2.rectangle(img_with_box, pt1, pt2, (15, 185, 255), thickness=1)
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

def read_npy(npy_dir):
    if os.path.exists(npy_dir) == False:
        return False, False
    return True, np.load(npy_dir)

# record bounding boxes
def record(record_file, boxes):
    record_dir = os.path.dirname(record_file)
    if not os.path.isdir(record_dir):
        os.makedirs(record_dir)
    np.savetxt(record_file, boxes, fmt='%.1f', delimiter=',')

def record_bin(record_file, arr):
    record_dir = os.path.dirname(record_file)
    if not os.path.isdir(record_dir):
        os.makedirs(record_dir)
    np.save(record_file, arr)