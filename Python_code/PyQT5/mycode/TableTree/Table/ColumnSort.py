import sys

# 按列排序
# 升序或降序

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class ColumnSort(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('table view')

        layout = QVBoxLayout()

        self.tablewidget = QTableWidget()
        self.tablewidget.setRowCount(4)
        self.tablewidget.setColumnCount(3)
        layout.addWidget(self.tablewidget)
        
        self.tablewidget.setHorizontalHeaderLabels(['name', 'gender', 'weight'])

        newItem = QTableWidgetItem('shaun')
        self.tablewidget.setItem(0, 0, newItem)
        newItem = QTableWidgetItem('male')
        self.tablewidget.setItem(0, 1, newItem)
        newItem = QTableWidgetItem('60')
        self.tablewidget.setItem(0, 2, newItem)

        newItem = QTableWidgetItem('shaun1')
        self.tablewidget.setItem(1, 0, newItem)
        newItem = QTableWidgetItem('female')
        self.tablewidget.setItem(1, 1, newItem)
        newItem = QTableWidgetItem('80')
        self.tablewidget.setItem(1, 2, newItem)

        newItem = QTableWidgetItem('shaun2')
        self.tablewidget.setItem(2, 0, newItem)
        newItem = QTableWidgetItem('female')
        self.tablewidget.setItem(2, 1, newItem)
        newItem = QTableWidgetItem('70')
        self.tablewidget.setItem(2, 2, newItem)

        newItem = QTableWidgetItem('shaun3')
        self.tablewidget.setItem(3, 0, newItem)
        newItem = QTableWidgetItem('male')
        self.tablewidget.setItem(3, 1, newItem)
        newItem = QTableWidgetItem('77')
        self.tablewidget.setItem(3, 2, newItem)

        self.button = QPushButton('sort')
        self.orderType = Qt.DescendingOrder
        self.tablewidget.sortItems(2, self.orderType)
        self.button.clicked.connect(self.order)
        layout.addWidget(self.button)

        self.setLayout(layout)

    def order(self):
        if self.orderType == Qt.DescendingOrder:
            self.orderType = Qt.AscendingOrder
        else:
            self.orderType = Qt.DescendingOrder
        
        # 第二列
        self.tablewidget.sortItems(2, self.orderType)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = ColumnSort()
    main.show()

    sys.exit(app.exec_())