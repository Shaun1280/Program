import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class WindowMinMax(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('window min max')

        self.setWindowFlags(Qt.WindowMaximizeButtonHint | Qt.WindowCloseButtonHint)

        layout = QVBoxLayout()

        maxButton1 = QPushButton()
        maxButton1.setText('窗口最大化1')
        maxButton1.clicked.connect(self.maximize1)
        layout.addWidget(maxButton1)

        maxButton2 = QPushButton()
        maxButton2.setText('窗口最大化2')
        maxButton2.clicked.connect(self.showMaximized)
        layout.addWidget(maxButton2)

        maxButton3 = QPushButton()
        maxButton3.setText('窗口最小化1')
        maxButton3.clicked.connect(self.showMinimized)
        layout.addWidget(maxButton3)

        self.setLayout(layout)

    def maximize1(self):
        desktop = QApplication.desktop()
        # 获取桌面可用尺寸
        rect = desktop.availableGeometry()
        self.setGeometry(rect)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = WindowMinMax()
    main.show()

    sys.exit(app.exec_())