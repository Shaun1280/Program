import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class LabelButtonBG(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('label button background')
        
        label1 = QLabel()
        label1.setToolTip('this is a label')
        label1.setStyleSheet('''
            QLabel{
                border-image:url('../../image/icon.icon');
            }
        ''')

        label1.setFixedWidth(476)
        label1.setFixedHeight(259)

        btn1 = QPushButton()
        btn1.setObjectName('btn1')
        btn1.setMaximumSize(100, 100)
        btn1.setMinimumSize(100, 100)

        style = '''
            #btn1{
                background-image:url('../../image/tmp.jfif');
            }
            #btn1.Pressed{
                background-image:url('../../image/icon.icon');
            }
        '''

        

        btn1.setStyleSheet(style)

        vbox = QVBoxLayout()
        vbox.addWidget(label1)
        vbox.addStretch(0)
        vbox.addWidget(btn1)

        self.setLayout(vbox)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = LabelButtonBG()

    main.show()
    sys.exit(app.exec_())