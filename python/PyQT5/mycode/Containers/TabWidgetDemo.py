import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class TabWidgetDemo(QTabWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 200)
        self.setWindowTitle('tab widget')

        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()

        self.addTab(self.tab1, 'tab1')
        self.addTab(self.tab2, 'tab2')
        self.addTab(self.tab3, 'tab3')

        self.tab1UI()
        self.tab2UI()
        self.tab3UI()

    def tab1UI(self):
        layout = QFormLayout()
        layout.addRow('name', QLineEdit())
        layout.addRow('address', QLineEdit())
        self.setTabText(0, '联系方式')
        self.tab1.setLayout(layout)

    def tab2UI(self):
        layout = QFormLayout()
        gender = QHBoxLayout()
        gender.addWidget(QRadioButton('male'))
        gender.addWidget(QRadioButton('female'))
        layout.addRow(QLabel('gender'), gender)
        layout.addRow('Birthday', QLineEdit())
        self.setTabText(1, '个人信息')
        self.tab2.setLayout(layout)

    def tab3UI(self):
        layout = QHBoxLayout()
        layout.addWidget(QLabel('subject'))
        layout.addWidget(QCheckBox('physics'))
        layout.addWidget(QCheckBox('math'))
        self.setTabText(2, '教育背景')
        self.tab3.setLayout(layout)



if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TabWidgetDemo()
    main.show()

    sys.exit(app.exec_())