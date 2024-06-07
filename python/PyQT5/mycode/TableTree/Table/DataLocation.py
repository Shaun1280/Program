import sys

# 数据定位: findItems
# 如果找到，会定位到单元格所在行 setSliderPosition

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DataLocation(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('table view')

        layout = QHBoxLayout()
        tablewidget = QTableWidget()
        tablewidget.setRowCount(40)
        tablewidget.setColumnCount(30)

        layout.addWidget(tablewidget)

        for i in range(40):
            for j in range(30):
                itemContent = '({},{})'.format(i, j)
                tablewidget.setItem(i, j, QTableWidgetItem(itemContent))

        self.setLayout(layout)

        # 精确搜索
        text = '(13,1)'
        # Qt.MathStartsWith
        items = tablewidget.findItems(text, Qt.MatchExactly)
        if len(items) > 0:
            item = items[0]
            item.setBackground(QBrush(QColor(0, 255, 0)))
            item.setForeground(QBrush(QColor(255, 0, 0)))

            row = item.row()

            # 定位到指定行
            tablewidget.verticalScrollBar().setSliderPosition(row)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DataLocation()
    main.show()

    sys.exit(app.exec_())