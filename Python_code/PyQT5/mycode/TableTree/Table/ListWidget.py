import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class TableView(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('table view')

        self.listwidget = QListWidget()
        self.listwidget.resize(300, 120)
        self.listwidget.addItem('item1')
        self.listwidget.addItem('item2')
        self.listwidget.addItem('item3')
        self.listwidget.itemClicked.connect(self.clicked)

        self.listwidget.setWindowTitle('demo')
        self.setCentralWidget(self.listwidget)

    def clicked(self, item):
        print(item, self.listwidget.row(item))
        QMessageBox.information(self, 'QListWidget', self.listwidget.item(self.listwidget.row(item)).text())

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TableView()
    main.show()

    sys.exit(app.exec_())