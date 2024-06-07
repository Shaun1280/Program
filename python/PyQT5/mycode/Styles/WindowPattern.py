import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class WindowPattern(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('set win pattern')

        self.setWindowFlags(Qt.WindowMaximizeButtonHint
                            | Qt.WindowStaysOnTopHint
                            | Qt.FramelessWindowHint)

        self.setObjectName('MainWindow')
        self.setStyleSheet('#MainWindow{\
            border-image:url(../../image/icon.icon)\
        }')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = WindowPattern()
    main.show()

    sys.exit(app.exec_())