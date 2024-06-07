import sys
import math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class FillRect(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 600)
        self.setWindowTitle('用画刷填充区域')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        brush = QBrush(Qt.SolidPattern)
        painter.setBrush(brush)
        painter.drawRect(10, 15, 90, 60 )

        brush = QBrush(Qt.Dense1Pattern) # Dense1 2 3 4 5 6 7
        painter.setBrush(brush)
        painter.drawRect(130, 15, 90, 60)

        brush = QBrush(Qt.HorPattern) # horizontal
        painter.setBrush(brush)
        painter.drawRect(10, 105, 90, 60)

        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = FillRect()
    main.show()

    sys.exit(app.exec_())