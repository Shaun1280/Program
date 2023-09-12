import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QColorDialogDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.colorButton = QPushButton('设置文字颜色')
        self.colorButton.clicked.connect(self.getColor)
        layout.addWidget(self.colorButton)

        self.colorButton1 = QPushButton('设置背景颜色')
        self.colorButton1.clicked.connect(self.getBGColor)
        layout.addWidget(self.colorButton1)

        self.colorLabel = QLabel('hello, test color dialog demo')
        layout.addWidget(self.colorLabel)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QMessageBox Demo')

    def getColor(self):
        color = QColorDialog.getColor()
        print('color: ', color.red(), color.green(), color.blue())
        # 设置调色板
        p = QPalette()
        p.setColor(QPalette.WindowText, color)
        self.colorLabel.setPalette(p)

    def getBGColor(self):
        color = QColorDialog.getColor()
        print('color: ', color.red(), color.green(), color.blue())
        # 设置调色板
        p = QPalette() # 可以设置成全局，防止另一个字体颜色被覆盖
        p.setColor(QPalette.Window, color)
        self.colorLabel.setAutoFillBackground(True)
        self.colorLabel.setPalette(p)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QColorDialogDemo()
    main.show()

    sys.exit(app.exec_())