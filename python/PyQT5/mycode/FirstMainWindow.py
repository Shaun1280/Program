import sys

from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QIcon

class FirstMainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(FirstMainWindow, self).__init__(parent)

        # 设置窗口主题
        self.setWindowTitle('first main window app')

        # 设置窗口尺寸
        self.resize(400, 300)

        self.status = self.statusBar()

        self.status.showMessage('只存在五秒的消息', 5000)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    mainWindow = FirstMainWindow()

    mainWindow.show()
    sys.exit(app.exec_())