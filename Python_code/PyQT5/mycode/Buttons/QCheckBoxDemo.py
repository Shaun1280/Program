import sys

'''
QCheckBox
- unchecked 0
- half-checked 1
- checked 2
'''

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QCheckBoxDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.checkbox1 = QCheckBox('checkbox1')
        self.checkbox1.setChecked(True)
        self.checkbox1.stateChanged.connect(self.checkBoxState)

        self.checkbox2 = QCheckBox('checkbox2')
        self.checkbox2.stateChanged.connect(self.checkBoxState)

        self.checkbox3 = QCheckBox('half-checked')
        self.checkbox3.setTristate(True) # 是否允许半选中
        self.checkbox3.setCheckState(Qt.PartiallyChecked) # 设置半选中状态
        self.checkbox3.stateChanged.connect(self.checkBoxState)

        layout = QHBoxLayout()
        layout.addWidget(self.checkbox1)
        layout.addWidget(self.checkbox2)
        layout.addWidget(self.checkbox3)
        self.setLayout(layout)
 
        self.resize(400, 300)

        self.setWindowTitle('QPushButton Demo')

    def checkBoxState(self):
        checkBox = self.sender()
        print(checkBox.checkState())
        if checkBox.checkState() == Qt.Unchecked:
            print('<' + checkBox.text() + '> is not checked')
        elif checkBox.checkState() == Qt.PartiallyChecked:
            print('<' + checkBox.text() + '> is partially checked')
        elif checkBox.checkState() == Qt.Checked:
            print('<' + checkBox.text() + '> is checked')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QCheckBoxDemo()
    main.show()

    sys.exit(app.exec_())