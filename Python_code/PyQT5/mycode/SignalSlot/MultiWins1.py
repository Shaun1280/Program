import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from DateDialog import DateDialog

'''
不使用信号与槽
'''

class MultiWins1(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(300, 100)
        
        self.lineEdit = QLineEdit()
        self.button1 = QPushButton('btn1')
        self.button1.clicked.connect(self.onButton1Click)

        self.button2 = QPushButton('btn2')
        self.button2.clicked.connect(self.onButton2Click)

        gridLayout = QGridLayout()
        gridLayout.addWidget(self.lineEdit)
        gridLayout.addWidget(self.button1)
        gridLayout.addWidget(self.button2)

        self.setLayout(gridLayout)

    def onButton1Click(self):
        dialog = DateDialog(self)
        result = dialog.exec()
        date = dialog.dateTime()
        self.lineEdit.setText(date.date().toString())
        dialog.destroy()

    def onButton2Click(self):
        date, time, result = DateDialog.getDateTime()
        self.lineEdit.setText(date.toString())

        if result == QDialog.Accepted:
            print('点击确定按钮')
        else:
            print('点击取消按钮')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = MultiWins1()
    main.show()

    sys.exit(app.exec_())