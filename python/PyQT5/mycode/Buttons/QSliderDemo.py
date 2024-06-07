import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QSliderDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()
        
        self.label = QLabel('hello world')
        self.label.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.label)

        self.slider = QSlider(Qt.Horizontal)
        # 设置最小值
        self.slider.setMinimum(12)
        # 设置最大值
        self.slider.setMaximum(48)
        # 步长
        self.slider.setSingleStep(3)
        # 设置当前值
        self.slider.setValue(18)
        # 设置刻度位置，可度在下方
        self.slider.setTickPosition(QSlider.TicksBelow)
        # 设置刻度的间隔
        self.slider.setTickInterval(6)
        self.slider.valueChanged.connect(self.valueChange)
        layout.addWidget(self.slider)

        self.slider2 = QSlider(Qt.Vertical)
        # 设置最小值
        self.slider2.setMinimum(10)
        # 设置最大值
        self.slider2.setMaximum(60)
        # 步长
        self.slider2.setSingleStep(5)
        # 设置当前值
        self.slider2.setValue(30)
        # 设置刻度位置，可度在下方
        self.slider2.setTickPosition(QSlider.TicksLeft)
        # 设置刻度的间隔
        self.slider2.setTickInterval(2)
        self.slider2.valueChanged.connect(self.valueChange)
        layout.addWidget(self.slider2)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QComboBox Demo')

    def valueChange(self):
        print('slider value', self.sender().value())
        size = self.sender().value()
        self.label.setFont(QFont('Arial', size))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QSliderDemo()
    main.show()

    sys.exit(app.exec_())