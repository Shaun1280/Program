import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Stretch(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)

        btn1 = QPushButton(self)
        btn2 = QPushButton(self)
        btn3 = QPushButton(self)
        btn4 = QPushButton(self)
        btn5 = QPushButton(self)
        btn1.setText('btn1')
        btn2.setText('btn2')
        btn3.setText('btn3')
        btn4.setText('btn4')
        btn5.setText('btn5')

        layout = QHBoxLayout()

        layout.addStretch(0)
        layout.addWidget(btn1)
        layout.addWidget(btn2)
        layout.addWidget(btn3)
        layout.addWidget(btn4)
        layout.addWidget(btn5)

        btnOK = QPushButton(self)
        btnOK.setText('ok')
        btnCancel = QPushButton(self)
        btnCancel.setText('cancel')

        layout.addStretch(1)
        layout.addWidget(btnOK)
        layout.addWidget(btnCancel)


        self.setLayout(layout)



        
if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = Stretch()
    main.show()

    sys.exit(app.exec_())