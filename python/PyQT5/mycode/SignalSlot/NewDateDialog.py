import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

'''
如果一个窗口 A 与另一个窗口 B 交互，那么 A 尽量不要直接访问 B 窗口的控件
应该通过信号访问，并指定与信号绑定的槽函数
'''

class NewDateDialog(QDialog):
    signal_with_one_arg = pyqtSignal(str)

    def __init__(self, parent = None):
        super().__init__(parent)
        self.setWindowTitle('DateDialog')

        layout = QVBoxLayout()

        self.label = QLabel(self)
        self.label.setText('前者发射内置信号，后者发射自定义信号')

        self.datetime_inner = QDateTimeEdit(self)
        self.datetime_inner.setCalendarPopup(True)
        self.datetime_inner.setDateTime(QDateTime.currentDateTime())

        self.datetime_emit = QDateTimeEdit(self)
        self.datetime_emit.setCalendarPopup(True)
        self.datetime_emit.setDateTime(QDateTime.currentDateTime())

        layout.addWidget(self.label)
        layout.addWidget(self.datetime_inner)
        layout.addWidget(self.datetime_emit)
        
        buttons = QDialogButtonBox(
            QDialogButtonBox.Ok | QDialogButtonBox.Cancel,
            Qt.Horizontal
        )

        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)

        layout.addWidget(buttons)

        self.setLayout(layout)

        self.datetime_emit.dateTimeChanged.connect(self.emit_signal)

    def emit_signal(self):
        date_str = self.datetime_emit.dateTime().toString()
        self.signal_with_one_arg.emit(date_str)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = NewDateDialog()
    main.show()

    sys.exit(app.exec_())