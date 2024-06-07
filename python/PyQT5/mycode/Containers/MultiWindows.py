import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
QMdiArea

QMdiSubWindow
'''

class MultiWindows(QMainWindow):
    count = 0

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 200)
        self.setWindowTitle('容纳多文档的窗口')

        self.mdi = QMdiArea()

        bar = self.menuBar()
        file = bar.addMenu('File')
        file.addAction('New')
        file.addAction('Cascade')
        file.addAction('Tiled')
        file.triggered.connect(self.windowaction)

        self.setCentralWidget(self.mdi)
    
    def windowaction(self, q):
        if q.text() == 'New':
            MultiWindows.count = MultiWindows.count + 1
            sub = QMdiSubWindow()
            sub.setWidget(QTextEdit())
            sub.setWindowTitle('sub' + str(MultiWindows.count))
            self.mdi.addSubWindow(sub)
            sub.show() # 显示子窗口
        elif q.text() == 'Cascade':
            self.mdi.cascadeSubWindows()
        elif q.text() == 'Tiled':
            self.mdi.tileSubWindows()


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = MultiWindows()
    main.show()

    sys.exit(app.exec_())