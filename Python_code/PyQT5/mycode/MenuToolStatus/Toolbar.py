import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class Toolbar(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('tool bar')

        tb1 = self.addToolBar('File')
        new = QAction(QIcon('../../image/icon.icon'), 'new', self)
        tb1.addAction(new)

        open_action = QAction(QIcon('../../image/icon.icon'), "open", self)
        tb1.addAction(open_action)

        save_action = QAction(QIcon('../../image/tmp.jfif'), "save", self)
        tb1.addAction(save_action)

        # 右侧显示
        tb1.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)

        tb2 = self.addToolBar('File1')
        new1 = QAction(QIcon('../../image/icon.icon'), 'new1', self)
        tb2.addAction(new1)
        # 右侧显示
        tb2.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)

        tb1.actionTriggered.connect(self.toolbtnpressed)
        tb2.actionTriggered.connect(self.toolbtnpressed)

    def toolbtnpressed(self, a):
        print(a.text() + ' is pressed')


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = Toolbar()
    main.show()

    sys.exit(app.exec_())