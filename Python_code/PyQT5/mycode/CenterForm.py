import sys

from PyQt5.QtWidgets import QApplication, QMainWindow, QDesktopWidget
from PyQt5.QtGui import QIcon

class CenterForm(QMainWindow):
    def __init__(self, parent=None):
        super(CenterForm, self).__init__(parent)

        # 设置窗口主题
        self.setWindowTitle('center form app')

        # 设置窗口尺寸
        self.resize(400, 300)

        self.status = self.statusBar()

        self.status.showMessage('只存在五秒的消息', 5000)

        self.center()

    def center(self):
        screen = QDesktopWidget().screenGeometry()
        window = self.geometry()
        new_left = (screen.width() - window.width()) / 2
        new_top = (screen.height() - window.height()) / 2

        self.move(new_left, new_top)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    mainWindow = CenterForm()

    mainWindow.show()
    sys.exit(app.exec_())