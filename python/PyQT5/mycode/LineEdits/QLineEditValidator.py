import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon, QIntValidator, QDoubleValidator, QRegExpValidator
from PyQt5.QtCore import QRegExp


class QLineEditValidator(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QLineEdit Validator')

        # create form layout
        formLayout = QFormLayout()

        intLineEdit = QLineEdit()
        doubleLineEdit = QLineEdit()
        expRegLineEdit = QLineEdit()

        formLayout.addRow('int', intLineEdit)
        formLayout.addRow('double', doubleLineEdit)
        formLayout.addRow('expReg', expRegLineEdit)

        intLineEdit.setPlaceholderText('int')
        doubleLineEdit.setPlaceholderText('double')
        expRegLineEdit.setPlaceholderText('expReg')

        intValidator = QIntValidator(self)
        intValidator.setRange(1, 99)

        doubleValidator = QDoubleValidator(self)
        doubleValidator.setRange(-360, 360)
        doubleValidator.setNotation(QDoubleValidator.StandardNotation)
        doubleValidator.setDecimals(2)

        regExp = QRegExp('[a-zA-z0-9]+$')
        validator = QRegExpValidator(self)
        validator.setRegExp(regExp)

        intLineEdit.setValidator(intValidator)
        doubleLineEdit.setValidator(doubleValidator)
        expRegLineEdit.setValidator(validator)

        self.setLayout(formLayout)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QLineEditValidator()
    main.show()

    sys.exit(app.exec_())