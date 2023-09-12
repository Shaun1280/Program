import os
import time

import sys

sys.path.insert(0, os.path.dirname(__file__))

import cv2
import torch
import numpy as np

from analyzer.detector.models.experimental import attempt_load

from analyzer.detector.utils.general import (
    check_img_size, non_max_suppression, scale_coords, plot_one_box, set_logging)

def time_synchronized():
    torch.cuda.synchronize() if torch.cuda.is_available() else None
    return time.time()

class YoloDetector:
    def __init__(self, augment=False, conf=0.5, iou_thres=0.45, imgsz=416, \
        weights = os.path.join(os.path.dirname(__file__), "weights/best.pt")):
        self.augment = augment
        self.conf = conf
        self.iou_thres = iou_thres
        self.imgsz = imgsz
        self.init_detect(weights)

    @torch.no_grad()
    def init_detect(self, weights):
        # Initialize
        set_logging()

        # 获取设备
        self.device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

        # 如果设备为gpu，使用Float16
        self.half = self.device.type != 'cpu'  # half precision only supported on CUDA

        # Load model
        # 加载Float32模型，确保用户设定的输入图片分辨率能整除32(如不能则调整为能整除并返回)
        self.model = attempt_load(weights, map_location=self.device)  # load FP32 model
        self.imgsz = check_img_size(self.imgsz, s=self.model.stride.max())  # check img_size
        # 设置Float16
        if self.half:
            self.model.half()  # to FP16

        # # 进行一次前向推理,测试程序是否正常
        # img = torch.zeros((1, 3, self.imgsz, self.imgsz), device=self.device)  # init img
        # _ = self.model(img.half() if self.half else img) if self.device.type != 'cpu' else None  # run once

    @torch.no_grad()
    def detect_frame(self, img):
        # Run inference
        t0 = time.time()

        box = np.zeros(4)
        im0 = img.copy()
        img = torch.from_numpy(img.transpose(2, 0, 1)).to(self.device) # Tensor
        # 图片也设置为Float16
        img = img.half() if self.half else img.float()  # uint8 to fp16/32
        img /= 255.0  # 0 ~ 255 to 0.0 ~ 1.0
        # 没有batch_size时，在最前面添加一个轴
        if img.ndimension() == 3:
            img = img.unsqueeze(0) # shape 如 (1,3,384,640)

        # Inference
        t1 = time_synchronized()
        pred = self.model(img, augment=self.augment)[0]

        # Apply NMS
        pred = non_max_suppression(pred, self.conf, self.iou_thres, classes=False, agnostic=False)
        t2 = time_synchronized()

        # Process detections
        for i, det in enumerate(pred):  # detections per image
            # s = ''
            # 设置打印信息(图片宽高)， s 如‘384*640’
            # s += '%gx%g ' % img.shape[2:]  # print string 
            
            if det is not None and len(det):
                # Rescale boxes from img_size to im0 size
                # 调整预测框的坐标：基于resize+pad的图片的坐标-->基于原size图片的坐标
                # 此时坐标格式为xyxy
                det[:, :4] = scale_coords(img.shape[2:], det[:, :4], im0.shape).round()

                *xyxy, _, _ = det[0]
                c1, c2 = (int(xyxy[0]), int(xyxy[1])), (int(xyxy[2]), int(xyxy[3]))
                box = np.array([c1[0], c1[1], c2[0] - c1[0], c2[1] - c1[1],])

            # Print time (inference + NMS)
            # 打印前向传播+nms时间
            # print('%sDone. (%.3fs)' % (s, t2 - t1))

        # 打印总时间
        # print('Done. (%.3fs)' % (time.time() - t0))

        return box

@torch.no_grad()
def init_detect(weights, imgsz):
    print(weights, imgsz)

    # Initialize
    set_logging()

    # 获取设备
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

    # 如果设备为gpu，使用Float16
    half = device.type != 'cpu'  # half precision only supported on CUDA

    # Load model
    # 加载Float32模型，确保用户设定的输入图片分辨率能整除32(如不能则调整为能整除并返回)
    model = attempt_load(weights, map_location=device)  # load FP32 model
    imgsz = check_img_size(imgsz, s=model.stride.max())  # check img_size
    # 设置Float16
    if half:
        model.half()  # to FP16
    
    # 进行一次前向推理,测试程序是否正常
    img = torch.zeros((1, 3, imgsz, imgsz), device=device)  # init img
    _ = model(img.half() if half else img) if device.type != 'cpu' else None  # run once

    return imgsz, device, half, model

@torch.no_grad()
def detect(images, augment=False, conf=0.5, iou_thres=0.45, \
    imgsz=480, visualize=False, \
    weights = os.path.join(os.path.dirname(__file__), "weights/best.pt")):
    # image (c, h, w)
    imgsz, device, half, model = init_detect(weights, imgsz)
    
    # Run inference
    t0 = time.time()
    frame_num = images.shape[0]
    boxes = np.zeros((frame_num, 4))

    for f, img in enumerate(images):
        im0 = img.copy()
        img = torch.from_numpy(img.transpose(2, 0, 1)).to(device) # Tensor
        # 图片也设置为Float16
        img = img.half() if half else img.float()  # uint8 to fp16/32
        img /= 255.0  # 0 ~ 255 to 0.0 ~ 1.0
        # 没有batch_size时，在最前面添加一个轴
        if img.ndimension() == 3:
            img = img.unsqueeze(0) # shape 如 (1,3,384,640)

        # Inference
        t1 = time_synchronized()
        pred = model(img, augment=augment)[0]

        # Apply NMS
        pred = non_max_suppression(pred, conf, iou_thres, classes=False, agnostic=False)
        t2 = time_synchronized()

        # Process detections
        # 对每一张图片作处理
        for i, det in enumerate(pred):  # detections per image
            s = ''
            # 设置打印信息(图片宽高)， s 如‘384*640’
            s += '%gx%g ' % img.shape[2:]  # print string 
            
            if det is not None and len(det):
                # Rescale boxes from img_size to im0 size
                # 调整预测框的坐标：基于resize+pad的图片的坐标-->基于原size图片的坐标
                # 此时坐标格式为xyxy
                det[:, :4] = scale_coords(img.shape[2:], det[:, :4], im0.shape).round()

                *xyxy, _, _ = det[0]
                c1, c2 = (int(xyxy[0]), int(xyxy[1])), (int(xyxy[2]), int(xyxy[3]))
                boxes[f, :] = np.array([c1[0], c1[1], c2[0] - c1[0], c2[1] - c1[1],])
                if visualize:  # Add bbox to image
                    plot_one_box(xyxy, im0, label='', color=(255, 255, 0), line_thickness=1)
                    cv2.imshow("Detection", im0)
                    cv2.waitKey(30)

            # Print time (inference + NMS)
            # 打印前向传播+nms时间
            print('%sDone. (%.3fs)' % (s, t2 - t1))

    # 打印总时间
    print('Done. (%.3fs)' % (time.time() - t0))

    return boxes