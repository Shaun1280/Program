import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
QThread

QLCDNumber

自定义信号 WorkThread(QThread)
'''

sec = 0

class WorkThread(QThread):
    timer = pyqtSignal() # 每隔一秒发送一次信号
    end = pyqtSignal() # 计数完成后发送信号
    
    def run(self):
        while True:
            self.sleep(1) # 休眠 1s
            if sec == 5:
                self.end.emit() # 发送 end 信号
                break

            self.timer.emit() # 发送 timer 信号

class Counter(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('counter')

        layout = QVBoxLayout()
        self.lcdNumber = QLCDNumber()
        layout.addWidget(self.lcdNumber)

        button = QPushButton('start counting')
        layout.addWidget(button)

        self.workThread = WorkThread()
        self.workThread.timer.connect(self.countTime)
        self.workThread.end.connect(self.end)

        button.clicked.connect(self.work)
        
        self.setLayout(layout)

    def countTime(self):
        global sec
        sec = sec + 1
        self.lcdNumber.display(sec)

    def end(self):
        QMessageBox().information(self, 'info', 'end', QMessageBox.Ok)

    def work(self):
        self.workThread.start()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = Counter()
    main.show()

    sys.exit(app.exec_())