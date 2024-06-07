import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class ScrollBar(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.resize(400, 200)
        self.setWindowTitle('Scroll Bar')

        hbox = QHBoxLayout()

        self.label = QLabel('change font color')
        self.labely = self.label.pos().y()
        hbox.addWidget(self.label)

        self.scrollbar1 = QScrollBar()
        self.scrollbar1.setMaximum(255)
        self.scrollbar1.sliderMoved.connect(self.sliderMoved)

        self.scrollbar2 = QScrollBar()
        self.scrollbar2.setMaximum(255)
        self.scrollbar2.sliderMoved.connect(self.sliderMoved)

        self.scrollbar3 = QScrollBar()
        self.scrollbar3.setMaximum(255)
        self.scrollbar3.sliderMoved.connect(self.sliderMoved)

        self.scrollbar4 = QScrollBar()
        self.scrollbar4.setMaximum(255)
        self.scrollbar4.sliderMoved.connect(self.slider4Moved)

        hbox.addWidget(self.scrollbar1)
        hbox.addWidget(self.scrollbar2)
        hbox.addWidget(self.scrollbar3)
        hbox.addWidget(self.scrollbar4)

        self.setGeometry(300, 300, 300, 200)

        self.setLayout(hbox)

    def sliderMoved(self):
        print(
            self.scrollbar1.value(),
            self.scrollbar2.value(),
            self.scrollbar3.value(),
        )

        palette = QPalette()
        palette.setColor(
            QPalette.Foreground,
            QColor(
            self.scrollbar1.value(),
            self.scrollbar2.value(),
            self.scrollbar3.value(),
        ))
        self.label.setPalette(palette)

    def slider4Moved(self):
        self.label.move(
            self.label.pos().x(),
            self.labely + self.scrollbar4.value() // 4
        )

if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = ScrollBar()
    main.show()

    sys.exit(app.exec_())