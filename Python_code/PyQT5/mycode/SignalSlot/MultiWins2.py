import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from NewDateDialog import NewDateDialog

class MultiWins2(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(400, 90)
        
        self.open_btn = QPushButton('获取时间')
        self.lineEdit_inner = QLineEdit(self)
        self.lineEdit_emit = QLineEdit(self)
        self.open_btn.clicked.connect(self.openDialog)

        self.lineEdit_inner.setText('接收子窗口内置信号的时间')
        self.lineEdit_emit.setText('接收子窗口自定义信号的时间')

        grid = QGridLayout()
        grid.addWidget(self.lineEdit_inner)
        grid.addWidget(self.lineEdit_emit)

        grid.addWidget(self.open_btn)
        self.setLayout(grid)

    def openDialog(self):
        dialog = NewDateDialog(self)

        # 连接 dialog 组件 datetime_inner 的内置信号与本窗口槽函数
        dialog.datetime_inner.dateTimeChanged.connect(self.deal_inner_slot)
        # 连接 dialog 自定义信号与本窗口槽函数 仅访问信号而不是控件
        dialog.signal_with_one_arg.connect(self.deal_emit_slot)
        dialog.show()

    def deal_inner_slot(self, date):
        self.lineEdit_inner.setText(date.toString())

    def deal_emit_slot(self, dateStr):
        self.lineEdit_emit.setText(dateStr)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = MultiWins2()
    main.show()

    sys.exit(app.exec_())