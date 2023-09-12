import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class OverrideSlot(QWidget):
    def __init__(self):
        super().__init__()

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape: # esc
            self.close()
        elif e.key() == Qt.Key_Alt:
            self.setWindowTitle('alt pressed')


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = OverrideSlot()
    main.show()

    sys.exit(app.exec_())