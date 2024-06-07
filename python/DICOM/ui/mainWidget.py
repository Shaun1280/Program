from PyQt5.QtWidgets import (QWidget, QGraphicsView, QGraphicsScene,
                             QGraphicsPixmapItem, QHBoxLayout, QMenu, 
                             QMessageBox)
from PyQt5.QtGui import QPixmap, QColor, QImage
from PyQt5.QtCore import Qt, pyqtSignal, QTimer, QEvent, QPoint

import cv2
import os
import numpy as np

from dicom.image import DicomImage
from ui.threads import (ImageLoadThread, AnalyzerCreateThread, AnalyzeFramesThread2,
                        AnalyzerInitFirstFrameThread, AnalyzerResetThread, SaveAnnoThread)

class MainWidget(QWidget):
    # 加载 flag 以及信息
    load_info_signal = pyqtSignal(bool, str)
    # 播放信息 是否结束 frame
    play_info_signal = pyqtSignal(bool, int)
    # analyzer 创建信息
    ananlyzer_create_info_signal = pyqtSignal(bool, str)
    # analyzer 第一初始化信息
    frist_frame_init_info_signal = pyqtSignal(bool, str)
    # 已分析帧数的信号
    analyzed_frames_signal = pyqtSignal(bool, int)
    # zoom_ratio1 修改信号
    zoom_signal = pyqtSignal(int)
    # box 修改完成信号
    modify_box_signal = pyqtSignal(bool, bool)
    # 保存 annotation 信号
    save_anno_signal = pyqtSignal(bool)

    def __init__(self, setting, parent=None):
        super().__init__(parent)

        self.setting = setting

        self.zoom_ratio = 1.0 # 最终缩方比例
        self.zoom_ratio1 = 1.0
        self.zoom_ratio2 = 1.0

        self.original_image_width = 480
        self.original_image_height = 480
        
        self.image = DicomImage()
        self.current_fname = ''

        self.analyzer = None
        self.stop_analyze_frame_by_frame = True

        self.modify_state = -1
        self.modify_box = None
        self.start_point = None
        self.end_point = None

        self.timer = None
        self.images = None
        self.images_gray = None
        self.current_image = None
        self.current_frame = 0 # 当前帧号
        self.total_frames = 0 # 总的帧号

        self.init_first_frame_thread = None
        self.analyzer_reset_thread = None

        self.initUI()

        self.paintPixmap()

    def initUI(self):
        # 显示控件
        self.graphicsView = QGraphicsView(self)
        self.graphicsViewAnalyze = QGraphicsView(self)

        self.graphicsView.setStyleSheet('''
            QGraphicsView {
                border: none;
                background: rgb(255, 255, 255)
            }
        ''')
        self.graphicsViewAnalyze.setStyleSheet('''
            QGraphicsView {
                border: none;
                background: rgb(255, 255, 255)
            }
        ''')

        self.graphicsViewAnalyze.viewport().installEventFilter(self)
        self.graphicsView.viewport().installEventFilter(self)

        layout = QHBoxLayout()
        layout.addWidget(self.graphicsView)
        layout.addWidget(self.graphicsViewAnalyze)
        layout.setContentsMargins(0, 5, 0, 2)
        self.setLayout(layout)

        self.graphicsViewAnalyze.setHidden(True)

        self.pix = QPixmap(self.original_image_width, self.original_image_height)
        self.pix.fill(QColor(200, 200, 200))

        self.pixAnalyze = QPixmap(self.original_image_width, self.original_image_height)
        self.pixAnalyze.fill(QColor(200, 200, 200))

    def paintPixmap(self, analyze=False):
        height = int(self.original_image_height * self.zoom_ratio)
        width = int(self.original_image_width * self.zoom_ratio)

        if self.current_image is None or self.images is None:
            self.pix = self.pix.scaled(height, width, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            self.pixAnalyze = self.pixAnalyze.scaled(height, width, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            self.scene = QGraphicsScene()
            self.scene.addItem(QGraphicsPixmapItem(self.pix))
            self.graphicsView.setScene(self.scene)

            self.sceneAnalyze = QGraphicsScene()
            self.sceneAnalyze.addItem(QGraphicsPixmapItem(self.pixAnalyze))
            self.graphicsViewAnalyze.setScene(self.sceneAnalyze)
        else:
            # 原图像:
            scaled_img = cv2.resize(self.images[self.current_frame], (width, height))
            qimg = QImage(scaled_img, scaled_img.shape[1],
                        scaled_img.shape[0], scaled_img.shape[1] * 3, QImage.Format_RGB888)
            self.pix = QPixmap.fromImage(qimg)

            self.scene = QGraphicsScene()
            self.scene.addItem(QGraphicsPixmapItem(self.pix))
            self.graphicsView.setScene(self.scene)

            if analyze:
                # 通过 opencv 缩方图像
                scaled_img = cv2.resize(self.current_image, (width, height))
                # 先转为 QImage，再放入 QPixmap
                qimg = QImage(scaled_img, scaled_img.shape[1],
                        scaled_img.shape[0], scaled_img.shape[1] * 3, QImage.Format_RGB888)
                self.pixAnalyze = QPixmap.fromImage(qimg)
                
                self.sceneAnalyze = QGraphicsScene()
                self.sceneAnalyze.addItem(QGraphicsPixmapItem(self.pixAnalyze))
                self.graphicsViewAnalyze.setScene(self.sceneAnalyze)
            else:
                self.sceneAnalyze = QGraphicsScene()
                self.sceneAnalyze.addItem(QGraphicsPixmapItem(self.pix))
                self.graphicsViewAnalyze.setScene(self.sceneAnalyze)

    def set_original_image_size(self, width, height):
        self.original_image_width = width
        self.original_image_height = height

    def loadImage(self, fname):
        # 重新设置 images & images_gray
        self.images = None
        self.images_gray = None

        # 重新设置 analyzer
        self.analyzer = None

        # 创建读取 dicom 工作线程
        self.image_load_thread = ImageLoadThread(fname, self)
        self.image_load_thread.load_finish_signal.connect(lambda : {self.loadImageFinish(fname), self.showImage()})
        self.image_load_thread.exception_signal.connect(self.handleExceptionStr)

        # 发送正在读取信号
        self.load_info_signal.emit(True, 'loading {}...'.format(fname))

        # 启动线程
        self.image_load_thread.start()

    def loadImageFinish(self, fname):
        self.load_info_signal.emit(False, '{} loading done.'.format(os.path.basename(fname)))

        self.image_load_thread = None

        # 获取 bgr 和灰度图像
        self.images = self.image.get_images()
        self.images_gray = self.image.get_gray_images()

        # 设置当前帧序号
        self.current_frame = 0
        self.total_frames = len(self.images)

    def saveAnno(self, dirname):
        if self.analyzer.analyzed_frame >= 0 and self.analyzer.analyzed_frame + 1 == self.total_frames:
            save_anno_thread = SaveAnnoThread(dirname, self)
            save_anno_thread.save_finish_signal.connect(lambda :{
                self.save_anno_signal.emit(True)
            })

            save_anno_thread.start()
        else:
            raise Exception('未分析完全部影像序列，不可保存') 

    # =====================image=========================
    def showImage(self, analyze=False, play=False):
        assert self.images is not None

        # 发送播放信号
        self.play_info_signal.emit(self.current_frame + 1 == self.total_frames, self.current_frame)

        if self.current_frame < 0:
            self.current_frame = 0

        # 设置当前帧图像，并绘制
        if analyze == False:
            self.current_image = self.images[self.current_frame]
        else:
            self.current_image = self.analyzer.frame_image_analyzed(
                self.images,
                self.current_frame,
                epiglottis=self.parent().show_epiglottis_box(),
                barium=self.parent().show_barium())
        self.paintPixmap(analyze=analyze)

        if play == True and self.current_frame + 1 == self.total_frames:
            if not self.timer is None:
                self.timer.stop()
                self.timer = None
            # self.current_frame = -1

    def playImage(self, fps=15, analyze=False):
        print('fps: ', fps)
        
        self.timer = QTimer()
        self.timer_gap = 0
        if analyze == False:
            self.timer.timeout.connect(lambda :self.setCurrentFrameByDelta(1, analyze, True))
            self.timer.start(1000.0 / fps)
        else:
            self.timer.timeout.connect(lambda :self.setCurrentFrameByDelta(1, analyze, True))
            self.timer.start(250.0 / fps)

    def stopImage(self):
        if not self.timer is None:
            self.timer.stop()
            self.timer = None

    # 设置当前帧号
    def setCurrentFrame(self, frame, analyze=False):
        if frame == 0 or self.hasImage() == False:
            self.current_frame = 0
        else:
            self.current_frame = frame - 1
            self.showImage(analyze=analyze)

    def setCurrentFrameByDelta(self, delta, analyze=False, play=False):
        if self.hasImage() == True:
            if analyze == False:
                self.current_frame = self.current_frame + delta
                if self.current_frame < 0:
                    self.current_frame += self.total_frames
                elif self.current_frame >= self.total_frames:
                    self.current_frame %= self.total_frames
                self.showImage(analyze=False, play=play)
            else:
                if play == True:
                    assert delta == 1 # delta should be one
                    if self.current_frame + 1 == self.total_frames:
                        self.play_info_signal.emit(True, self.current_frame)
                        if not self.timer is None:
                            self.timer.stop()
                            self.timer = None
                    elif self.current_frame + delta <= \
                        self.analyzer.analyzed_frame and self.timer_gap >= 2:
                        self.current_frame = self.current_frame + delta
                        # display
                        self.showImage(analyze=True, play=play)
                        self.timer_gap = 0
                    else:
                        self.timer_gap += 1
                else:
                    self.current_frame = self.current_frame + delta
                    if self.current_frame < 0:
                        self.current_frame += (self.analyzer.analyzed_frame + 1)
                    elif self.current_frame > self.analyzer.analyzed_frame:
                        self.current_frame %= (self.analyzer.analyzed_frame + 1)
                    self.showImage(analyze=True, play=play)

    def hasImage(self):
        return not self.images is None
    
    def hideGraphicsViewAnalyze(self, hidden):
        self.graphicsViewAnalyze.setHidden(hidden)

        if hidden:
            self.layout().removeWidget(self.graphicsViewAnalyze)
        else:
            self.layout().removeWidget(self.graphicsView)
            self.layout().addWidget(self.graphicsView)
            self.layout().addWidget(self.graphicsViewAnalyze)

        self.set_zoom_ratio2(True, False)
    # =====================zoom======================

    # resize 时调整缩放比例
    def resizeEvent(self, event):
        height = self.height() - 10
        width = self.width() - 10
        if not self.graphicsViewAnalyze.isHidden():
            self.zoom_ratio2 = width / 2 / self.original_image_width
        else:
            self.zoom_ratio2 = height / self.original_image_height
        
        self.zoom_ratio = self.zoom_ratio1 * self.zoom_ratio2
        self.paintPixmap()

    # 连接 zoom_ratio1 缩放信号
    def set_zoom_ratio1(self, delta, value):
        if delta == True: # 通过差值调整大小
            self.zoom_ratio1 += value / 100
        else: # 直接设置大小
            self.zoom_ratio1 = value / 100
        if self.zoom_ratio1 < 0.1:
            self.zoom_ratio1 = 0.1
        elif self.zoom_ratio1 > 2.0:
            self.zoom_ratio1 = 2.0
        self.zoom_signal.emit(int(self.zoom_ratio1 * 100 + 1e-6))
        self.zoom_ratio = self.zoom_ratio1 * self.zoom_ratio2
        self.paintPixmap(self.parent().analyzeChecked) # 重新绘制图像

    # 连接 zoom_ratio2 缩方信号 用于 1:1 显示图像与否
    def set_zoom_ratio2(self, fit_screen, zoom1=True):
        if fit_screen == True:
            if not self.graphicsViewAnalyze.isHidden():
                width = self.width() - 10
                self.zoom_ratio2 = width / 2 / self.original_image_width
            else:
                height = self.height() - 10
                self.zoom_ratio2 = height / self.original_image_height
        else:
            self.zoom_ratio2 = 1.0
        
        if zoom1:
            self.zoom_ratio1 = 1.0

        self.zoom_signal.emit(int(self.zoom_ratio1 * 100 + 1e-6))
        self.zoom_ratio = self.zoom_ratio1 * self.zoom_ratio2
        self.paintPixmap(self.parent().analyzeChecked)
    # =====================analyzer======================
    
    def hasAnalyzer(self):
        return not self.analyzer is None
    
    def createAnalyzer(self):
        analyzer_create_thread = AnalyzerCreateThread(self)
        analyzer_create_thread.analyzer_create_finish_signal.connect(lambda :{
            self.ananlyzer_create_info_signal.emit(False, 'analyzer creating done.')
        })
        analyzer_create_thread.exception_signal.connect(self.handleExceptionStr)

        self.ananlyzer_create_info_signal.emit(True, 'analyzer creating...')

        analyzer_create_thread.start()

    def analyzeFirstFrame(self, _new=True, _detect=False, _dir=''):
        if not self.analyzer_reset_thread is None:
            self.analyzer_reset_thread.quit()
        if not self.init_first_frame_thread is None:
            self.init_first_frame_thread.quit()

        self.init_first_frame_thread = AnalyzerInitFirstFrameThread(_new=_new, _detect=_detect, _dir=_dir, parent=self)
        self.init_first_frame_thread.first_frame_init_finish_signal.connect(lambda :{
            self.frist_frame_init_info_signal.emit(False, 'fisrt frame initilized.')
        })
        self.init_first_frame_thread.exception_signal.connect(self.handleExceptionStr)

        self.frist_frame_init_info_signal.emit(True, 'fisrt frame initializing...')

        self.init_first_frame_thread.start()

    def analyzeReset(self, _new=True, _detect=False, box=None, _dir=''):
        if not self.analyzer_reset_thread is None:
            self.analyzer_reset_thread.quit()
        if not self.init_first_frame_thread is None:
            self.init_first_frame_thread.quit()

        self.analyzer_reset_thread = AnalyzerResetThread(_new=_new, _detect=_detect, box=box, _dir=_dir, parent=self)
        self.analyzer_reset_thread.analyzer_reset_signal.connect(lambda :{
            self.frist_frame_init_info_signal.emit(False, 'analyzer reset.')
        })
        self.analyzer_reset_thread.exception_signal.connect(self.handleExceptionStr)

        self.frist_frame_init_info_signal.emit(True, 'analyzer reseting...')

        self.analyzer_reset_thread.start()

    def handleExceptionStr(self, msg):
        if not self.parent().msgBox is None:
            self.parent().msgBox.close()

        QMessageBox.critical(
            self, 
            'Error',
            '影像分析失败: \n{}'.format(msg),
            buttons=QMessageBox.Ok,
            defaultButton=QMessageBox.Ok
        )

    # 直接分析所有帧
    def analyzeAllFrames(self):
        pass

    # 逐帧分析 可暂停
    def analyzeFrameByFrame(self):
        self.stop_analyze_frame_by_frame = False

        analyze_frames_thread = AnalyzeFramesThread2(self)
        analyze_frames_thread.analyzed_frames_signal.connect(lambda f: {
            self.analyzed_frames_signal.emit(f + 1 == self.total_frames, f)
        })

        analyze_frames_thread.start()
    
    def stopAnalyzeFrameByFrame(self):
        self.stop_analyze_frame_by_frame = True

    # =====================modify========================
    # 修改当前帧图像 bbox
    def handleModifyBox(self, state, first=False):
        # print('state', state)
        if self.modify_state + 1 == state:
            self.modify_state = state
            
            if state == 0:
                self.setCursor(Qt.CrossCursor)

                # 转到第一帧并取消标注显示
                if first:
                    self.setCurrentFrame(1, analyze=False)
                else: # 仅取消标注显示
                    if self.hasImage():
                        self.showImage(analyze=False)

            elif state == 1:
                self.setCursor(Qt.ArrowCursor)

                box = None

                # accept box
                if self.start_point is not None and self.end_point is not None:
                    start_x, start_y = self.start_point
                    end_x, end_y = self.end_point

                    start_x /= self.zoom_ratio
                    start_x = int(round(start_x) + 1e-6)
                    start_y /= self.zoom_ratio
                    start_y = int(round(start_y) + 1e-6)
                    end_x /= self.zoom_ratio
                    end_x = int(round(end_x) + 1e-6)
                    end_y /= self.zoom_ratio
                    end_y = int(round(end_y) + 1e-6)

                    if self.hasImage() and self.hasAnalyzer():
                        box = np.array([start_x, start_y, end_x - start_x, end_y - start_y])
                        self.analyzer.modify_one_frame(
                            self.images_gray,
                            self.images,
                            self.current_frame,
                            box
                        )

                if self.hasImage():
                    self.showImage(True)
                self.modify_box_signal.emit(True, first)
                self.modify_state = -1

                # 是否重新分析
                if first and box is not None:
                    self.showReAnalyzeDialog(box)

    def showReAnalyzeDialog(self, box):
        ret = QMessageBox.question(
                    self,
                    'Message',
                    '已重新框选首帧图像，是否重新分析影像',
                    QMessageBox.Yes | QMessageBox.No,
                    QMessageBox.No
                )

        if ret == QMessageBox.Yes and self.hasAnalyzer():
            self.parent().analyze_history_action.setChecked(False)
            self.parent().toolBarFile.setAnalyzeComboBoxDisabled(False)
            self.analyzeReset(_new=True, _detect=self.analyzer._detect, box=box)

    def getPosInScene(self, point):
        return point.x() - (self.graphicsViewAnalyze.width() // 2 - self.graphicsViewAnalyze.scene().width() // 2), \
            point.y() - (self.graphicsViewAnalyze.height() // 2 - self.graphicsViewAnalyze.scene().height() // 2)

    def posOutOfScene(self, x, y):
        return x < 0 or y < 0 or x >= self.graphicsViewAnalyze.scene().width() or \
                y >= self.graphicsViewAnalyze.scene().height()

    def eventFilter(self, source, event):
        if self.modify_state == 0:
            # 鼠标移动事件
            if event.type() == QEvent.MouseMove:
                # 左键按下拖动
                if event.buttons() == Qt.LeftButton and source == self.graphicsViewAnalyze.viewport():
                    # start_point 不能为空
                    if not self.start_point is None:
                        self.end_point = event.localPos()

                        # 获取在 scene 中的坐标
                        start_x, start_y = self.start_point
                        end_x, end_y = self.getPosInScene(self.end_point)

                        # 重新绘制 scene
                        scene = QGraphicsScene()
                        scene.addItem(QGraphicsPixmapItem(self.pix))
                        self.graphicsViewAnalyze.setScene(scene)

                        # 防止超出边界
                        if self.posOutOfScene(end_x, end_y):
                            end_x = min(end_x, self.graphicsViewAnalyze.scene().width() - 1)
                            end_y = min(end_y, self.graphicsViewAnalyze.scene().height() - 1)
                        
                        self.end_point = (end_x, end_y)

                        # 左上到右下
                        if end_x > start_x and end_y > start_y:
                            self.graphicsViewAnalyze.scene().addRect(
                                start_x, start_y,
                                end_x - start_x, end_y - start_y,
                                QColor(255, 185, 15)
                            )
                        else:
                            self.end_point = None

            elif event.type() == QEvent.MouseButtonPress:
                if event.button() == Qt.LeftButton and source == self.graphicsViewAnalyze.viewport():
                    self.start_point = event.localPos()
                    start_x, start_y = self.getPosInScene(self.start_point)
                    self.start_point = (start_x, start_y)

                    if self.posOutOfScene(start_x, start_y):
                        self.start_point = None
                elif event.button() == Qt.RightButton:
                    self.cancelModifyBox()

            elif event.type() == QEvent.MouseButtonRelease:
                if event.button() == Qt.LeftButton and source == self.graphicsViewAnalyze.viewport():
                    if not self.start_point is None and not self.end_point is None:
                        menu = QMenu()
                        ok = menu.addAction('OK')
                        cancel = menu.addAction('Cancel')

                        end_x, end_y = self.end_point
                        end_x += (self.graphicsViewAnalyze.x() + self.graphicsViewAnalyze.width() // 2 - self.graphicsViewAnalyze.scene().width() // 2)
                        end_y += (self.graphicsViewAnalyze.height() // 2 - self.graphicsViewAnalyze.scene().height() // 2)
                        global_pos = self.mapToGlobal(QPoint(end_x, end_y))
                        action = menu.exec(QPoint(global_pos.x(), global_pos.y()))

                        if action == cancel:
                            self.cancelModifyBox()
                        elif action == ok:
                            self.handleModifyBox(1, self.parent().modify_first_box_action.isEnabled())

        if event.type() == QEvent.Wheel and self.parent().ctrl_pressed:
            return True
        return super().eventFilter(source, event)

    def cancelModifyBox(self):
        self.start_point = None
        self.end_point = None

        # 还原 scene
        scene = QGraphicsScene()
        scene.addItem(QGraphicsPixmapItem(self.pixAnalyze))
        self.graphicsViewAnalyze.setScene(scene)

        self.handleModifyBox(1, self.parent().modify_first_box_action.isEnabled())