import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
默认左对齐
setTextAlignment
'''

class CellFontAndColor(QWidget):
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
        
        tablewidget.setHorizontalHeaderLabels(['name', 'gender', 'weight'])

        newItem = QTableWidgetItem('shaun')
        newItem.setTextAlignment(Qt.AlignRight | Qt.AlignBottom)
        tablewidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem('male')
        # 居中优先，后面的 bottom 不生效
        newItem.setTextAlignment(Qt.AlignCenter | Qt.AlignBottom)
        tablewidget.setItem(0, 1, newItem)

        newItem = QTableWidgetItem('male')
        newItem.setTextAlignment(Qt.AlignRight)
        tablewidget.setItem(0, 2, newItem)


        self.setLayout(layout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = CellFontAndColor()
    main.show()

    sys.exit(app.exec_())