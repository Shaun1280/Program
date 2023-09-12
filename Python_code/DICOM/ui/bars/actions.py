from PyQt5.QtWidgets import (QAction, QFileDialog, QMessageBox)
from PyQt5.QtCore import pyqtSignal, Qt
from PyQt5.QtGui import QKeySequence
import os

class OpenAndAnalyzeAction(QAction):
    open_signal = pyqtSignal(str)
    analyze_signal = pyqtSignal(int)

    def __init__(self, setting, icon, text='打开', parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        if text == '打开' or text == '打开并分析':
            # 获取 setting 中的 LastDicPath 值
            self.last_dic_path = self.setting.value('LastDicPath')

            # 如果字符串为空，将路径索引到根目录
            if self.last_dic_path is None:
                self.last_dic_path = '/' # 根盘符

            if text == '打开':
                self.setShortcut('Ctrl+O')
            else:
                self.setShortcut('Ctrl+Shift+O')

            self.triggered.connect(lambda :self.openDicom(text))
        elif text == '分析':
            self.setShortcut('Ctrl+A')
            self.setCheckable(True)
            self.setChecked(False)
            self.triggered.connect(lambda :self.emitAnalyzeSignal())

    def openDicom(self, text):
        fname, _ = QFileDialog.getOpenFileName(self.parent(), 'open file', self.last_dic_path, '*.dic')

        # 如果文件为空，取消后续指令
        if fname is None or len(fname) <= 0:
            return

        try:
            # 保存当前目录的路径到配置文件中
            self.parent().setting.setValue(
                'LastDicPath',
                os.path.dirname(fname)
            )
            
            # 将路径设为''程序会使用上一次的路径
            self.last_dic_path = ''

            self.open_signal.emit(fname)

            if text == '打开并分析':
                self.emitAnalyzeSignal(2)
            elif text == '打开':
                self.emitAnalyzeSignal(0) # 只打开文件，不进行分析

        except Exception as e:
            # 发生异常，弹窗警告
            QMessageBox.warning(
                self.parent(), 
                'Warning',
                '.dic文件打开失败{}'.format(e),
                buttons=QMessageBox.Ok,
                defaultButton=QMessageBox.Ok
            )

    def emitAnalyzeSignal(self, flag=-1):
        # emit analyze signal
        if flag == -1:
            flag = int(self.isChecked())
        self.analyze_signal.emit(flag)

class AnalyzeHistoryAction(QAction):
    use_history_signal = pyqtSignal(bool)
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.triggered.connect(self.useHistory)

        self.setDisabled(True)

        self.setCheckable(True)

    def useHistory(self):
        self.use_history_signal.emit(self.isChecked())

class ExportImageAction(QAction):
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        # self.currentFrame
        self.setShortcut('Ctrl+E')
        self.setDisabled(True)

class PlayAction(QAction):
    play_status_signal = pyqtSignal(int)

    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.play_status = 0 # 0 stop 1 play

        self.setShortcut(Qt.Key_Space)
        self.triggered.connect(self.changeStatus)

    def changeStatus(self):
        self.play_status = self.play_status ^ 1
        self.play_status_signal.emit(self.play_status)

class StopAction(QAction):
    play_status_signal = pyqtSignal(int)
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.setShortcut(QKeySequence(Qt.CTRL + Qt.SHIFT + Qt.Key_Space))
        self.triggered.connect(self.stop)

    def stop(self):
        self.play_status_signal.emit(0)

class FrameAction(QAction):
    frame_step_signal = pyqtSignal(int)
    def __init__(self, setting, icon, text, shortCut, step=1, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.step = step

        self.setShortcut(shortCut)
        self.triggered.connect(self.changeFrame)

    def changeFrame(self):
        self.frame_step_signal.emit(self.step)

class ModifyBoxAction(QAction):
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.setDisabled(True)

class ModifyFirstBoxAction(QAction):
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.setDisabled(True)

class CancelModifyBoxAction(QAction):
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.setDisabled(True)

class SaveAnnoAction(QAction):
    save_signal = pyqtSignal()
    def __init__(self, setting, icon, text, parent=None):
        super().__init__(icon, text, parent)

        self.setting = setting

        self.setDisabled(True)

        self.triggered.connect(self.saveAnno)

    def saveAnno(self):
        self.save_signal.emit()