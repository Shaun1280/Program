import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
子控件选择器
'''

class QssSelector(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('qss sub class')
        
        combo = QComboBox(self)
        combo.setObjectName('myComboBox')
        combo.addItem('windows')
        combo.addItem('linux')
        combo.addItem('mac')

        combo.move(50, 50)

        self.setGeometry(250, 300, 320, 150)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QssSelector()

    qssStyle = '''
        QComboBox#myComboBox::drop-down {
            image:url('../../image/icon.icon')
        }
    '''

    main.setStyleSheet(qssStyle)
    main.show()

    sys.exit(app.exec_())