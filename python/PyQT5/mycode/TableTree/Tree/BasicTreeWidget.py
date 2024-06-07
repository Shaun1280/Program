import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class BasicTreeWidget(QMainWindow):
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
        child1.setText(1, 'value of node1')
        child1.setIcon(0, QIcon('../../../image/icon.icon'))
        child1.setCheckState(0, Qt.Checked)

        # 子节点 2
        child2 = QTreeWidgetItem(root)
        child2.setText(0, 'node2')
        child2.setIcon(0, QIcon('../../../image/icon.icon'))

        # 为 2 添加子节点
        child21 = QTreeWidgetItem(child2)
        child21.setText(0, 'node21')

        self.tree.expandAll()

        self.setCentralWidget(self.tree)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = BasicTreeWidget()
    main.show()

    sys.exit(app.exec_())