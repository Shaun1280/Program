import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
通过 mask 实现异性窗口

需要一张透明的 PNG 图，透明部分被扣除，形成一个非矩形的区域
'''

class AbnormityWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('abnormity window')
        
        self.pix = QBitmap('../../image/icon.icon')

        self.resize(self.pix.size())
        self.setMask(self.pix)

        self.setWindowFlags(Qt.WindowMaximizeButtonHint
                            | Qt.WindowStaysOnTopHint
                            | Qt.FramelessWindowHint)

        self.m_drag = False

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.drawPixmap(0, 0, 
            self.pix.width(),
            self.pix.height(),
            QPixmap('../../image/icon.icon')
        )

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.m_drag = True
            '''
            event.globalPos: 相对于屏幕位置
            event.pos: 相对窗口(不包括边框和标签栏)
            self.pos: 左上角相对屏幕
            m_dragPosition: 相对于窗口的位置（包括边框和标签栏)
            '''
            self.m_dragPosition = event.globalPos() - self.pos()
            self.setCursor(QCursor(Qt.OpenHandCursor))
        elif event.button() == Qt.RightButton:
            self.close()

    def mouseMoveEvent(self, QMouseEvent):
        if Qt.LeftButton and self.m_drag:
            # 计算窗口左上角坐标并且移动
            self.move(QMouseEvent.globalPos() - self.m_dragPosition)
    
    def mouseReleaseEvent(self, event):
        self.m_drag = False
        self.setCursor(QCursor(Qt.ArrowCursor))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = AbnormityWindow()
    main.show()

    sys.exit(app.exec_())