import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class NNSignal(QObject):
    signal1 = pyqtSignal() # 无参
    signal2 = pyqtSignal(int)

    def __init__(self):
        super().__init__()

        self.signal1.connect(self.call1)
        self.signal1.connect(self.call11)

        self.signal1.emit()

        self.signal2.connect(self.signal1) # signal2 绑定到 signal1 上
        self.signal2.emit(2) # 触发了信号 1

        self.signal1.disconnect(self.call1) # 取消绑定
        self.signal1.disconnect(self.call11)
        self.signal2.disconnect(self.signal1)

        self.signal1.connect(self.call1)
        self.signal2.connect(self.call2)

        print('\n')

        self.signal1.emit()
        self.signal2.emit(2)

    def call1(self):
        print('call1')

    def call11(self):
        print('call11')

    def call2(self, val):
        print('call2', val)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = NNSignal()

    sys.exit(app.exec_())