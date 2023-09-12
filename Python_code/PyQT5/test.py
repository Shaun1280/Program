import sys

# 135

from PyQt5.QtWidgets import QApplication, QMainWindow

from designer_ui.Ui_test import Ui_MainWindow as Ui_test
from designer_ui.Ui_absoluteLayout import Ui_MainWindow as Ui_abs
from designer_ui.Ui_sizePolicy import Ui_MainWindow as Ui_size_policy
from designer_ui.Ui_signal_slot import Ui_MainWindow as Ui_signal_slot
from designer_ui.Ui_menu_toolbar import Ui_MainWindow as Ui_menu_toolbar


if __name__ == '__main__':
    app = QApplication(sys.argv)

    mainWindow = QMainWindow()

    # ui = Ui_test()
    ui = Ui_menu_toolbar()
    ui.setupUi(mainWindow)

    mainWindow.show()
    sys.exit(app.exec_())

    # app = QApplication(sys.argv)
    # w = QWidget()
    # w.resize(300, 150)
    # w.move(300, 300)
    # w.setWindowTitle('hello world')
    # w.show()
    # sys.exit(app.exec_())
