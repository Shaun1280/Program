import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class TreeEvent(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 400)
        self.setWindowTitle('basic tree widget')

        self.tree = QTreeWidget()
        # 指定列数
        self.tree.setColumnCount(2)
        # 指定列标签
        self.tree.setHeaderLabels(['key', 'value'])

        root = QTreeWidgetItem(self.tree)
        root.setText(0, 'root')
        root.setIcon(0, QIcon('../../../image/icon.icon'))
        self.tree.setColumnWidth(0, 120)

        # 添加子节点
        child1 = QTreeWidgetItem(root)
        child1.setText(0, 'node1')
        child1.setText(1, '233')
        child1.setIcon(0, QIcon('../../../image/icon.icon'))
        child1.setCheckState(0, Qt.Checked)

        # 为 2 添加子节点
        child11 = QTreeWidgetItem(child1)
        child11.setText(0, 'node11')
        child11.setText(1, 'hahaha')

        # 添加子节点2
        child2 = QTreeWidgetItem(root)
        child2.setText(0, 'node2')
        child2.setText(1, '6666')
        child2.setIcon(0, QIcon('../../../image/icon.icon'))

        self.tree.clicked.connect(self.onTreeClicked)
        self.tree.expandAll()

        self.setCentralWidget(self.tree)
    
    def onTreeClicked(self, index):
        item = self.tree.currentItem()
        print(index.row())
        print(item.text(0) + ' | ' + item.text(1))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = TreeEvent()
    main.show()

    sys.exit(app.exec_())