import sys
import math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DrawGeometry(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 600)
        self.setWindowTitle('draw geometry')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        painter.setPen(Qt.blue)
        # draw arc
        rect = QRect(0, 10, 100, 100)
        # alen: 1 alen= 1 / 16 degrees 
        painter.drawArc(rect, 0, 50 * 16) # 逆时针

        # 通过弧绘制圆
        painter.setPen(Qt.red)
        painter.drawArc(QRect(120, 10, 100, 100), 0, 360 * 16)

        # 绘制带弦的弧
        painter.drawChord(QRect(10, 120, 100, 100), 12, 130 * 16)

        # 绘制扇形
        painter.drawPie(QRect(10, 240, 100, 100), 12, 130 * 16)

        # 椭圆
        painter.drawEllipse(QRect(120, 120, 150, 100))

        # 绘制五边形
        point1 = QPoint(140, 380)
        point2 = QPoint(270, 420)
        point3 = QPoint(290, 512)
        point4 = QPoint(290, 512)
        point5 = QPoint(290, 588)
        polygon = QPolygon([point1, point2, point3, point4, point5])
        painter.drawPolygon(polygon)
        
        # 绘制图像
        image = QImage('../../image/icon.icon')
        rect = QRect(10, 400, image.width() / 3, image.height() / 3)
        painter.drawImage(rect, image)

        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DrawGeometry()
    main.show()

    sys.exit(app.exec_())