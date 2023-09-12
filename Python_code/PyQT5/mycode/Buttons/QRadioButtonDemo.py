import sys

'''
QAbstractButton
- QPushButton
- QToolButton
- QRadioButton
- QCheckBox
'''

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QRadioButtonDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.button1 = QRadioButton('btn1')
        self.button1.toggled.connect(self.buttonState)
        self.button1.setChecked(True)

        self.button2 = QRadioButton('btn2')
        self.button2.toggled.connect(self.buttonState)
        
        layout = QHBoxLayout()
        layout.addWidget(self.button1)
        layout.addWidget(self.button2)
        self.setLayout(layout)

        self.resize(400, 300)

        self.setWindowTitle('QPushButton Demo')

    def buttonState(self):
        radioButton = self.sender()
        if radioButton.isChecked() == True:
            print('<' + radioButton.text() + '> is checked')
        else:
            print('<' + radioButton.text() + '> is not checked')
                

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QRadioButtonDemo()
    main.show()

    sys.exit(app.exec_())