import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class GridForm(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 200)
        self.setWindowTitle('grid form')
        
        titleLabel = QLabel('title')
        authorLabel = QLabel('author')
        contentLabel = QLabel('content')

        titleEdit = QLineEdit()
        authorEdit = QLineEdit()
        contentEdit = QTextEdit()

        grid = QGridLayout()
        grid.setSpacing(10)

        grid.addWidget(titleLabel, 1, 0)
        grid.addWidget(titleEdit, 1, 1)

        grid.addWidget(authorLabel, 2, 0)
        grid.addWidget(authorEdit, 2, 1)

        grid.addWidget(contentLabel, 3, 0)
        grid.addWidget(contentEdit, 3, 1, 5, 1)


        self.setLayout(grid)

        
if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = GridForm()
    main.show()

    sys.exit(app.exec_())