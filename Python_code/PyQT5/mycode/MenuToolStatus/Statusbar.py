import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Statusbar(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('tool bar')

        bar = self.menuBar()
        file= bar.addMenu('File')
        file.addAction("show")
        file.triggered.connect(self.processTrigger)

        self.setCentralWidget(QTextEdit())
        self.statusBar = QStatusBar()
        self.setStatusBar(self.statusBar)


    def processTrigger(self, q):
        if q.text() == 'show':
            self.statusBar.showMessage(q.text() + ' is clicked')


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = Statusbar()
    main.show()

    sys.exit(app.exec_())