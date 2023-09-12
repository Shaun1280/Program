import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QssSelector(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('basic qss')
        
        btn1 = QPushButton()
        btn1.setText('btn1')

        btn2 = QPushButton()
        btn2.setProperty('name', 'btn2')
        btn2.setText('btn2')

        vbox = QVBoxLayout()
        vbox.addWidget(btn1)
        vbox.addWidget(btn2)

        self.setLayout(vbox)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QssSelector()

    qssStyle = '''
        QPushButton[name="btn2"] {
            background-color:red;
            color:yellow;
            height:120;
            font-size:60px;
        }
    '''

    main.setStyleSheet(qssStyle)
    main.show()

    sys.exit(app.exec_())