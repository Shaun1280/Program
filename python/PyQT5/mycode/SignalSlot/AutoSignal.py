import sys

from PyQt5 import QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *

class AutoSignal(QWidget):
    def __init__(self):
        super().__init__()

        self.okButton = QPushButton('ok', self)
        self.okButton.setObjectName('okButton')

        self.cancelButton = QPushButton('cancel', self)
        self.cancelButton.setObjectName('cancelButton')

        layout = QHBoxLayout()
        layout.addWidget(self.okButton)
        layout.addWidget(self.cancelButton)
        self.setLayout(layout)
        QtCore.QMetaObject.connectSlotsByName(self)
        # self.okButton.clicked.connect(self.onButtonClicked)
        
        self.setLayout(layout)

    @QtCore.pyqtSlot() # on_objName_signalName
    def on_okButton_clicked(self):
        print('ok button clicked')

    @QtCore.pyqtSlot()
    def on_cancelButton_clicked(self):
        print('cancel button clicked')


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = AutoSignal()
    main.show()

    sys.exit(app.exec_())