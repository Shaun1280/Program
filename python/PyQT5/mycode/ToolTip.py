import sys

from PyQt5.QtWidgets import QApplication, QMainWindow, \
    QWidget, QToolTip, QPushButton, QHBoxLayout
from PyQt5.QtGui import QIcon, QFont

class ToolTip(QMainWindow):
    def __init__(self):
        super(ToolTip, self).__init__()
        self.initUI()

    def initUI(self):
        QToolTip.setFont(QFont('SansSerif', 12))
        self.setToolTip('today is <b>Friday</b>')
        self.setGeometry(300, 300, 200, 300)
        self.setWindowTitle('set tool tip')

        self.button1 = QPushButton('my button')
        self.button1.setToolTip('this is a button')

        layout = QHBoxLayout()
        layout.addWidget(self.button1)

        mainFrame = QWidget()
        mainFrame.setLayout(layout)

        self.setCentralWidget(mainFrame)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = ToolTip()
    main.show()

    sys.exit(app.exec_())