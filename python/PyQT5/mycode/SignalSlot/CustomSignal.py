import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class CustomSignal(QObject):
    sendMsg = pyqtSignal(object) # 参数为 object

    # 3 args
    sendMsg3 = pyqtSignal(str, int, int)

    def run(self):
        self.sendMsg.emit('hello world') # arg = hello world

    def run3(self):
        self.sendMsg3.emit('hello', 233, 666)

class CustomSlot(QObject):
    def get(self, msg):
        print('msg: ' + msg)

    def get3(self, msg, num1, num2): 
        print(msg, num1, num2)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    send = CustomSignal()
    slot = CustomSlot()

    send.sendMsg.connect(slot.get)
    send.sendMsg3.connect(slot.get3)

    send.run()
    send.run3()

    send.sendMsg.disconnect()

    sys.exit(app.exec_())