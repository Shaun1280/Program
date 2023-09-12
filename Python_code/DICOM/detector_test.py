import os
import cv2
import numpy as np

from analyzer.detector.utils.datasets import letterbox
from analyzer.detector.detect import detect

def get_images(opt):
    source, imgsz = opt["source"], opt["img-size"]
    files = os.listdir(os.path.join(source))
    images = []
    names = []
    for f in files:
        if f.lower().endswith('.jpg'):
            img = cv2.imread(os.path.join(source, f))
            print(img.shape)
            # Padded resize
            img = letterbox(img, new_shape=(imgsz, imgsz), auto=False)[0] # 对图片进行resize+pad
            img = img[:, :, ::-1]  # BGR to RGB, to 3x640x640
            img = np.ascontiguousarray(img) # 将数组内存转为连续，提高运行速度
            images.append(img)
            names.append(f)
    return np.array(images, dtype=np.uint8), names

if __name__ == '__main__':
    opt = {}
    dirname = os.path.dirname(__file__)
    opt["weights"] = os.path.join(dirname, "detector/weights/best.pt") # 训练的权重
    opt["conf"] = 0.4 # 置信度阈值
    opt["img-size"] = 480 # 网络输入图片大小
    opt["source"] = os.path.join(dirname, "detector/inference/images") # 测试数据
    opt["iou-thres"] = 0.45 # 做nms的iou阈值
    opt["save-dir"] = os.path.join(dirname, "detector/inference/output") # 结果图片保存路径
    opt["visualize-img"] = True
    opt["save-img"] = True
    opt["augment"] = False # 推理的时候进行多尺度，翻转等操作(TTA)推理

    # get images
    images, names = get_images(opt)
    # for img in images:
    #     cv2.imshow('test', img.transpose(1, 2, 0))
    #     cv2.waitKey(100)

    bboxes = detect(images, visualize=False)

    for f, img in enumerate(images):
        bbox = bboxes[f]
        p1 = (int(bbox[0]), int(bbox[1]))
        p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
        cv2.rectangle(img, p1, p2, (255, 255, 0), 1, 1)
        if opt["save-img"] == True:
            cv2.imwrite(os.path.join(opt["save-dir"], "{}".format(names[f])), img)
        cv2.imshow("Detected", img)
        cv2.waitKey(100)