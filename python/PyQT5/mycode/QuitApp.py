import sys

from PyQt5.QtWidgets import QApplication, QMainWindow,\
    QDesktopWidget, QWidget, QHBoxLayout, QPushButton
from PyQt5.QtGui import QIcon

class QuitApp(QMainWindow):
    def __init__(self, parent=None):
        super(QuitApp, self).__init__(parent)

        # 设置窗口主题
        self.setWindowTitle('quit app')

        self.resize(400, 300)

        self.button1 = QPushButton('quit app')
        # 将信号与槽关联
        self.button1.clicked.connect(self.onclick_button)

        layout = QHBoxLayout()
        layout.addWidget(self.button1)

        mainFrame = QWidget()
        mainFrame.setLayout(layout)

        self.setCentralWidget(mainFrame)

        self.center()
    
    # 按钮单击事件的方法
    def onclick_button(self):
        sender = self.sender()
        print(sender.text() + " was pushed")
        app = QApplication.instance()
        app.quit()

    def center(self):
        screen = QDesktopWidget().screenGeometry()
        window = self.geometry()
        new_left = (screen.width() - window.width()) / 2
        new_top = (screen.height() - window.height()) / 2

        self.move(new_left, new_top)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    mainWindow = QuitApp()

    mainWindow.show()
    sys.exit(app.exec_())