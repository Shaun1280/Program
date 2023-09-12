import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
QDockWidget
'''

class QDockDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 200)
        self.setWindowTitle('QStackedWidgetDemo')

        layout = QHBoxLayout()
        self.items = QDockWidget('Dockalbe', self)

        self.listWidget = QListWidget()
        self.listWidget.addItem('item1')
        self.listWidget.addItem('item2')
        self.listWidget.addItem('item3')

        self.items.setWidget(self.listWidget)

        self.setCentralWidget(QLineEdit())

        self.addDockWidget(Qt.RightDockWidgetArea, self.items)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QDockDemo()
    main.show()

    sys.exit(app.exec_())