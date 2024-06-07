import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class MultiSignals(QObject):
    signal1 = pyqtSignal() # 无参
    signal2 = pyqtSignal(int)
    signal3 = pyqtSignal(int, str)
    signal4 = pyqtSignal(list)
    signal5 = pyqtSignal(dict)
    signal6 = pyqtSignal([int, str], [str]) # 重载版本信号 int, str 或 str

    def __init__(self):
        super().__init__()
        self.signal1.connect(self.signalCall1)
        self.signal2.connect(self.signalCall2)
        self.signal3.connect(self.signalCall3)
        self.signal4.connect(self.signalCall4)
        self.signal5.connect(self.signalCall5)
        self.signal6[int, str].connect(self.signalCall6)
        self.signal6[str].connect(self.signalCall6Overload)

        self.signal1.emit()
        self.signal2.emit(2)
        self.signal3.emit(3, 'str')
        self.signal4.emit([4, 5, 6])
        self.signal5.emit({
            'name': 'shaun',
            'age': 30
        })
        self.signal6[int, str].emit(6, 'str')
        self.signal6[str].emit('str')

    def signalCall1(self):
        print('call1')
    
    def signalCall2(self, val):
        print('call2', val)

    def signalCall3(self, val, text):
        print('call3', val, text)

    def signalCall4(self, val):
        print('call4', list)

    def signalCall5(self, dict):
        print('call5', dict)

    def signalCall6(self, val, text):
        print('call6', val, text)

    def signalCall6Overload(self, val):
        print('call6', val)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = MultiSignals()

    sys.exit(app.exec_())