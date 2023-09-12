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

        hlayout = QHBoxLayout()
        hlayout.addWidget(QPushButton('btn1'),
                          2, # 所占比例
                          Qt.AlignLeft | Qt.AlignTop)
        hlayout.addWidget(QPushButton('btn2'), 4, Qt.AlignLeft | Qt.AlignTop)
        hlayout.addWidget(QPushButton('btn3'), 1, Qt.AlignLeft | Qt.AlignTop)
        hlayout.addWidget(QPushButton('btn4'), 1, Qt.AlignLeft | Qt.AlignBottom)
        hlayout.addWidget(QPushButton('btn5'), 1, Qt.AlignLeft | Qt.AlignBottom)

        hlayout.setSpacing(40)
        self.setLayout(hlayout)


        
if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = AbsoluteLayout()
    main.show()

    sys.exit(app.exec_())