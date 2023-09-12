import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class WinSignal(QWidget):
    button_click_signal = pyqtSignal()

    def __init__(self):
        super().__init__()
        self.resize(300, 100)

        btn = QPushButton('close window', self)

        btn.clicked.connect(self.btn_clicked)

        self.button_click_signal.connect(self.btn_close)

    def btn_clicked(self):
        self.button_click_signal.emit()

    def btn_close(self):
        self.close()



if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = WinSignal()
    main.show()

    sys.exit(app.exec_())