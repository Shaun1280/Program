import sys
import math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DrawLines(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('Set Pen Style')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        pen = QPen(Qt.red, 3, Qt.SolidLine)
        painter.setPen(pen)
        painter.drawLine(20, 40, 250, 40) # x1 y1, x2 y2

        pen.setStyle(Qt.DashLine) # 虚线
        painter.setPen(pen)
        painter.drawLine(20, 80, 250, 80)

        pen.setStyle(Qt.DashDotDotLine)
        painter.setPen(pen)
        painter.drawLine(20, 120, 250, 120)

        pen.setStyle(Qt.CustomDashLine)
        pen.setDashPattern([1, 10, 5, 8])
        painter.setPen(pen)
        painter.drawLine(20, 160, 250, 160)

        size = self.size()
        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DrawLines()
    main.show()

    sys.exit(app.exec_())