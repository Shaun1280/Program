import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class BasicQSS(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('basic qss')
        
        btn1 = QPushButton()
        btn1.setText('btn1')

        btn2 = QPushButton()
        btn2.setText('btn2')

        vbox = QVBoxLayout()
        vbox.addWidget(btn1)
        vbox.addWidget(btn2)

        self.setLayout(vbox)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = BasicQSS()

    qssStyle = '''
        QPushButton {
            background-color:red
        }
    '''

    main.setStyleSheet(qssStyle)
    main.show()

    sys.exit(app.exec_())