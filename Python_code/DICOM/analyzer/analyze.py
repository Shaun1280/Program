import numpy as np
import cv2
import time
import os
from matplotlib import pyplot as plt

from .fgExtractor import ViBe, run_vibe
from .tracker import track, ECO
from .detector import detect, YoloDetector
from . import utils
# from . import segment
from . import barium

class Analyzer:
    def __init__(self):
        self.vibe = ViBe()
        self.detector = YoloDetector()
        self.tracker = ECO()
        
        # self.colors = segment.get_colors()

        self.initialized = False

        self.analyzed_frame = -1

    # 初始化，针对第一帧图像
    def init_analyze(self, images_gray, images, _new=True, _detect=False, 
                     save=False, box=None, _dir=''):
        if self.initialized == True:
            return

        # 获取帧数
        self.frame_num = images.shape[0]

        self._new = _new
        self._detect = _detect
        self._save = save

        if not box is None:
            self._new = True
        
        # 如果不重新识别
        if self._new == False:
            success1, boxes = utils.read_all_boxes(os.path.join(_dir, 'result.boxes'))
            if success1:
                self.boxes = boxes

            success2, arr = utils.read_npy(os.path.join(_dir, 'result.markers.npy'))
            if success2:
                self.markers_roi = arr

            success3, roi = utils.read_all_boxes(os.path.join(_dir, 'result.roi'))
            if success3:
                roi = roi.astype(np.int32)
                self.roi1 = roi[0]

            # 获取已有结果失败，需要重新识别
            if not success1 or not success2 or not success3:
               self._new = True

        # 如果需要重新识别
        if self._new:
            self.boxes = np.zeros((self.frame_num, 4))
            if box is not None: # 使用手动标记的位置
                self.boxes[0] = box.copy()
            else: # 识别出第一帧会厌软骨的位置
                box = self.detector.detect_frame(images[0])
                # box = None # 测试没有跟踪框
                if box is None:
                    self.boxes[0] = np.array([0, 0, 0, 0])
                else:
                    self.boxes[0] = box
            self.get_roi1(self.boxes[0], images[0].shape[:2])

        # 初始化 markers_roi 用于标记 roi 中的钡餐
        if self._new:
            self.markers_roi = np.zeros((self.frame_num, self.roi1[3], self.roi1[2]))

        # 初始化背景
        gray_within_roi = self.get_img_roi1(images_gray[0])
        gray_within_roi = utils.hist_img(gray_within_roi)
        self.vibe.init_background(gray_within_roi)

        self.initialized = True

        print("initialization Done.")

    # 获取会厌软骨 bbox，f 为帧
    def get_epiglottis_box(self, img, f):
        box = None
        if self._new:
            if self._detect: # detect
                if f == 0: # 第一帧已经获取
                    box = self.boxes[0]
                else:
                    box = self.detect_box(img)
            else: # else track
                if f == 0:
                    box = self.init_track(img)
                    # for _ in range(60):
                    #     self.update_track(img)
                else:
                    box = self.update_track(img)
        else:
            box = self.boxes[f]
        return box

    def detect_box(self, img):
        box = self.detector.detect_frame(img)
        return box

    def init_track(self, img):
        loose = self.boxes[0]
        loose[0], loose[1] = loose[0] - 1, loose[1] - 1
        loose[2], loose[3] = loose[2] + 2, loose[3] + 2

        # 只跟踪局部图片
        img_within_roi = self.get_img_roi1(img)
        box_in_roi = np.array([
            loose[0] - self.roi1[0],
            loose[1] - self.roi1[1],
            loose[2], loose[3]
        ])

        self.tracker.init(img_within_roi, box_in_roi)#self.boxes[0])
        return loose

    def update_track(self, img):
        img_within_roi = self.get_img_roi1(img)
        ret = self.tracker.update(img_within_roi)
        box = np.array([
            ret[0] + self.roi1[0],
            ret[1] + self.roi1[1],
            ret[2], ret[3]
        ])
        return box

    def get_roi1(self, box, imgsz):
        x, y, w, h = list(map(int, box))
        img_height = imgsz[0]
        img_width = imgsz[1]
        p1 = (int(round(max(0, x - w)) + 1e-6), int(round(max(0, y - h * 2.0)) + 1e-6))
        p2 = (int(round(min(img_width, x + w * 1.5)) + 1e-6), int(round(min(img_height, y + h * 5.0)) + 1e-6))
        self.roi1 = np.array([p1[0], p1[1], p2[0] - p1[0], p2[1] - p1[1]], np.int32)

    def get_img_roi1(self, img):
        return img[self.roi1[1]:self.roi1[1] + self.roi1[3], self.roi1[0]:self.roi1[0] + self.roi1[2]]

    # 获取 box 在 roi 中的区域
    def box_in_roi(self, box):
        roi_x1, roi_y1 = self.roi1[0], self.roi1[1]
        roi_x2, roi_y2 = self.roi1[0] + self.roi1[2], self.roi1[1] + self.roi1[3]
        box_x1, box_y1 = box[0], box[1]
        box_x2, box_y2 = box[0] + box[2], box[1] + box[3]

        if box_x1 > roi_x2 or box_y1 > roi_y2:
            return np.array([roi_x2, roi_y2, 0, 0])
        elif box_x2 < roi_x1 or box_y2 < roi_y1:
            return np.array([roi_x1, roi_y1, 0, 0])
        else:
            x1, y1 = max(roi_x1, box_x1), max(roi_y1, box_y1)
            x2, y2 = min(roi_x2, box_x2), min(roi_y2, box_y2)
            return np.array([x1, y1, x2 - x1, y2 - y1])

    def get_seg_map(self, gray):
        gray_within_roi = self.get_img_roi1(gray)
        gray_within_roi = utils.hist_img(gray_within_roi)
        high = utils.hist_gray_level(60 + 20 * 2)
        low = utils.hist_gray_level(60 - 25)
        return self.vibe.update_background(gray_within_roi, low, high)

    def analyze_all(self, images_gray, images):
        since = time.time()
        for f in range(self.frame_num):
            if f % 30 == 0:
                since = time.time()

            gray = images_gray[f]
            img = images[f]

            # 当前帧处理起始时间
            since = time.time()

            # 获取跟踪框
            box = self.get_epiglottis_box(img, f)
            self.boxes[self.analyzed_frame + 1] = box.copy()

            if self._new:
                # 返回提取的前景 = 255
                segmap = self.get_seg_map(gray)
                # img_seg = extract_barium(gray, segmap, box)
                markers_roi, _ = barium.get_markers_roi(
                    self.get_img_roi1(img),
                    self.get_img_roi1(gray),
                    segmap,
                    self.roi1,
                    box
                )
                # cv2.imshow('segmap', segmap)
                self.markers_roi[self.analyzed_frame + 1] = markers_roi.copy()

            img_marked = self.frame_image_analyzed(images, f, True, True)
            cv2.imshow('img_marked', img_marked)

            self.analyzed_frame = f
            
            # if self._save:
            #     # np.savetxt('result/test_roi.txt', np.array(self.roi1), fmt='%.3f', delimiter=',')
            #     img_tmp = np.concatenate((
            #         #cv2.cvtColor(img_within_roi1, cv2.COLOR_RGB2GRAY),
            #         # img_within_roi1,
            #         # out,
            #         #segmap,
            #         # cv2.cvtColor(segmap, cv2.COLOR_GRAY2BGR),
            #     ), axis=1)
            #     print('saving', 'analyzer/res_seg/{}.jpg'.format(str(f).zfill(5)))
            #     cv2.imwrite('analyzer/res_seg/{}.jpg'.format(str(f).zfill(5)), img_tmp)

            if (f - 29) % 30 == 0:
                print("analyzing {} th frame, fps = {}".format(f, 1.0 / (time.time() - since)))
            
            if (cv2.waitKey(30) & 0xff) == ord('q'):
                break

        cv2.destroyAllWindows()

    def analyze_one_frame(self, images_gray, images):
        if self.analyzed_frame + 1 == len(images): # 0 indexed
            return True
        
        # 首帧目标未检测到，分析失败
        if self.analyzed_frame == -1 and self.boxes[0][2] == 0 and self.boxes[0][3] == 0:
            raise Exception('未检测出首帧目标，需手动框选')

        gray = images_gray[self.analyzed_frame + 1]
        img = images[self.analyzed_frame + 1]

        # 获取跟踪框
        box = self.get_epiglottis_box(img, self.analyzed_frame + 1)
        if box is None:
            box = np.array([0, 0, 0, 0])
        self.boxes[self.analyzed_frame + 1] = box.copy()

        # if self._new: # 用于查看 socre map
        #    print(self.analyzed_frame + 2, self.tracker.tracker.std_score)
        #     x = np.arange(0, self.tracker.tracker.score.shape[0], 1)
        #     y = np.arange(0, self.tracker.tracker.score.shape[1], 1)
        #     plt.clf()
        #     xx, yy = np.meshgrid(x, y)
        #     plt.pcolor(xx, yy, self.tracker.tracker.score, cmap='jet')
        #     plt.savefig(os.path.join(os.path.dirname(__file__), 'score/{}.jpg'.format(str(self.analyzed_frame + 1).zfill(5))))

        # 返回提取的前景 = 255
        if self._new:
            box = self.box_in_roi(box)
            segmap = self.get_seg_map(gray)
            markers_roi, _ = barium.get_markers_roi(
                self.get_img_roi1(img),
                self.get_img_roi1(gray),
                segmap,
                self.roi1,
                box
            )
            self.markers_roi[self.analyzed_frame + 1] = markers_roi.copy()

        self.analyzed_frame = self.analyzed_frame + 1

        return True

    def modify_one_frame(self, images_gray, images, f, box):
        if f < 0 or f > self.analyzed_frame:
            return

        gray = images_gray[f]
        img = images[f]

        # 返回提取的前景 = 255
        box_roi = self.box_in_roi(box)
        segmap = self.get_seg_map(gray)
        markers_roi, _ = barium.get_markers_roi(
            self.get_img_roi1(img),
            self.get_img_roi1(gray),
            segmap,
            self.roi1,
            box_roi
        )
        self.markers_roi[f] = markers_roi.copy()
        self.boxes[f] = box.copy()

    # 获取跟踪第一帧目标框
    def get_tracking_first_box(self):
        anno = self.boxes[0]
        anno[0], anno[1] = anno[0] - 1, anno[1] - 1
        anno[2], anno[3] = anno[2] + 2, anno[3] + 2
        return anno

    def isinitialized(self):
        return self.initialized
    
    def reset(self, images_gray, images, _new=True, _detect=False, box=None, _dir=''):
        self.initialized = False
        self.analyzed_frame = -1

        self.init_analyze(images_gray, images, _new=_new, _detect=_detect, box=box, _dir=_dir)

    # 初始化后的第一帧图像 (是否带会厌软骨框)
    def image_initialized(self, images, epiglottis=True):
        ret_image = images[0].copy()
        if epiglottis == True:
            ret_image = utils.get_image_with_box(images[0], self.boxes[0])
        return ret_image

    # 分析后的第 f 帧图像（是否带会厌软骨框、是否有钡餐标记）
    def frame_image_analyzed(self, images, f, epiglottis=True, barium=False):
        ret_image = images[f].copy()
        if barium == True:
            markers = np.zeros((images[f].shape[0], images.shape[1]), np.uint8)
            markers[self.roi1[1]:self.roi1[1] + self.roi1[3], \
                    self.roi1[0]:self.roi1[0] + self.roi1[2]] = self.markers_roi[f]
            ret_image[markers == 1] = (130, 221, 238)
            ret_image[markers == 2] = (80, 127, 255)
        if epiglottis == True:
            ret_image = utils.get_image_with_box(ret_image, self.boxes[f])

        ret_image = cv2.cvtColor(ret_image, cv2.COLOR_BGR2RGB)
        return ret_image

    def get_pix_barium(self, f, val):
        ret = (self.markers_roi[f] == val).sum()
        if ret <= 25:
            ret = 0
        return ret
    
    def save_anno(self, dirname):
        utils.record(os.path.join(dirname, 'result.boxes'), self.boxes)
        utils.record_bin(os.path.join(dirname, 'result.markers'), self.markers_roi)
        saved_roi = np.zeros((1, 4))
        saved_roi[0] = self.roi1
        utils.record(os.path.join(dirname, 'result.roi'), saved_roi)

    # ----------------------------------------
    def track_epiglottis(self, images):
        anno = self.detector.detect_frame(images[0])
        anno[0], anno[1] = anno[0] - 1, anno[1] - 1
        anno[2], anno[3] = anno[2] + 2, anno[3] + 2
        # boxes, times = track.siamse_track(self.images, anno)
        # utils.record('result/test.txt', boxes, times)
        # track.kcf_dsst_track(self.images, anno)
        track.eco_track(images, anno)

    def track_barium(self, images_gray):
        run_vibe(images_gray)

    def show_track_epiglottis_result(self, images):
        utils.show_result(images)

    def detect_all_boxes(self, images):
        boxes = detect(images)
        utils.record('analyzer/result/test.txt', boxes, np.zeros((boxes.shape[0], 1)))
    # -------------------------------------------------------

    