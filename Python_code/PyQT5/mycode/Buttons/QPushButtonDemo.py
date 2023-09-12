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

class QPushButtonDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.button1 = QPushButton('first button')
        self.button1.setText('first button...')
        self.button1.setCheckable(True)
        self.button1.toggle()
        self.button1.clicked.connect(lambda:self.whichButton(self.button1))
        self.button1.clicked.connect(self.buttonState)

        # button with image
        self.button2 = QPushButton("img button")
        self.button2.setIcon(QIcon(QPixmap('../image/icon.icon')))
        self.button2.clicked.connect(lambda:self.whichButton(self.button2))

        # disabled button
        self.button3 = QPushButton("disabled button")
        self.button3.setEnabled(False)

        #
        self.button4 = QPushButton("&MyButton")
        self.button4.setDefault(True) # unique for each window
        self.button4.clicked.connect(lambda:self.whichButton(self.button4))

        
        layout.addWidget(self.button1)
        layout.addWidget(self.button2)
        layout.addWidget(self.button3)
        layout.addWidget(self.button4)
        
        self.setLayout(layout)

        self.resize(400, 300)

        self.setWindowTitle('QPushButton Demo')

    def whichButton(self, btn):
        print('button pushed: <' + btn.text() + '>')

    def buttonState(self):
        if self.button1.isChecked():
            print('button1 checked')
        else:
            print('button1 is not checked')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QPushButtonDemo()
    main.show()

    sys.exit(app.exec_())