import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class WindowStyle(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('set win style')

        horizontalLayout = QHBoxLayout()
        self.styleLabel = QLabel('set win style')
        horizontalLayout.addWidget(self.styleLabel)

        self.styleComboBox = QComboBox()
        self.styleComboBox.addItems(QStyleFactory.keys())

        # 获取当前风格
        print(QApplication.style().objectName())
        index = self.styleComboBox.findText(
            QApplication.style().objectName(),
            Qt.MatchFixedString
        )
        self.styleComboBox.setCurrentIndex(index)

        self.styleComboBox.activated[str].connect(self.handleStyleChanged)

        horizontalLayout.addWidget(self.styleComboBox)

        self.setLayout(horizontalLayout)

    def handleStyleChanged(self, style):
        QApplication.setStyle(style)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = WindowStyle()
    main.show()

    sys.exit(app.exec_())