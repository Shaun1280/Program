import sys

from PyQt5.QtWidgets import QApplication, QMainWindow, \
    QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QPalette, QIcon, QPixmap
from PyQt5.QtCore import Qt

class QLabelDemo(QWidget):
    def __init__(self):
        super(QLabelDemo, self).__init__()
        self.initUI()

    def initUI(self):
        label1 = QLabel(self)
        label2 = QLabel(self)
        label3 = QLabel(self)
        label4 = QLabel(self)

        label1.setText("<font color=yellow>label1, this is a text</font>")
        label1.setAutoFillBackground(True)
        palette = QPalette()
        palette.setColor(QPalette.Window, Qt.blue)
        label1.setPalette(palette) # set background color
        label1.setAlignment(Qt.AlignCenter)

        label2.setText("<a href='#'>label2, hello world</a>")

        label3.setAlignment(Qt.AlignCenter)
        label3.setToolTip('label3, this is a image label')
        label3.setPixmap(QPixmap("../image/icon.icon"))

        label4.setOpenExternalLinks(True)
        label4.setText("<a href='https://lol.qq.com'>label4</a>")
        label4.setAlignment(Qt.AlignRight)

        vbox = QVBoxLayout()
        vbox.addWidget(label1)
        vbox.addWidget(label2)
        vbox.addWidget(label3)
        vbox.addWidget(label4)

        label2.linkHovered.connect(self.linkHovered)
        # label4.linkActivated.connect(self.linkClicked)

        self.setLayout(vbox)
        self.setWindowTitle('QLabel')
        self.resize(400, 300)

    def linkHovered(self):
        print(self, "linkHovered")

    def linkClicked(self):
        print(self, "linkClicked")


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QLabelDemo()
    main.show()

    sys.exit(app.exec_())