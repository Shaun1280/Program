import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class ScaleImage(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('scale image')

        filename = '../../image/icon.icon'

        img = QImage(filename)

        label1 = QLabel(self)
        label1.setFixedWidth(200)
        label1.setFixedHeight(200)
        img.scaled(label1.width(), label1.height())

        result = img.scaled(label1.width(), label1.height(), Qt.IgnoreAspectRatio, Qt.SmoothTransformation)
        print(result)
        label1.setPixmap(QPixmap.fromImage(result))

        vbox = QVBoxLayout()
        vbox.addWidget(label1)

        self.setLayout(vbox)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = ScaleImage()
    main.show()

    sys.exit(app.exec_())