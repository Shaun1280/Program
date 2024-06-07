import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QMainWindow()
    # 0 完全透明 1 完全不透明
    main.setWindowOpacity(0.2)
    main.resize(400, 200)
    main.show()

    sys.exit(app.exec_())