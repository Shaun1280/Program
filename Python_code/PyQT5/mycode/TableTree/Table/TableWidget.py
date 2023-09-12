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

        layout = QHBoxLayout()
        tablewidget = QTableWidget()
        tablewidget.setRowCount(4)
        tablewidget.setColumnCount(3)
        layout.addWidget(tablewidget)

        tablewidget.setHorizontalHeaderLabels(['name', 'age', 'country'])
        nameItem = QTableWidgetItem('shaun')
        tablewidget.setItem(0, 0, nameItem)

        ageItem = QTableWidgetItem('24')
        tablewidget.setItem(0, 1, ageItem)

        countryItem = QTableWidgetItem('chengdu')
        tablewidget.setItem(0, 2, countryItem)

        # 禁止编辑
        # tablewidget.setEditTriggers(QAbstractItemView.NoEditTriggers)

        # 整行选择 默认列
        tablewidget.setSelectionBehavior(QAbstractItemView.SelectRows)

        # 调整行列大小
        tablewidget.resizeColumnsToContents()
        tablewidget.resizeRowsToContents()

        # 取消显示 header
        tablewidget.horizontalHeader().setVisible(False)
        # tablewidget.verticalHeader().setVisible(False)

        tablewidget.setVerticalHeaderLabels(['a', 'b', '1'])

        # 取消表格线
        tablewidget.setShowGrid(False)

        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TableView()
    main.show()

    sys.exit(app.exec_())