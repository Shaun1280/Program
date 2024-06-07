import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

class QTextEditDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QTextEdite Demo')

        self.resize(300, 280)

        self.textEdit = QTextEdit()
        self.buttonText = QPushButton('show text')
        self.buttonHTML = QPushButton('show HTML')

        layout = QVBoxLayout()
        layout.addWidget(self.textEdit)
        layout.addWidget(self.buttonText)
        layout.addWidget(self.buttonHTML)

        self.setLayout(layout)

        self.buttonText.clicked.connect(self.onclick_button_text)
        self.buttonHTML.clicked.connect(self.onclick_button_html)

    def onclick_button_text(self):
        self.textEdit.setPlainText('hello world')
        # print(self.textEdit.toPlainText())

    def onclick_button_html(self):
        self.textEdit.setHtml('<font color="blue" size="5">hello world</font>')
        # print(self.textEdit.toHtml())

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QTextEditDemo()
    main.show()

    sys.exit(app.exec_())