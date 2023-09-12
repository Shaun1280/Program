import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class BackendThread(QThread):
    update_date = pyqtSignal(str)

    def run(self):
        while True:
            self.sleep(1)
            data = QDateTime.currentDateTime()
            current = data.toString('yyyy-MM-dd hh:mm:ss')
            self.update_date.emit(current)

class ThreadUpdateUI(QDialog):
    def __init__(self):
        super().__init__()
        self.resize(400, 100)

        self.input = QLineEdit(self)
        self.input.resize(400, 100)

        self.initUI()

    def initUI(self):
        self.backend = BackendThread()
        self.backend.update_date.connect(self.handleDisplay)

        self.backend.start()

    def handleDisplay(self, date):
        self.input.setText(date)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = ThreadUpdateUI()
    main.show()

    sys.exit(app.exec_())