from PyQt5.QtWidgets import (QToolBar, QSlider, QLabel, QLineEdit, QComboBox)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont

class ToolBarFile(QToolBar):
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
        self.setWindowTitle('工具栏-文件')

        self.layout().setSpacing(5)

        self.addAction(self.parent().open_action)
        self.addAction(self.parent().open_analyze_action)
        
        # 分析模式
        analyze_action = self.parent().analyze_action
        self.addAction(analyze_action)

        self.addAction(self.parent().analyze_history_action)

        self.addSeparator()

        # 分析设置选项 comboBox
        self.add_ananlyze_comboBox_widget()
        
        self.addSeparator()

        # 导出图像
        self.addAction(self.parent().export_action)

        # 仅显示图标
        self.setToolButtonStyle(Qt.ToolButtonIconOnly)

    def process(self, a):
        print(self.sender().text())

    def add_ananlyze_comboBox_widget(self):
        label_combo = QLabel('会厌软骨检测: ')
        label_combo.setFont(QFont('宋体', 10))
        self.addWidget(label_combo)

        self.analyze_comboBox = QComboBox()
        self.analyze_comboBox.setStyleSheet('''
            QComboBox {
                border: none;
                width: 120px;
                height: 20px;
                background: rgb(250, 250, 250);
            }
            QComboBox::down-arrow {
                border: 0px;
                image: url(./ui/images/down-chevron);
            }
        ''')
        # height:30px;width:20px;
        self.analyze_comboBox.addItems(['ECO tracking', 'YOLO detection'])
        self.analyze_comboBox.currentIndexChanged.connect(self.analyze_comboBox_selectionChange)
        self.addWidget(self.analyze_comboBox)

    def setAnalyzeComboBoxDisabled(self, flag):
        self.analyze_comboBox.setDisabled(flag)

    def analyze_comboBox_selectionChange(self, idx):
        text = self.analyze_comboBox.itemText(idx)
        print(idx, text)
        self.parent().changeAnalyzerMethod(idx)

    def analyzeMethodIndex(self):
        return self.analyze_comboBox.currentIndex()


class ToolBarPlay(QToolBar):
    def __init__(self, setting, parent=None):
        super().__init__(parent)

        self.setting = setting

        self.initUI()

    def initUI(self):
        self.setWindowTitle('工具栏-显示')
        
        self.layout().setSpacing(5)

        self.addAction(self.parent().play_action)
        self.addAction(self.parent().stop_action)

        self.addSeparator()

        # 前进后退
        self.addAction(self.parent().prev_10frame_action)
        self.addAction(self.parent().prev_frame_action)
        self.addAction(self.parent().next_frame_action)
        self.addAction(self.parent().next_10frame_action)

        self.addSeparator()

        # fps settings
        self.addFpsWidget()

        self.addSeparator()

        # self.addAction(self.parent().cine_setting_action)

        # 仅显示图标
        self.setToolButtonStyle(Qt.ToolButtonIconOnly)

    def addFpsWidget(self):
        self.addWidget(QLabel('FPS:'))
        self.fps_slider = QSlider(Qt.Horizontal)
        self.fps_slider.setMinimum(1)
        self.fps_slider.setMaximum(120)
        self.fps_slider.setSingleStep(5)
        self.fps_slider.setValue(15)
        self.fps_slider.setTickInterval(60)
        self.fps_slider.setFixedWidth(200)
        self.fps_slider.setTickPosition(QSlider.TicksBelow)
        self.addWidget(self.fps_slider)

        self.fps_text = QLineEdit('15')
        self.fps_text.setFixedHeight(20)
        self.fps_text.setFixedWidth(30)
        self.addWidget(self.fps_text)

        self.fps_slider.valueChanged.connect(self.fpsSliderValueChange)
        self.fps_text.textEdited.connect(self.fpsTextEdit)
        self.fps_text.returnPressed.connect(self.fps_text.clearFocus)
        self.fps_text.editingFinished.connect(self.fpsTextEditFinish)
    
    def fpsSliderValueChange(self):
        value = self.sender().value()
        if self.fps_text.text() == '' and value == 1:
            return
        self.fps_text.setText(str(value))

    def fpsTextEdit(self):
        text = self.sender().text()

        if text == '':
            self.fps_slider.setValue(1)
        elif text.isdecimal() == False:
            self.fps_slider.setValue(1)
            self.fps_text.setText('1')
        else:
            value = int(text)
            if value <= 0:
                value = 1
            elif value > 120:
                value = 120
            self.fps_slider.setValue(value)
            self.fps_text.setText(str(value))

    def fpsTextEditFinish(self):
        text = self.sender().text()
        if text == '':
            self.fps_text.setText('1')

    def process(self, a):
        print(self.sender().text())

class ToolBarAnno(QToolBar):
    def __init__(self, setting, parent=None):
        super().__init__(parent)

        self.setting = setting

        self.initUI()

    def initUI(self):
        self.setWindowTitle('工具栏-标注')
        
        self.layout().setSpacing(5)

        self.addAction(self.parent().modify_box_action)
        self.addAction(self.parent().modify_first_box_action)
        self.addAction(self.parent().cancel_modify_box_action)

        self.addSeparator()

        self.addAction(self.parent().save_anno_action)

        self.addSeparator()

        # 仅显示图标
        self.setToolButtonStyle(Qt.ToolButtonIconOnly)
