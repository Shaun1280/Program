import sys

# 在单元格放置控件 setCellWidget
# 文本 setItem

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class PlaceControllCell(QWidget):
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
        textItem = QTableWidgetItem('shaun')
        tablewidget.setItem(0, 0, textItem)

        combox = QComboBox()
        combox.addItems(['male', 'female'])
        combox.setStyleSheet('QComboBox{margin:3px};')
        tablewidget.setCellWidget(0, 1, combox)
        
        modifyButton = QPushButton('modify')
        modifyButton.setDown(True)
        modifyButton.setStyleSheet('QPushButton{margin:3px};')
        tablewidget.setCellWidget(0, 2, modifyButton)


        self.setLayout(layout)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = PlaceControllCell()
    main.show()

    sys.exit(app.exec_())