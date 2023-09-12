import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DrawingApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('drawing app')
        self.pix = QPixmap()
        self.lastPoint = QPoint()
        self.endPoint = QPoint()

        self.initUI()

    def initUI(self):
        self.resize(600, 600)

        self.pix = QPixmap(600, 600)
        # 设置 pixmap 背景色
        self.pix.fill(Qt.white)

    # 调用 update 方法触发 paintEvent
    def paintEvent(self, event):
        pp = QPainter(self.pix)
        # 根据鼠标前后两个位置绘制直线
        pp.drawLine(self.lastPoint, self.endPoint)
        # 绘制完成后修改 lastPoint
        self.lastPoint = self.endPoint
        painter = QPainter(self)
        painter.drawPixmap(0, 0, self.pix)

    # 鼠标按下 设置 last point
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.lastPoint = event.pos()
    
    def mouseMoveEvent(self, event):
        if event.buttons() & Qt.LeftButton:
            self.endPoint = event.pos()
            self.update()
    
    def mouseReleaseEvent(self, event):
        # 鼠标左键释放
        if event.button() == Qt.LeftButton:
            self.endPoint = event.pos()
            self.update()


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DrawingApp()
    main.show()

    sys.exit(app.exec_())