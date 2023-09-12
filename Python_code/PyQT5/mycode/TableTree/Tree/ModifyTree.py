import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class ModifyTree(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(600, 400)
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

        addBtn = QPushButton('add node')
        addBtn.clicked.connect(self.addNode)

        updateBtn = QPushButton('update node')
        updateBtn.clicked.connect(self.updateNode)

        deleteBtn = QPushButton('delete node')
        deleteBtn.clicked.connect(self.deleteNode)

        layout = QVBoxLayout()
        layout.addWidget(addBtn)
        layout.addWidget(updateBtn)
        layout.addWidget(deleteBtn)
        layout.addWidget(self.tree)

        self.tree.expandAll()
        self.setLayout(layout)

    def onTreeClicked(self, index):
        item = self.tree.currentItem()
        print(index.row())
        print(item.text(0) + ' | ' + item.text(1))

    def addNode(self):
        item = self.tree.currentItem()
        if not item is None:
            node = QTreeWidgetItem(item)
            node.setText(0, 'new Node')
            node.setText(1, 'newValue')
        else:
            print('item is none')

    def updateNode(self):
        item = self.tree.currentItem()
        if not item is None:
            item.setText(0, 'modify node')
            item.setText(1, 'value modified')
        else:
            print('item is none')

    def deleteNode(self):
        root = self.tree.invisibleRootItem()
        for item in self.tree.selectedItems():
            (item.parent() or root).removeChild(item)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = ModifyTree()
    main.show()

    sys.exit(app.exec_())