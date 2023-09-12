import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class CellImageText(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(1200, 400)
        self.setWindowTitle('table view')

        layout = QHBoxLayout()

        tablewidget = QTableWidget()
        tablewidget.setRowCount(4)
        tablewidget.setColumnCount(3)
        # 设置尺寸
        tablewidget.setIconSize(QSize(300, 200))
        for i in range(3):
            tablewidget.setColumnWidth(i, 300)
        for i in range(4):
            tablewidget.setRowHeight(i, 200)

        layout.addWidget(tablewidget)
        
        tablewidget.setHorizontalHeaderLabels(['name', 'gender', 'image'])

        newItem = QTableWidgetItem('shaun')
        newItem.setFont(QFont('Times', 14, QFont.Black))
        newItem.setForeground(QBrush(QColor(255, 0, 0)))
        tablewidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem('male')
        newItem.setForeground(QBrush(QColor(255, 255, 0)))
        newItem.setBackground(QBrush(QColor(0, 0, 255)))
        tablewidget.setItem(0, 1, newItem)

        newItem = QTableWidgetItem(QIcon('../../../image/icon.icon'), 'icon')
        tablewidget.setItem(0, 2, newItem)

        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../../image/icon.icon'))

    main = CellImageText()
    main.show()

    sys.exit(app.exec_())