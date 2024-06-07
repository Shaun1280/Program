import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class BottomRightButton(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('absolute layout')

        okBtn = QPushButton('ok')
        cancelBtn = QPushButton('取消')
        
        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(okBtn)
        hbox.addWidget(cancelBtn)

        vbox = QVBoxLayout()
        btn1 = QPushButton('btn1')
        btn2 = QPushButton('btn2')
        btn3 = QPushButton('btn3')

        vbox.addStretch(0)
        vbox.addWidget(btn1)
        vbox.addWidget(btn2)
        vbox.addWidget(btn3)
        vbox.addStretch(1)

        vbox.addLayout(hbox)

        self.setLayout(vbox)

        
if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = BottomRightButton()
    main.show()

    sys.exit(app.exec_())