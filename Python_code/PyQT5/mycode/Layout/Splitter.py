import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Splitter(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('form layout')

        topleft = QFrame()
        topleft.setFrameShape(QFrame.StyledPanel)
        
        bottom = QFrame()
        bottom.setFrameShape(QFrame.StyledPanel)

        splitter1 = QSplitter(Qt.Horizontal)
        textEdit = QTextEdit()
        
        splitter1.addWidget(topleft)
        splitter1.addWidget(textEdit)
        splitter1.setSizes([100, 200])

        splitter2 = QSplitter(Qt.Vertical)
        splitter2.addWidget(splitter1)
        splitter2.addWidget(bottom)

        hbox = QHBoxLayout()
        hbox.addWidget(splitter2)
        self.setLayout(hbox)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = Splitter()
    main.show()

    sys.exit(app.exec_())