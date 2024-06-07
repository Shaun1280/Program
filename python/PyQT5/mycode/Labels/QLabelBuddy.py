import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
# from PyQt5.QtCore import Qt

# mainLayout.addWidget(widget, rowIndex, columnIndex, height, width)

class QLabelBuddy(QDialog):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QLabel and Buddy')

        nameLabel = QLabel('&Name', self)
        nameLineEdit = QLineEdit(self)
        # 设置伙伴控件
        nameLabel.setBuddy(nameLineEdit)


        passwordLabel = QLabel('&Password', self)
        passwordLineEdit = QLineEdit(self)
        # 设置伙伴控件
        passwordLabel.setBuddy(passwordLineEdit)

        btnOK = QPushButton('&OK')
        btnCancel = QPushButton('&Cancel')

        mainLayout = QGridLayout(self)
        mainLayout.addWidget(nameLabel, 0, 0)
        mainLayout.addWidget(nameLineEdit, 0, 1, 1, 2) # (0, 1) 一行两列

        mainLayout.addWidget(passwordLabel, 1, 0)
        mainLayout.addWidget(passwordLineEdit, 1, 1, 1, 2) # 一行两列

        mainLayout.addWidget(btnOK, 2, 1)
        mainLayout.addWidget(btnCancel, 2, 2)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QLabelBuddy()
    main.show()

    sys.exit(app.exec_())