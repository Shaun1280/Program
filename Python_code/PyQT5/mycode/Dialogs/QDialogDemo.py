import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
QMessageBox
QColorDialog
QFileDialog
QFontDialog
QInputDialog

QMainWindow
QWidget
QDialog
'''

class QDialogDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.button = QPushButton(self)
        self.button.setText('弹出对话框')
        self.button.move(50, 50)
        self.button.clicked.connect(self.showDialog)

        layout.addWidget(self.button)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QPushButton Demo')

    def showDialog(self):
        dialog = QDialog()
        button = QPushButton('ok', dialog)
        button.clicked.connect(dialog.close)
        button.move(50, 50)
        dialog.setWindowTitle('Dialog Window')
        dialog.setWindowModality(Qt.ApplicationModal)

        dialog.exec()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QDialogDemo()
    main.show()

    sys.exit(app.exec_())