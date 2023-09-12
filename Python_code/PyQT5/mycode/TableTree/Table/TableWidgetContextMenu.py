import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class TableWidgetContextMenu(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('table view')

        layout = QHBoxLayout()
        self.tablewidget = QTableWidget()
        self.tablewidget.setRowCount(4)
        self.tablewidget.setColumnCount(3)
        layout.addWidget(self.tablewidget)

        self.tablewidget.setHorizontalHeaderLabels(['name', 'age', 'country'])
        nameItem = QTableWidgetItem('shaun')
        self.tablewidget.setItem(0, 0, nameItem)

        ageItem = QTableWidgetItem('24')
        self.tablewidget.setItem(0, 1, ageItem)

        countryItem = QTableWidgetItem('chengdu')
        self.tablewidget.setItem(0, 2, countryItem)
        
        self.tablewidget.setContextMenuPolicy(Qt.CustomContextMenu)
        self.tablewidget.customContextMenuRequested.connect(self.generateMenu)

        self.setLayout(layout)

    def generateMenu(self, pos):
        print(pos)

        for i in self.tablewidget.selectionModel().selection().indexes():
            rowNum = i.row()

        if rowNum < 2:
            menu = QMenu()
            item1 = menu.addAction('option1')
            item2 = menu.addAction('option2')
            item3 = menu.addAction('option3')

            screenPos = self.tablewidget.mapToGlobal(pos)
            # 被阻塞
            action = menu.exec(screenPos)
            if action == item1:
                print('option1 selected')
            elif action == item2:
                print('option2 selected')
            elif action == item3:
                print('option3 selected')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TableWidgetContextMenu()
    main.show()

    sys.exit(app.exec_())