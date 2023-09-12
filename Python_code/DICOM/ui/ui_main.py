import os
import cv2
import shutil
import torch

import warnings
warnings.filterwarnings("ignore")

from PyQt5.QtWidgets import QMainWindow, QMessageBox
from PyQt5.QtCore import QSettings, Qt
from PyQt5.QtGui import QIcon

from ui.bars.menuBar import MenuBar
from ui.bars.toolBar import ToolBarFile, ToolBarPlay, ToolBarAnno
from ui.bars.statusBar import StatusBar
from ui.bars.actions import (OpenAndAnalyzeAction, ExportImageAction, 
                             PlayAction, StopAction, FrameAction, ModifyBoxAction,
                             ModifyFirstBoxAction, SaveAnnoAction, AnalyzeHistoryAction,
                             CancelModifyBoxAction)
from ui.mainWidget import MainWidget
from ui.infoDockWidget import InfoDockWidget
from ui.exportWidget import ExportWidget

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(1360, 768)

        self.setWindowTitle('Dicom')
        self.setWindowIcon(QIcon(os.path.join(os.path.dirname(__file__),
                         './images/radiology.png')))
        
        # 创建 QSettings，配置文件是 .config
        self.setting = QSettings(
            os.path.join(os.path.dirname(__file__), '.config')
            , QSettings.IniFormat)
        self.setting.setIniCodec('UTF-8')

        self.analyzeChecked = 0

        self.ctrl_pressed = False

        self.open_fname = ''
        self.save_dirname = ''
        self.has_saved_result = False

        self.msgBox = None

        self.initActions()

        # 设置工具栏
        self.toolBarFile = ToolBarFile(self.setting, self) # 工具栏 文件
        self.toolBarFile.visibilityChanged.connect(lambda visible: {
            self.menuBar().action_file_tool_bar.setChecked(visible)
        })
        self.addToolBar(self.toolBarFile)

        self.toolBarAnno = ToolBarAnno(self.setting, self) # 工具栏 标注
        self.toolBarAnno.visibilityChanged.connect(lambda visible: {
            self.menuBar().action_anno_tool_bar.setChecked(visible)
        })
        self.addToolBar(self.toolBarAnno)

        self.toolBarPlay = ToolBarPlay(self.setting, self) # 工具栏 显示
        self.toolBarPlay.visibilityChanged.connect(lambda visible: {
            self.menuBar().action_view_tool_bar.setChecked(visible)
        })
        self.addToolBar(self.toolBarPlay)
        self.insertToolBarBreak(self.toolBarPlay) # 换行

        # 设置菜单
        self.setMenuBar(MenuBar(self.setting, self))
        self.menuBar().annotate_signal.connect(self.handleAnnotateSignal)
        
        # 设置状态栏
        self.setStatusBar(StatusBar(self.setting, self))
        self.statusBar().current_frame_signal.connect(self.setMainWidgetFrame)

        # 设置 centralWidget
        self.mainWidget = MainWidget(self.setting, self)
        self.setCentralWidget(self.mainWidget)
        self.mainWidget.load_info_signal.connect(self.handleLoadInfoSignal)
        self.mainWidget.play_info_signal.connect(self.handlePlayInfoSignal)
        self.mainWidget.ananlyzer_create_info_signal.connect(self.handleAnanlyzerCreateInfoSignal)
        self.mainWidget.frist_frame_init_info_signal.connect(self.handleFirstFrameInitInfoSignal)
        self.mainWidget.analyzed_frames_signal.connect(self.handleAnalyzedFramesSignal)
        self.mainWidget.zoom_signal.connect(self.statusBar().handleZoomSignal)
        self.mainWidget.modify_box_signal.connect(self.handleModifyBoxTriggered)
        self.mainWidget.save_anno_signal.connect(self.handleSaveSignal)

        # 设置信息显示控件
        self.infoDockWidget = InfoDockWidget(self.setting, 'Tabs', self)
        self.addDockWidget(Qt.RightDockWidgetArea, self.infoDockWidget)
        self.infoDockWidget.visibilityChanged.connect(lambda visible: {
            self.menuBar().action_tabs.setChecked(visible)
        })
    
    def initFileActions(self):
        self.open_action = OpenAndAnalyzeAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/folder.png')),
            '打开',
            self
        )
        self.open_action.open_signal.connect(self.handleOpenSignal)
        self.open_action.analyze_signal.connect(self.handleAnalyzeSignal)
        self.open_analyze_action = OpenAndAnalyzeAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/open_analyze.png')),
            '打开并分析',
            self
        )
        self.open_analyze_action.open_signal.connect(self.handleOpenSignal)
        self.open_analyze_action.analyze_signal.connect(self.handleAnalyzeSignal)
        self.analyze_action = OpenAndAnalyzeAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/analyze.png')),
            '分析',
            self
        )
        self.analyze_action.analyze_signal.connect(self.handleAnalyzeSignal)
        # 无影像时不可设置分析
        self.analyze_action.setDisabled(True)

        self.analyze_history_action = AnalyzeHistoryAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/history.png')),
            '使用已有分析结果',
            self
        )
        self.analyze_history_action.use_history_signal.connect(self.handleUseHistorySignal)

        self.export_action = ExportImageAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/export.png')),
            '导出图像',
            self
        )
        self.export_action.triggered.connect(self.showExportWidget)

    def initViewActions(self):
        self.play_action = PlayAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/play-button.png')),
            '播放',
            self
        )
        self.play_action.play_status_signal.connect(self.changePlayStatus)
        self.stop_action = StopAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/stop.png')),
            '停止',
            self
        )
        self.stop_action.play_status_signal.connect(self.changePlayStatus)

        self.prev_frame_action = FrameAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/back.png')),
            '前一帧',
            'LEFT',
            step=-1,
            parent=self
        )
        self.prev_frame_action.frame_step_signal.connect(self.handleFrameStepSignal)
        self.next_frame_action = FrameAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/next.png')),
            '后一帧',
            'RIGHT',
            step=1,
            parent=self
        )
        self.next_frame_action.frame_step_signal.connect(self.handleFrameStepSignal)
        self.prev_10frame_action = FrameAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/rewind.png')),
            '前十帧',
            'Ctrl+LEFT',
            step=-10,
            parent=self
        )
        self.prev_10frame_action.frame_step_signal.connect(self.handleFrameStepSignal)
        self.next_10frame_action = FrameAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/fast-forward.png')),
            '后十帧',
            'Ctrl+RIGHT',
            step=10,
            parent=self
        )
        self.next_10frame_action.frame_step_signal.connect(self.handleFrameStepSignal)

    def initAnnoActions(self):
        self.modify_box_action = ModifyBoxAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/rect.png')),
            '当前帧跟踪框',
            parent=self
        )
        self.modify_box_action.triggered.connect(lambda: self.handleModifyBoxTriggered(False, False))
        self.modify_first_box_action = ModifyFirstBoxAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/one.png')),
            '首帧跟踪框',
            parent=self
        )
        self.cancel_modify_box_action = CancelModifyBoxAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/undo.png')),
            '取消重新标注',
            parent=self
        )
        self.cancel_modify_box_action.triggered.connect(self.cancelModifyBox)


        self.modify_first_box_action.triggered.connect(lambda :self.handleModifyBoxTriggered(False, True))
        self.save_anno_action = SaveAnnoAction(
            self.setting,
            QIcon(os.path.join(os.path.dirname(__file__), './images/save2.png')),
            '保存标注',
            parent=self
        )
        self.save_anno_action.save_signal.connect(self.handleSaveSignal)

    def initActions(self):
        self.initFileActions()
        self.initViewActions()
        self.initAnnoActions()
    # ===================================================

    # 修改播放状态
    def changePlayStatus(self, status):
        if status == 0:
            self.play_action.play_status = 0
            self.play_action.setIcon(QIcon(os.path.join(os.path.dirname(__file__), './images/play-button.png')))
            self.play_action.setText('播放')
            
            self.export_action.setDisabled(False)

            # 播放结束可设置 fps 
            self.toolBarPlay.fps_slider.setDisabled(False)
            self.toolBarPlay.fps_text.setDisabled(False)

            # 播放结束可设置 帧号
            self.statusBar().setFrameWidgetDisabled(False)

            # 播放结束可设置检测方式
            if not self.analyze_history_action.isChecked():
                self.toolBarFile.setAnalyzeComboBoxDisabled(False)
            if self.has_saved_result:
                self.analyze_history_action.setDisabled(False)

            if self.analyzeChecked == True:
                # 停止逐帧分析线程
                self.mainWidget.stopAnalyzeFrameByFrame()
                # 可重新标注跟踪框
                self.modify_box_action.setDisabled(False)

                if self.mainWidget.modify_state == -1:
                    self.modify_first_box_action.setDisabled(False)

            # 可设置分析
            self.analyze_action.setDisabled(False)

            # 停止播放
            self.mainWidget.stopImage()

        else:
            # 有影像时才改变播放状态
            if self.mainWidget.hasImage() == False:
                self.play_action.play_status = 0
                return
            
            self.play_action.play_status = 1
            self.play_action.setIcon(QIcon(os.path.join(os.path.dirname(__file__), './images/pause.png')))
            self.play_action.setText('暂停')

            self.export_action.setDisabled(True)

            # 播放时暂不可设置 fps
            self.toolBarPlay.fps_slider.setDisabled(True)
            self.toolBarPlay.fps_text.setDisabled(True)

            # 播放时暂不可设置帧号
            self.statusBar().setFrameWidgetDisabled(True)

            # 播放时暂不可设置检测方式
            self.toolBarFile.setAnalyzeComboBoxDisabled(True)
            self.analyze_history_action.setDisabled(True)

            # 如果选用分析，在另一个线程中逐帧分析
            if self.analyzeChecked == True:
                self.mainWidget.analyzeFrameByFrame()

            # 不可设置分析
            self.analyze_action.setDisabled(True)

            # 不可重新标注跟踪框
            self.modify_box_action.setDisabled(True)
            self.modify_first_box_action.setDisabled(True)

            # 开始按照 fps 播放
            self.mainWidget.playImage(
                fps=self.toolBarPlay.fps_slider.value(),
                analyze=self.analyzeChecked
            )

    # 加载医学影像
    def handleOpenSignal(self, fname):
        try:
            self.mainWidget.loadImage(fname)
            self.open_fname = fname
        except Exception as e:
            # 发生异常，弹窗警告
            QMessageBox.warning(
                self, 
                'Warning',
                '.dic文件打开失败{}'.format(e),
                buttons=QMessageBox.Ok,
                defaultButton=QMessageBox.Ok
            )

    # 影像当前加载的信息（是否加载完成）以及 flag 处理
    def handleLoadInfoSignal(self, flag, info):
        self.changeStatusBarInfo(info)

        if flag == True: # 正在加载
            self.open_action.setDisabled(True)
            self.open_analyze_action.setDisabled(True)
            self.analyze_action.setDisabled(True)
            self.play_action.setDisabled(True)
            self.stop_action.setDisabled(True)
            self.export_action.setDisabled(True)

            self.analyze_history_action.setChecked(False)
            self.analyze_history_action.setDisabled(True)

            # 停止播放
            self.changePlayStatus(0)
            # 暂不可设置 fps
            self.toolBarPlay.fps_slider.setDisabled(True)
            self.toolBarPlay.fps_text.setDisabled(True)

            # 暂不可设置帧号
            self.statusBar().setFrameWidgetDisabled(True)
            self.prev_frame_action.setDisabled(True)
            self.next_frame_action.setDisabled(True)
            self.prev_10frame_action.setDisabled(True)
            self.next_10frame_action.setDisabled(True)

            # 不可重新标注跟踪框
            self.modify_box_action.setDisabled(True)
            self.modify_first_box_action.setDisabled(True)

            self.infoDockWidget.setTab2Info(None)

            # more actions should be disabled ...

        else: # 停止加载
            self.open_action.setDisabled(False)
            self.open_analyze_action.setDisabled(False)
            self.analyze_action.setDisabled(False)
            self.play_action.setDisabled(False)
            self.stop_action.setDisabled(False)
            self.export_action.setDisabled(False)

            # 加载完成后可设置 fps
            self.toolBarPlay.fps_slider.setDisabled(False)
            self.toolBarPlay.fps_text.setDisabled(False)

            # 可设置帧号
            self.statusBar().setFrameWidgetDisabled(False)
            self.prev_frame_action.setDisabled(False)
            self.next_frame_action.setDisabled(False)
            self.prev_10frame_action.setDisabled(False)
            self.next_10frame_action.setDisabled(False)

            # more actions should be enabled ...

            # 设置 dockwidget tab1 患者信息
            self.infoDockWidget.setTab1Info(self.mainWidget.image.info)

            # 如果启用分析
            if self.analyzeChecked == 1:
                if self.mainWidget.hasAnalyzer() == False:
                    # 创建 ananlyzer，并在创建完成 handleAnanlyzerCreateInfoSignal 中初始化第一帧
                    self.mainWidget.createAnalyzer()
                else: # 已有 analyzer，直接分析第一帧
                    if self.toolBarFile.analyzeMethodIndex() == 0:
                        self.mainWidget.analyzeFirstFrame(_detect=False)
                    elif self.toolBarFile.analyzeMethodIndex() == 1:
                        self.mainWidget.analyzeFirstFrame(_detect=True)

            self.createResultFolder()
            self.checkResulsExist(True)

    # 创建结果保存文件夹
    def createResultFolder(self):
        stem, suffix = os.path.splitext(self.open_fname)

        if not os.path.exists(stem):
            os.makedirs(stem)
        
        self.save_dirname = stem
    
    # 检查是否有有保存的结果
    def checkResulsExist(self, allowSetChecked=False):
        boxes_exist = os.path.exists(os.path.join(self.save_dirname, 'result.boxes'))
        markers_exist = os.path.exists(os.path.join(self.save_dirname, 'result.markers.npy'))
        roi_exists = os.path.exists(os.path.join(self.save_dirname, 'result.roi'))

        self.has_saved_result = (boxes_exist and markers_exist and roi_exists)
        self.analyze_history_action.setDisabled(not self.has_saved_result)

        if self.has_saved_result and allowSetChecked:
            self.msgBox = QMessageBox()
            self.msgBox.setWindowTitle('Message')
            self.msgBox.setText('已有分析结果，是否使用?')
            self.msgBox.setWindowModality(Qt.NonModal)
            self.msgBox.setWindowIcon(QIcon(os.path.join(os.path.dirname(__file__), './images/radiology.png')))
            self.msgBox.setIcon(QMessageBox.Information)
            self.msgBox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
            self.msgBox.setDefaultButton(QMessageBox.Yes)

            self.msgBox.show()

            self.msgBox.buttonClicked.connect(self.handleSelfMsgBoxClicked)

    def handleSelfMsgBoxClicked(self, button):
        assert not self.msgBox is None
        if button == self.msgBox.buttons()[0]:
            self.analyze_history_action.setChecked(True)
            self.toolBarFile.setAnalyzeComboBoxDisabled(True)
            self.handleUseHistorySignal(True)

    # 保存标注结果
    def handleSaveSignal(self, flag=False):
        if flag == False:
            try:
                self.modify_box_action.setDisabled(True)
                self.modify_first_box_action.setDisabled(True)

                self.open_action.setDisabled(True)
                self.open_analyze_action.setDisabled(True)

                self.toolBarFile.setAnalyzeComboBoxDisabled(True)

                self.mainWidget.saveAnno(self.save_dirname)
            except Exception as e:
                self.modify_box_action.setDisabled(False)
                self.modify_first_box_action.setDisabled(False)

                self.open_action.setDisabled(False)
                self.open_analyze_action.setDisabled(False)

                if not self.analyze_history_action.isChecked():
                    self.toolBarFile.setAnalyzeComboBoxDisabled(False)

                QMessageBox.warning(
                    self, 
                    'Warning',
                    '标注结果保存失败: \n{}'.format(e),
                    buttons=QMessageBox.Ok,
                    defaultButton=QMessageBox.Ok
                )
        else: # 保存结束
            self.modify_box_action.setDisabled(False)
            self.modify_first_box_action.setDisabled(False)

            self.open_action.setDisabled(False)
            self.open_analyze_action.setDisabled(False)

            if not self.analyze_history_action.isChecked():
                self.toolBarFile.setAnalyzeComboBoxDisabled(False)

            self.checkResulsExist()
                
            QMessageBox.information(
                self, 
                'Information',
                '标注结果已成功保存至: \n{}'.format(self.save_dirname),
                buttons=QMessageBox.Ok,
                defaultButton=QMessageBox.Ok
            )
    
    def handleUseHistorySignal(self, flag):
        if flag: # 使用已有结果
            self.toolBarFile.setAnalyzeComboBoxDisabled(True)
            pass
        else:
            self.toolBarFile.setAnalyzeComboBoxDisabled(False)
            pass

        if self.mainWidget.hasAnalyzer() and self.mainWidget.hasImage():
            if flag:
                self.mainWidget.analyzeReset(_new=False, _dir=self.save_dirname)
            else:
                self.mainWidget.analyzeReset(
                    _detect=bool(self.toolBarFile.analyzeMethodIndex())
                )
    
    # 显示导出组件
    def showExportWidget(self):
        exportWidget = ExportWidget(self)
        exportWidget.export_signal.connect(self.handleExportSignal)
        exportWidget.show()

    # 处理导出信号
    def handleExportSignal(self, l, r, epiglottis, barium):
        try:
            print('export', l, r, epiglottis, barium)

            export_dir = os.path.join(self.save_dirname, 'export')
            if not os.path.exists(export_dir):
                os.makedirs(export_dir)
            else:
                shutil.rmtree(export_dir)
                os.makedirs(export_dir)

            assert not self.mainWidget.images is None

            msgBox = QMessageBox()
            msgBox.setWindowTitle('Information')
            msgBox.setWindowIcon(self.export_action.icon())

            for f in range(l, r + 1):
                img = None
                analyzer = self.mainWidget.analyzer
                if self.mainWidget.hasAnalyzer() and f - 1 <= analyzer.analyzed_frame:
                    img = analyzer.frame_image_analyzed(
                        self.mainWidget.images,
                        f - 1,
                        epiglottis,
                        barium
                    )
                else:
                    img = self.mainWidget.images[f - 1]

                export_path = os.path.join(export_dir, '{}.jpg'.format(str(f - 1).zfill(5)))

                img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
                cv2.imwrite(export_path, img)

                msgBox.setText('正在导出: \n{}'.format(export_path))
                msgBox.show()

                cv2.waitKey(10)
            
            QMessageBox.information(
                self, 
                'Information',
                '影像导出成功至: \n{}'.format(export_dir),
                buttons=QMessageBox.Ok,
                defaultButton=QMessageBox.Ok
            )

        except Exception as e:
            QMessageBox.warning(
                self, 
                'Warning',
                '导出失败: \n{}'.format(e),
                buttons=QMessageBox.Ok,
                defaultButton=QMessageBox.Ok
            )
    # ===================================================

    # 影像播放信息处理
    def handlePlayInfoSignal(self, isEnd, frame):
        # print('ui_main-handlePlayInfoSignal-frame:', frame)
        
        if isEnd: # 达到最后一帧，停止播放
            self.changePlayStatus(0)

        # 修改 statusBar 显示的帧号
        if self.analyzeChecked == 0:
            self.statusBar().setFrameWidget(frame + 1, self.mainWidget.total_frames)
        else:
            if self.mainWidget.hasAnalyzer() == True:
                self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, self.mainWidget.analyzer.analyzed_frame + 1)
                
                if self.mainWidget.analyzer.initialized:
                    self.infoDockWidget.setTab2Info(
                        self.mainWidget.current_frame + 1,
                        self.mainWidget.analyzer.boxes[max(0, self.mainWidget.current_frame)],
                        self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 1),
                        self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 2)
                    )

    # 处理播放前进和后退信号
    def handleFrameStepSignal(self, delta):
        self.mainWidget.setCurrentFrameByDelta(delta, analyze=self.analyzeChecked)

        if self.mainWidget.hasImage() == True:
            # 修改 statusBar 显示的帧号
            if self.analyzeChecked == False:
                self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, self.mainWidget.total_frames)
            else:
                self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, self.mainWidget.analyzer.analyzed_frame + 1)

                if self.mainWidget.hasAnalyzer():
                    self.infoDockWidget.setTab2Info(
                        self.mainWidget.current_frame + 1,
                        self.mainWidget.analyzer.boxes[max(0, self.mainWidget.current_frame)],
                        self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 1),
                        self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 2)
                    )
    # ===================================================

    # 处理分析信号
    def handleAnalyzeSignal(self, flag):
        print('handleAnalyzeSignal', flag)
        if flag == 2:
            self.analyze_action.setChecked(True)
            self.mainWidget.hideGraphicsViewAnalyze(False)
            flag = 1

        elif flag == 1:
            self.analyze_action.setChecked(True)
            self.mainWidget.hideGraphicsViewAnalyze(False)

            if self.mainWidget.hasAnalyzer() == False:
                # 创建 ananlyzer，并在创建完成 handleAnanlyzerCreateInfoSignal 中初始化第一帧
                self.mainWidget.createAnalyzer()
        else:
            self.analyze_action.setChecked(False)
            self.mainWidget.hideGraphicsViewAnalyze(True)
            
        self.analyzeChecked = flag

        # 提示分析是否开启
        if self.mainWidget.hasAnalyzer():
            if self.analyzeChecked == 0:
                self.changeStatusBarInfo('analyze disabled.')
                self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, self.mainWidget.total_frames)
                self.infoDockWidget.setTab2Info(None)

                # 不可重新标注跟踪框
                self.modify_box_action.setDisabled(True)
                self.modify_first_box_action.setDisabled(True)
            else:
                self.changeStatusBarInfo('analyze enabled.')

                if self.mainWidget.current_frame >= self.mainWidget.analyzer.analyzed_frame:
                    self.setMainWidgetFrame(self.mainWidget.analyzer.analyzed_frame + 1)

                self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, self.mainWidget.analyzer.analyzed_frame + 1)

                # 可重新标注跟踪框
                self.modify_box_action.setDisabled(False)
                self.modify_first_box_action.setDisabled(False)
    
            self.mainWidget.showImage(analyze=self.analyzeChecked)
        else:
            self.infoDockWidget.setTab2Info(None)

    # 初始化建立 analyzer 时的信号
    def handleAnanlyzerCreateInfoSignal(self, flag, info):
        print('handleAnanlyzerCreateInfoSignal flag, info:', flag, info)
        self.changeStatusBarInfo(info)

        if flag == False: # analyzer 创建完成
            # enable ...
            self.play_action.setDisabled(False)
            self.stop_action.setDisabled(False)
            self.analyze_action.setDisabled(False)
            
            # analyzer 创建完成时就有图像 初始化分析第一帧
            if self.mainWidget.hasImage():
                if self.analyze_history_action.isChecked():
                    self.mainWidget.analyzeFirstFrame(_new=False, _dir=self.save_dirname)
                else:
                    self.mainWidget.analyzeFirstFrame(
                        _detect=bool(self.toolBarFile.analyzeMethodIndex())
                    )
        else:
            # disable ...
            self.play_action.setDisabled(True)
            self.stop_action.setDisabled(True)
            self.analyze_action.setDisabled(True)
            # 不可重新标注跟踪框
            self.modify_box_action.setDisabled(True)
            self.modify_first_box_action.setDisabled(True)
            # 不可保存标注结果
            self.save_anno_action.setDisabled(True)

    def handleFirstFrameInitInfoSignal(self, flag, info):
        print('handleFirstFrameInitInfoSignal flag, info:', flag, info)
        self.changeStatusBarInfo(info)

        if flag == False: # 第一帧初始化完成
            # enable ...
            self.play_action.setDisabled(False)
            self.stop_action.setDisabled(False)
            self.analyze_action.setDisabled(False)

            # 可设置帧号
            self.statusBar().setFrameWidgetDisabled(False)
            self.prev_frame_action.setDisabled(False)
            self.next_frame_action.setDisabled(False)
            self.prev_10frame_action.setDisabled(False)
            self.next_10frame_action.setDisabled(False)

            if self.mainWidget.hasAnalyzer() == True:
                if self.mainWidget.current_frame > self.mainWidget.analyzer.analyzed_frame:
                    self.setMainWidgetFrame(self.mainWidget.analyzer.analyzed_frame + 1)

                self.mainWidget.showImage(analyze=self.analyzeChecked)

                self.statusBar().setFrameWidget(
                    self.mainWidget.current_frame + 1,
                    self.mainWidget.analyzer.analyzed_frame + 1
                )

                # 可重新标注跟踪框
                self.modify_box_action.setDisabled(False)
                self.modify_first_box_action.setDisabled(False)

                # 可保存标注结果
                self.save_anno_action.setDisabled(False)

        else:
            # disable
            self.play_action.setDisabled(True)
            self.stop_action.setDisabled(True)
            self.analyze_action.setDisabled(True)

            # 不可设置帧号
            self.statusBar().setFrameWidgetDisabled(True)
            self.prev_frame_action.setDisabled(True)
            self.next_frame_action.setDisabled(True)
            self.prev_10frame_action.setDisabled(True)
            self.next_10frame_action.setDisabled(True)

            # 不可重新标注跟踪框
            self.modify_box_action.setDisabled(True)
            self.modify_first_box_action.setDisabled(True)

            # 不可保存标注结果
            self.save_anno_action.setDisabled(True)

            self.infoDockWidget.setTab2Info(None)

    def handleAnalyzedFramesSignal(self, flag, frame_num):
        # print('handleAnalyzedFramesSignal', flag, frame_num)
        if flag == True:
            print('handleAnalyzedFramesSignal finished.')

        self.statusBar().setFrameWidget(self.mainWidget.current_frame + 1, frame_num + 1)
    
    # 修改每一帧 analyze 方法，0 ECO tracking, 1 YOLO detection
    def changeAnalyzerMethod(self, idx):
        if idx == 1:
            # 提示 cuda 不可用
            if torch.cuda.is_available() is False:
                    self.msgBox = QMessageBox()
                    self.msgBox.setWindowTitle('Message')
                    self.msgBox.setText('CUDA 不可用，分析过程会比较耗时.')
                    self.msgBox.setWindowModality(Qt.NonModal)
                    self.msgBox.setWindowIcon(QIcon(os.path.join(os.path.dirname(__file__), './images/radiology.png')))
                    self.msgBox.setIcon(QMessageBox.Information)
                    self.msgBox.setStandardButtons(QMessageBox.Ok)
                    self.msgBox.show()
    
        if self.mainWidget.hasAnalyzer() and self.mainWidget.hasImage():
            if idx == 0: # ECO tracking
                self.mainWidget.analyzeReset(_detect=False)
            elif idx == 1: # YOLO detection
                self.mainWidget.analyzeReset(_detect=True)

    # 修改标注显示
    def handleAnnotateSignal(self):
        if self.mainWidget.hasImage() and self.mainWidget.hasAnalyzer() \
            and self.analyzeChecked == True:
            self.mainWidget.showImage(True)
    
    def handleModifyBoxTriggered(self, end=False, first=False):
        if end == False:
            # 暂不可修改帧号
            self.play_action.setDisabled(True)
            self.stop_action.setDisabled(True)
            self.analyze_action.setDisabled(True)
            self.analyze_history_action.setDisabled(True)

            self.statusBar().setFrameWidgetDisabled(True)

            self.statusBar().setFrameWidgetDisabled(True)
            self.prev_frame_action.setDisabled(True)
            self.next_frame_action.setDisabled(True)
            self.prev_10frame_action.setDisabled(True)
            self.next_10frame_action.setDisabled(True)

            self.toolBarFile.setAnalyzeComboBoxDisabled(True)

            if self.mainWidget.current_frame == 0:
                first = True

            if first == False:
                self.modify_first_box_action.setDisabled(True)
            else:
                if self.mainWidget.current_frame != 0:
                    self.modify_box_action.setDisabled(True)
            self.cancel_modify_box_action.setDisabled(False)

            self.mainWidget.handleModifyBox(0, first)
        else:
            # 可修改帧号
            self.play_action.setDisabled(False)
            self.stop_action.setDisabled(False)
            self.analyze_action.setDisabled(False)
            self.analyze_history_action.setDisabled(False)

            self.statusBar().setFrameWidgetDisabled(False)

            self.statusBar().setFrameWidgetDisabled(False)
            self.prev_frame_action.setDisabled(False)
            self.next_frame_action.setDisabled(False)
            self.prev_10frame_action.setDisabled(False)
            self.next_10frame_action.setDisabled(False)

            if not self.analyze_history_action.isChecked():
                self.toolBarFile.setAnalyzeComboBoxDisabled(False)

            if first == False:
                self.modify_first_box_action.setDisabled(False)
            else:
                self.modify_box_action.setDisabled(False)

            self.cancel_modify_box_action.setDisabled(True)

    def cancelModifyBox(self):
        self.mainWidget.cancelModifyBox()
        self.cancel_modify_box_action.setDisabled(True)
    # ===================================================

    # 修改状态栏显示的信息
    def changeStatusBarInfo(self, info):
        self.statusBar().setInfoLabelText(info)

    # 设置当前帧数
    def setMainWidgetFrame(self, frame):
        self.mainWidget.setCurrentFrame(frame, analyze=self.analyzeChecked)

        if self.mainWidget.hasAnalyzer() and self.analyzeChecked \
            and self.mainWidget.analyzer.initialized:
            self.infoDockWidget.setTab2Info(
                self.mainWidget.current_frame + 1,
                self.mainWidget.analyzer.boxes[max(0, self.mainWidget.current_frame)],
                self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 1),
                self.mainWidget.analyzer.get_pix_barium(max(0, self.mainWidget.current_frame), 2)
            )
    # ===================================================
    def wheelEvent(self, event):
        if self.ctrl_pressed == True and self.mainWidget.modify_state == -1:
            if event.angleDelta().y() > 0:
                self.mainWidget.set_zoom_ratio1(True, 5)
            elif event.angleDelta().y() < 0:
                self.mainWidget.set_zoom_ratio1(True, -5)
        else:
            return super().wheelEvent(event)

    def keyReleaseEvent(self, QKeyEvent):
        if QKeyEvent.key() == Qt.Key_Control:
            self.ctrl_pressed = False
        return super().keyReleaseEvent(QKeyEvent)

    def keyPressEvent(self, QKeyEvent):
        if QKeyEvent.key() == Qt.Key_Control:
            self.ctrl_pressed = True
        return super().keyPressEvent(QKeyEvent)
    
    # ===================================================
    def show_epiglottis_box(self):
        return self.menuBar().action_epiglottis.isChecked()
    
    def show_barium(self):
        return self.menuBar().action_barium.isChecked()