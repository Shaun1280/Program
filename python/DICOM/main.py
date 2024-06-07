import sys

from PyQt5.QtWidgets import QApplication
from ui.ui_main import MainWindow

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = MainWindow()
    main.show()

    sys.exit(app.exec_())