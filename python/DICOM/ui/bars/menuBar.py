from PyQt5.QtWidgets import (QMenuBar, QAction, QApplication)
from PyQt5.QtGui import QKeySequence
from PyQt5.QtCore import Qt, pyqtSignal

import sys

class MenuBar(QMenuBar):
    annotate_signal = pyqtSignal()

    def __init__(self, setting, parent=None):
        super().__init__(parent)

        self.setting = setting
        # 获取 LastDicPath 值
        self.last_dic_path = self.setting.value('LastDicPath')

        # 如果字符串为空，将路径索引到根目录
        if self.last_dic_path is None:
            self.last_dic_path = '/' # 根盘符

        self.initUI()

    def initUI(self):
        # 一级菜单 1
        file = self.addMenu('文件')

        file.addAction(self.parent().open_action)
        file.addAction(self.parent().open_analyze_action)
        file.addAction(self.parent().analyze_action)
        file.addAction(self.parent().analyze_history_action)
        # file.addAction(self.parent().analyze_setting_action)

        file.addSeparator()

        file.addAction(self.parent().export_action)

        file.addSeparator()

        action_quit = QAction('退出', self)
        action_quit.setShortcut('Ctrl+Q')
        action_quit.triggered.connect(self.handleQuit)
        file.addAction(action_quit)

        # 一级菜单 2
        view = self.addMenu('显示')

        # 二级菜单 2-1
        cine = view.addMenu('放映')

        cine.addAction(self.parent().play_action)
        cine.addAction(self.parent().stop_action)
        # cine.addAction(self.parent().cine_setting_action)

        # 二级菜单 2-2
        browse_image = view.addMenu('浏览图像')

        browse_image.addAction(self.parent().prev_frame_action)
        browse_image.addAction(self.parent().next_frame_action)
        browse_image.addAction(self.parent().prev_10frame_action)
        browse_image.addAction(self.parent().next_10frame_action)

        view.addSeparator()

        # 二级菜单 2-3
        zoom = view.addMenu('缩放')

        action_11resolution = QAction('1:1 显示', self)
        action_11resolution.setShortcut('Ctrl+1')
        action_11resolution.triggered.connect(lambda :{self.parent().mainWidget.set_zoom_ratio2(False)})
        zoom.addAction(action_11resolution)

        action_fit_to_screen = QAction('适合屏幕', self)
        action_fit_to_screen.setShortcut('Shift+1')
        action_fit_to_screen.triggered.connect(lambda :{self.parent().mainWidget.set_zoom_ratio2(True)})
        zoom.addAction(action_fit_to_screen)

        action_zoom_in = QAction('放大', self)
        action_zoom_in.setShortcut(QKeySequence(Qt.CTRL + Qt.Key_Plus))
        action_zoom_in.triggered.connect(lambda :{self.parent().mainWidget.set_zoom_ratio1(True, 10)})
        zoom.addAction(action_zoom_in)

        action_zoom_out = QAction('缩小', self)
        action_zoom_out.setShortcut('Ctrl+-')
        action_zoom_out.triggered.connect(lambda :{self.parent().mainWidget.set_zoom_ratio1(True, -10)})
        zoom.addAction(action_zoom_out)

        view.addSeparator()

        self.action_file_tool_bar = QAction('工具栏-文件', self)
        self.action_file_tool_bar.setCheckable(True)
        self.action_file_tool_bar.setChecked(True)
        self.action_file_tool_bar.triggered.connect(lambda: {
            self.parent().toolBarFile.setHidden(not self.action_file_tool_bar.isChecked())
        })
        view.addAction(self.action_file_tool_bar)

        self.action_anno_tool_bar = QAction('工具栏-标注', self)
        self.action_anno_tool_bar.setCheckable(True)
        self.action_anno_tool_bar.setChecked(True)
        self.action_anno_tool_bar.triggered.connect(lambda: {
            self.parent().toolBarAnno.setHidden(not self.action_anno_tool_bar.isChecked())
        })
        view.addAction(self.action_anno_tool_bar)

        self.action_view_tool_bar = QAction('工具栏-显示', self)
        self.action_view_tool_bar.setCheckable(True)
        self.action_view_tool_bar.setChecked(True)
        self.action_view_tool_bar.triggered.connect(lambda: {
            self.parent().toolBarPlay.setHidden(not self.action_view_tool_bar.isChecked())
        })
        view.addAction(self.action_view_tool_bar)

        action_status_bar = QAction('状态栏', self)
        action_status_bar.setCheckable(True)
        action_status_bar.setChecked(True)
        action_status_bar.triggered.connect(lambda: {
            self.parent().statusBar().setHidden(not action_status_bar.isChecked())
        })
        view.addAction(action_status_bar)

        view.addSeparator()

        self.action_tabs = QAction('Tabs', self)
        self.action_tabs.setCheckable(True)
        self.action_tabs.setChecked(True)
        self.action_tabs.triggered.connect(lambda: {
            self.parent().infoDockWidget.setHidden(not self.action_tabs.isChecked())
        })
        view.addAction(self.action_tabs)

        # 一级菜单 3
        annotate = self.addMenu('标注')

        self.action_epiglottis = QAction('会厌软骨跟踪框', self)
        self.action_epiglottis.setCheckable(True)
        self.action_epiglottis.setChecked(True)
        self.action_epiglottis.triggered.connect(lambda: {
            self.annotate_signal.emit()
        })
        annotate.addAction(self.action_epiglottis)

        self.action_barium = QAction('钡餐标记', self)
        self.action_barium.setCheckable(True)
        self.action_barium.setChecked(True)
        self.action_barium.triggered.connect(lambda: {
            self.annotate_signal.emit()
        })
        annotate.addAction(self.action_barium)

        annotate.addSeparator()

        # 二级菜单 3-1
        rect = annotate.addMenu('重新标注跟踪框')
        rect.addAction(self.parent().modify_box_action)
        rect.addAction(self.parent().modify_first_box_action)
        rect.addAction(self.parent().cancel_modify_box_action)

        annotate.addAction(self.parent().save_anno_action)

    def handleQuit(self):
        # app = QApplication.instance()
        # app.quit()

        sys.exit()
