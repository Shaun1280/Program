import sys

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class DateDialog(QDialog):
    def __init__(self, parent = None):
        super().__init__(parent)
        self.setWindowTitle('DateDialog')

        layout = QVBoxLayout()
        self.datetime = QDateTimeEdit()
        self.datetime.setCalendarPopup(True)
        self.datetime.setDateTime(QDateTime.currentDateTime())

        layout.addWidget(self.datetime)

        buttons = QDialogButtonBox(
            QDialogButtonBox.Ok | QDialogButtonBox.Cancel,
            Qt.Horizontal
        )

        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)

        layout.addWidget(buttons)

        self.setLayout(layout)

    def dateTime(self):
        return self.datetime.dateTime()
    
    @staticmethod
    def getDateTime(parent = None):
        dialog = DateDialog(parent)
        result = dialog.exec()
        date = dialog.dateTime()
        return (date.date(), date.time(), result == QDialog.Accepted)


if __name__ == '__main__':
    app = QApplication(sys.argv)

    app.setWindowIcon(QIcon('../../image/icon.icon'))

    main = DateDialog()
    main.show()

    sys.exit(app.exec_())