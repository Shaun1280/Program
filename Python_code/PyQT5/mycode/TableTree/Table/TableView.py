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

        self.model = QStandardItemModel(4, 3)
        self.model.setHorizontalHeaderLabels(['id', '姓名', '年龄'])

        self.tableview = QTableView()
        self.tableview.setModel(self.model)

        # 添加数据
        item11 = QStandardItem('10')
        item12 = QStandardItem('shaun')
        item13 = QStandardItem('10')
        self.model.setItem(0, 0, item11)
        self.model.setItem(0, 1, item12)
        self.model.setItem(0, 2, item13)




        layout = QVBoxLayout()
        layout.addWidget(self.tableview)
        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TableView()
    main.show()

    sys.exit(app.exec_())