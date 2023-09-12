import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from functools import partial

class PartialSlotArg(QMainWindow):
    def __init__(self):
        super().__init__()

        button1 = QPushButton('btn1')
        button2 = QPushButton('btn2')

        button1.clicked.connect(partial(self.onButtonClick, 10, 20))
        button2.clicked.connect(partial(self.onButtonClick, 100, -20))

        layout = QHBoxLayout()
        layout.addWidget(button1)
        layout.addWidget(button2)

        mainFrame = QWidget()
        mainFrame.setLayout(layout)
        self.setCentralWidget(mainFrame)

    def onButtonClick(self, m, n):
        print('m + n =', m + n)
        QMessageBox.information(self, 'result', str(m + n))


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = PartialSlotArg()
    main.show()

    sys.exit(app.exec_())