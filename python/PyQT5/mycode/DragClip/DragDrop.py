import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
A
B.setAcceptDrops(True)

B 需要两个事件
1. dragEnterEvent (将 A 拖到 B 触发)
2. dropEvent （在 B 的区域放下 A 触发）
'''

class MyComboBox(QComboBox):
    def __init__(self):
        super().__init__()
        self.setAcceptDrops(True)
    
    def dragEnterEvent(self, e):
        print(e)
        
        if e.mimeData().hasText():
            e.accept()
        else:
            e.ignore()

    def dropEvent(self, e):
        self.addItem(e.mimeData().text())

class DragDrop(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 600)
        self.setWindowTitle('draw geometry')

        formLayout = QFormLayout()
        formLayout.addRow(QLabel('move from left to right'))

        lineEdit = QLineEdit()
        lineEdit.setDragEnabled(True)

        combo = MyComboBox()
        formLayout.addRow(lineEdit, combo)

        self.setLayout(formLayout)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = DragDrop()
    main.show()

    sys.exit(app.exec_())