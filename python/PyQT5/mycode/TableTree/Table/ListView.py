import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class TableView(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('table view')

        layout = QVBoxLayout()

        listView = QListView()
        listModel = QStringListModel()
        self.list = ['item1', 'item2', 'item3', 'item4']
        listModel.setStringList(self.list)
        listView.setModel(listModel)
        listView.clicked.connect(self.clicked)

        layout.addWidget(listView)
        self.setLayout(layout)

    def clicked(self, item):
        QMessageBox.information(self, 'QListView', self.list[item.row()])


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TableView()
    main.show()

    sys.exit(app.exec_())