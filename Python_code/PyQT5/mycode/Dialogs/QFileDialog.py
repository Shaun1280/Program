import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QFileDialogDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.button1 = QPushButton('load image')
        self.button1.clicked.connect(self.loadImage)
        layout.addWidget(self.button1)

        self.imageLabel = QLabel()
        layout.addWidget(self.imageLabel)

        self.button2 = QPushButton('load txt')
        self.button2.clicked.connect(self.loadText)
        layout.addWidget(self.button2)

        self.contents = QTextEdit()
        layout.addWidget(self.contents)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QPushButton Demo')

    def loadImage(self):
        fname, _ = QFileDialog.getOpenFileName(self, 'open file', '.', '图像文件(*.jpq *.png)')
        print(fname)
        self.imageLabel.setPixmap(QPixmap(fname))

    def loadText(self):
        dialog = QFileDialog()
        dialog.setFileMode(QFileDialog.AnyFile)
        dialog.setFilter(QDir.Files)

        if dialog.exec():
            filenames = dialog.selectedFiles()
            with open(filenames[0], encoding='utf-8', mode='r') as f:
                data = f.read()
                self.contents.setText(data)
                # with 结束自动调用 close
        pass


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QFileDialogDemo()
    main.show()

    sys.exit(app.exec_())