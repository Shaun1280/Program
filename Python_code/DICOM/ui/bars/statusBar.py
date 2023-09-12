from PyQt5.QtWidgets import (QHBoxLayout, QWidget, QSlider, QStatusBar, QLabel, QPushButton, QLineEdit)
from PyQt5.QtCore import Qt, pyqtSignal

class StatusBar(QStatusBar):
    current_frame_signal = pyqtSignal(int)

    def __init__(self, setting, parent=None):
        super().__init__(parent)

        self.setting = setting

        self.total_frames = 0

        self.initUI()

        self.setFixedHeight(40)

    def initUI(self):
        self.addFrameWidget()

        self.label_img_size = QLabel('480 x 480')
        self.label_img_size.setFixedWidth(110)
        self.label_img_size.setAlignment(Qt.AlignCenter)
        self.addWidget(self.label_img_size)

        self.label_info = QLabel('information')
        self.label_info.setAlignment(Qt.AlignCenter)
        self.label_info.setWordWrap(True)
        self.addWidget(self.label_info, 1)

        self.addZoomWidget()

    def addFrameWidget(self):
        self.frame = QWidget()
        self.frame.setFixedWidth(160)

        frame_layout = QHBoxLayout()
        label = QLabel('Frame: ')
        frame_layout.addWidget(label)

        self.current_frame_edit = QLineEdit('0')
        self.current_frame_edit.setFixedWidth(34)
        self.current_frame_edit.setFixedHeight(15)
        self.current_frame_edit.setAlignment(Qt.AlignRight)
        self.current_frame_edit.setContentsMargins(-2, -2, -2, -2)
        self.current_frame_edit.textEdited.connect(self.currentFrameTextEdit)
        self.current_frame_edit.returnPressed.connect(self.current_frame_edit.clearFocus)
        self.current_frame_edit.editingFinished.connect(self.currentFrameEditFinish)

        self.total_frames_label = QLabel('/  0')
        self.total_frames_label.setAlignment(Qt.AlignVCenter)
        self.total_frames_label.setContentsMargins(0, 1.5, 0, 0)

        frame_layout.addWidget(self.current_frame_edit)
        frame_layout.addWidget(self.total_frames_label)

        self.frame.setLayout(frame_layout)
        self.addWidget(self.frame)

    def addZoomWidget(self):
        self.zoom = QWidget()
        self.zoom.setFixedWidth(270)
        zoom_layout = QHBoxLayout()
        self.zoom_label = QLabel('100 %')
        zoom_layout.addWidget(self.zoom_label)

        self.button_minus = QPushButton('-')
        self.button_minus.setStyleSheet('''
            QPushButton {
                width: 20px;
                border-radius: 20px;
            }
        ''')
        self.button_minus.clicked.connect(lambda :{self.parent().mainWidget.set_zoom_ratio1(True, -10)})
        self.button_minus.setCursor(Qt.PointingHandCursor)

        self.button_plus = QPushButton('+')
        self.button_plus.setStyleSheet('''
            QPushButton {
                width: 20px;
                border-radius: 20px;
            }
        ''')
        self.button_plus.setCursor(Qt.PointingHandCursor)
        self.button_plus.clicked.connect(lambda :{self.parent().mainWidget.set_zoom_ratio1(True, 10)})
        zoom_layout.addWidget(self.button_minus)

        self.zoom_slider = QSlider(Qt.Horizontal)
        self.zoom_slider.setMinimum(10)
        self.zoom_slider.setMaximum(200)
        self.zoom_slider.setSingleStep(10)
        self.zoom_slider.setValue(100)
        self.zoom_slider.setFixedWidth(120)
        self.zoom_slider.setTickPosition(QSlider.NoTicks)
        self.zoom_slider.setStyleSheet('''
            QSlider::groove:horizontal {
                height: 4px;
            }
            QSlider::handle:horizontal {
                width: 5px;
                background: rgb(0, 160, 230);
                margin: -3px 0px -3px 0px;
                border-radius: 5px;
            }
        ''')
        self.zoom_slider.valueChanged.connect(lambda :{
            self.parent().mainWidget.set_zoom_ratio1(False, self.zoom_slider.value())
        })
        zoom_layout.addWidget(self.zoom_slider)
        zoom_layout.addWidget(self.button_plus)

        self.zoom.setLayout(zoom_layout)
        self.addWidget(self.zoom)

    def setInfoLabelText(self, info):
        self.label_info.setText(info)

    def setFrameWidget(self, frame, total_frames):
        if total_frames < 1:
            total_frames = 1
        self.current_frame_edit.setText(str(frame))
        self.total_frames_label.setText('/  {}'.format(total_frames))

        self.total_frames = total_frames

    def setFrameWidgetDisabled(self, flag=True):
        self.current_frame_edit.setDisabled(flag)

    def currentFrameTextEdit(self):
        text = self.current_frame_edit.text()

        if text == '':
            # emit 之后，重新 setText ...
            return
        elif text.isdecimal() == False:
            if self.total_frames == 0:
                self.current_frame_edit.setText('0')
            else:
                self.current_frame_edit.setText('1')
        else:
            value = int(text)
            if value <= 0:
                value = 1

            if value > self.total_frames:
                value = self.total_frames
            self.current_frame_edit.setText(str(value))

    def currentFrameEditFinish(self):
        text = self.sender().text()
        if text == '':
            self.sender().setText('1')

        self.current_frame_signal.emit(int(self.sender().text()))

    def handleZoomSignal(self, value):
        self.zoom_slider.setValue(value)
        self.zoom_label.setText('{} %'.format(value))