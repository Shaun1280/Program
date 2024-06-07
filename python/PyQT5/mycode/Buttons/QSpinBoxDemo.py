import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class QSpinBoxDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.label = QLabel('current value: ?')
        self.label.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.label)

        self.spinBox = QSpinBox()
        self.spinBox.valueChanged.connect(self.spinBoxValueChanged)
        self.spinBox.setValue(18)
        self.spinBox.setRange(0, 999)
        # set single step
        layout.addWidget(self.spinBox)

        self.setLayout(layout)
        self.resize(400, 300)
        self.setWindowTitle('QPushButton Demo')

    def spinBoxValueChanged(self):
        self.label.setText('current value:' + str(self.spinBox.value()))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../image/icon.icon'))

    main = QSpinBoxDemo()
    main.show()

    sys.exit(app.exec_())