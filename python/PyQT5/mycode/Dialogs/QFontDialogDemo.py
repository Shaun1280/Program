import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
getItem
getText
getInt
'''

class QFontDialogDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.fontButton = QPushButton('选择字体')
        self.fontButton.clicked.connect(self.getFont)
        layout.addWidget(self.fontButton)

        self.fontLabel = QLabel('hello, test font demo')
        layout.addWidget(self.fontLabel)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QMessageBox Demo')

    def getFont(self):
        font, ok = QFontDialog.getFont()
        if ok:
            self.fontLabel.setFont(font)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QFontDialogDemo()
    main.show()

    sys.exit(app.exec_())