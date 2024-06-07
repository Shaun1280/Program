import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class AbsoluteLayout(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('absolute layout')

        self.label1 = QLabel('welcom', self)
        self.label1.move(15, 20) # 绝对布局通过 move 控制组件位置

        self.label2 = QLabel('hello', self)
        self.label2.move(35, 40)

        self.label3 = QLabel('world', self)
        self.label3.move(55, 80)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = AbsoluteLayout()
    main.show()

    sys.exit(app.exec_())