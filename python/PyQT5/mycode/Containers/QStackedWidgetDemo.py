import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QStackedWidgetDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 200)
        self.setWindowTitle('QStackedWidgetDemo')

        self.list = QListWidget()
        self.list.insertItem(0, '联系方式')
        self.list.insertItem(1, '个人信息')
        self.list.insertItem(2, '教育背景')

        self.stack1 = QWidget()
        self.stack2 = QWidget()
        self.stack3 = QWidget()

        self.stack1UI()
        self.stack2UI()
        self.stack3UI()

        self.stack = QStackedWidget()
        self.stack.addWidget(self.stack1)
        self.stack.addWidget(self.stack2)
        self.stack.addWidget(self.stack3)

        hbox = QHBoxLayout() # 左侧显示选项 右侧显示界面
        hbox.addWidget(self.list)
        hbox.addWidget(self.stack)
        self.setLayout(hbox)

        self.list.currentRowChanged.connect(self.display)

    def stack1UI(self):
        layout = QFormLayout()
        layout.addRow('name', QLineEdit())
        layout.addRow('address', QLineEdit())
        self.stack1.setLayout(layout)

    def stack2UI(self):
        layout = QFormLayout()
        gender = QHBoxLayout()
        gender.addWidget(QRadioButton('male'))
        gender.addWidget(QRadioButton('female'))
        layout.addRow(QLabel('gender'), gender)
        layout.addRow('Birthday', QLineEdit())
        self.stack2.setLayout(layout)

    def stack3UI(self):
        layout = QHBoxLayout()
        layout.addWidget(QLabel('subject'))
        layout.addWidget(QCheckBox('physics'))
        layout.addWidget(QCheckBox('math'))
        self.stack3.setLayout(layout)

    def display(self, index):
        self.stack.setCurrentIndex(index)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QStackedWidgetDemo()
    main.show()

    sys.exit(app.exec_())