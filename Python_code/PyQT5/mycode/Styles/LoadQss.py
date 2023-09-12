import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class CommonHelper:
    @staticmethod
    def readQSS(style):
        with open(style, 'r') as f:
            return f.read()
        
class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.resize(477, 258)

        btn = QPushButton()
        btn.setText('load qss')
        btn.setToolTip('hint txt')

        vbox = QVBoxLayout()
        vbox.addWidget(btn)
        btn.clicked.connect(self.onClick)
        
        widget = QWidget(self)
        widget.setLayout(vbox)
        self.setCentralWidget(widget)

    def onClick(self):
        styleFile = './style.qss'
        qssStyle = CommonHelper.readQSS(styleFile)
        self.setStyleSheet(qssStyle)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = MainWindow()
    main.show()

    sys.exit(app.exec_())