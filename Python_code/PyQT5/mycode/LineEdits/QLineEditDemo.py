import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon, QIntValidator, QFont, QDoubleValidator
from PyQt5.QtCore import Qt

class QLineEditDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        edit1 = QLineEdit()

        # int validator
        edit1.setValidator(QIntValidator())
        edit1.setMaxLength(4)
        edit1.setAlignment(Qt.AlignRight)
        edit1.setFont(QFont('Arial', 10))
        
        edit2 = QLineEdit()
        edit2.setValidator(QDoubleValidator(0.99, 99.99, 2))
        edit2.setMaxLength(5)

        edit3 = QLineEdit()
        edit3.setInputMask('99-9999-9999;#')

        edit4 = QLineEdit()
        edit4.textChanged.connect(self.textChanged)

        edit5 = QLineEdit()
        edit5.setEchoMode(QLineEdit.Password)
        edit5.editingFinished.connect(self.enterPressed)

        edit6 = QLineEdit('hello world')
        edit6.setReadOnly(True)

        formLayout = QFormLayout()
        formLayout.addRow('int validator', edit1)
        formLayout.addRow('double validator', edit2)
        formLayout.addRow('mask', edit3)
        formLayout.addRow('textChanged', edit4)
        formLayout.addRow('password', edit5)
        formLayout.addRow('read only', edit6)

        self.setLayout(formLayout)
        self.setWindowTitle('QLineEdit Demo')

    def textChanged(self, text):
        print('input changed to: ', text)
    
    def enterPressed(self):
        print('enterPressed')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QLineEditDemo()
    main.show()

    sys.exit(app.exec_())