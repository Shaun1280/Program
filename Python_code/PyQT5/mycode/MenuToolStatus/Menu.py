import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class Menu(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(300, 600)
        self.setWindowTitle('menu')

        bar = self.menuBar() # 获取菜单栏
        file = bar.addMenu('文件')
        file.addAction('新建') # 

        save = QAction('保存', self) # 创建 action
        save.setShortcut('Ctrl+S') # 设置快捷键
        file.addAction(save)
        save.triggered.connect(self.process) # 设置槽

        edit = file.addMenu('编辑') # 二级菜单
        edit.addAction('复制')
        edit.addAction('粘贴')

        quit = QAction('退出', self)
        file.addAction(quit)

    def process(self, a):
        print(self.sender().text())

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = Menu()
    main.show()

    sys.exit(app.exec_())