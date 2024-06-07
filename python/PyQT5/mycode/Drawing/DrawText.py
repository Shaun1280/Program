import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
1. 文本
2. 图形（直线、点、椭圆、弧、多边形）
3. 图像

painter = QPainter()
painter.begin()
painter.drawText(...)
painter.end()

在 paintEvent 事件方法中绘制各种元素
'''

class DrawText(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        #layout = QVBoxLayout()

        self.text = 'hello world'
        #layout.addWidget(self.contents)

        # self.setLayout(layout)
        self.resize(300, 200)
        self.setWindowTitle('Draw Text Demo')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)

        painter.setPen(QColor(150, 43, 5))
        painter.setFont(QFont('SimSun', 25))
        painter.drawText(event.rect(), Qt.AlignCenter, self.text)

        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DrawText()
    main.show()

    sys.exit(app.exec_())