import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
# from PyQt5.QtCore import QRegExp


class QLineEditMask(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Use QLineEdit Mask to restrict input')

        formLayout = QFormLayout()

        ipLineEdit = QLineEdit()
        macLineEdit = QLineEdit()
        dateLineEdit = QLineEdit()
        licenseLineEdit = QLineEdit()

        ipLineEdit.setInputMask("000.000.000.000;_")
        macLineEdit.setInputMask("HH:HH:HH:HH:HH:HH;_")
        dateLineEdit.setInputMask("0000-00-00;_")
        licenseLineEdit.setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#")

        formLayout.addRow('num mask', ipLineEdit)
        formLayout.addRow('mac mask', macLineEdit)
        formLayout.addRow('data mask', dateLineEdit)
        formLayout.addRow('license mask', licenseLineEdit)

        self.setLayout(formLayout)



if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QLineEditMask()
    main.show()

    sys.exit(app.exec_())