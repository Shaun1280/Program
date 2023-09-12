import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class FormLayout(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('form layout')

        formLayout = QFormLayout()
        
        titleLabel = QLabel('title')
        authorLabel = QLabel('author')
        contentLabel = QLabel('content')

        titleEdit = QLineEdit()
        authorEdit = QLineEdit()
        contentEdit = QTextEdit()

        formLayout.addRow(titleLabel, titleEdit)
        formLayout.addRow(authorLabel, authorEdit)
        formLayout.addRow(contentLabel, contentEdit)
        
        self.setLayout(formLayout)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = FormLayout()
    main.show()

    sys.exit(app.exec_())