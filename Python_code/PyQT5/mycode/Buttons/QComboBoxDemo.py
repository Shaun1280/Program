import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QCombooxDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.label = QLabel('please select language')

        self.comboBox = QComboBox()
        self.comboBox.addItem('C++')
        self.comboBox.addItems(['Python', 'Java', 'Javascript'])
        self.comboBox.currentIndexChanged.connect(self.selectionChange)

        layout.addWidget(self.comboBox)
        layout.addWidget(self.label)

        self.setLayout(layout)
        self.setWindowTitle('QComboBox Demo')
    
    def selectionChange(self, idx):
        self.label.setText(self.comboBox.currentText())
        self.label.adjustSize()

        for i in range(self.comboBox.count()):
            print('item' + str(i) + '=' + self.comboBox.itemText(i))
        print('current index is ' + str(idx))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QCombooxDemo()
    main.show()

    sys.exit(app.exec_())