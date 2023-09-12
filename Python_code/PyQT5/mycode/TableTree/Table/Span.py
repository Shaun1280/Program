import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Span(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('merge cells')

        layout = QHBoxLayout()

        tablewidget = QTableWidget()
        tablewidget.setRowCount(4)
        tablewidget.setColumnCount(3)
        layout.addWidget(tablewidget)
        
        tablewidget.setHorizontalHeaderLabels(['name', 'gender', 'weight'])

        newItem = QTableWidgetItem('shaun')
        tablewidget.setItem(0, 0, newItem)
        tablewidget.setSpan(0, 0, 3, 1)

        newItem = QTableWidgetItem('male')
        tablewidget.setItem(0, 1, newItem)
        tablewidget.setSpan(0, 1, 2, 1)

        newItem = QTableWidgetItem('male')
        tablewidget.setItem(0, 2, newItem)
        tablewidget.setSpan(0, 2, 4, 1)


        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = Span()
    main.show()

    sys.exit(app.exec_())