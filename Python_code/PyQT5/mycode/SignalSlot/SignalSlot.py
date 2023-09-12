import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class SignalSlotDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('form layout')

        self.btn = QPushButton('我都按钮', self)
        self.btn.clicked.connect(self.onClick)
    
    def onClick(self):
        self.btn.setText('got signal')
        self.btn.setStyleSheet('QPushButton{max-width:200px;min-width:200px}')


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = SignalSlotDemo()
    main.show()

    sys.exit(app.exec_())