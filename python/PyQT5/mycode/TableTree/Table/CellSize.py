import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class CellSize(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(800, 300)
        self.setWindowTitle('table view')

        layout = QHBoxLayout()

        tablewidget = QTableWidget()
        tablewidget.setRowCount(4)
        tablewidget.setColumnCount(3)
        layout.addWidget(tablewidget)
        
        tablewidget.setHorizontalHeaderLabels(['name', 'gender', 'weight'])

        #
        tablewidget.setRowHeight(0, 80)
        tablewidget.setColumnWidth(2, 240)

        newItem = QTableWidgetItem('shaun')
        newItem.setFont(QFont('Times', 14, QFont.Black))
        newItem.setForeground(QBrush(QColor(255, 0, 0)))
        tablewidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem('male')
        newItem.setForeground(QBrush(QColor(255, 255, 0)))
        newItem.setBackground(QBrush(QColor(0, 0, 255)))
        tablewidget.setItem(0, 1, newItem)

        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = CellSize()
    main.show()

    sys.exit(app.exec_())