import sys
import math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DrawPoints(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        #layout = QVBoxLayout()

        self.text = 'hello world'
        #layout.addWidget(self.contents)

        # self.setLayout(layout)
        self.resize(300, 200)
        self.setWindowTitle('Draw 2T sinx')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        painter.setPen(Qt.blue)
        size = self.size()

        for i in range(1000):
            # x belong to 100 * [-1, 1] step = 0.001
            # T = 2
            x = 100 * (-1 + 2.0 * i / 1000) + size.width() / 2.0
            y = -50 * math.sin((x - size.width() / 2.0) * 2 * math.pi / 100) + size.height() / 2.0 
            painter.drawPoint(x, y)

        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DrawPoints()
    main.show()

    sys.exit(app.exec_())