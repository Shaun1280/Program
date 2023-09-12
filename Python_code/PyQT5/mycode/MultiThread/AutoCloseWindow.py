import sys

'''
QTimer
QThread
多线程：同时完成多种任务
'''

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    label = QLabel('<font color=red size=140><b>Hello World! Closing in 5s</b></font>')
    label.setWindowFlags(Qt.SplashScreen | Qt.FramelessWindowHint)
    label.show()
    QTimer.singleShot(5000, app.quit)

    sys.exit(app.exec_())