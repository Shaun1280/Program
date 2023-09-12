from PyQt5.QtWidgets import (QWidget, QApplication, QHBoxLayout, 
                             QRadioButton, QLineEdit, QCheckBox, 
                             QLabel, QPushButton, QVBoxLayout)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt, pyqtSignal

import sys
import os

class ExportWidget(QWidget):
    export_signal = pyqtSignal(int, int, bool, bool) # l, r, epiglottis, barium
    def __init__(self, parent=None):
        super().__init__(parent) # parent = ui_main

        self.total_frames = 0

        self.initUI()

    def initUI(self):
        self.resize(400, 300)
        self.setWindowTitle('导出影像')
        self.setWindowIcon(QIcon(os.path.join(os.path.dirname(__file__), 'images/export.png')))
        self.setWindowFlags(self.windowFlags() | Qt.Dialog)

        self.initSingleExport()
        self.initMultiExport()
        self.initAnnoSelect()
        self.initBottomButtons()

        layout = QVBoxLayout()

        layout.addWidget(self.singleExport)
        layout.addWidget(self.multiExport)
        layout.addStretch(1)
        layout.addWidget(self.annoSelect)
        layout.addStretch(1)
        layout.addWidget(self.bottomButtons)

        self.setLayout(layout)

    def initSingleExport(self):
        self.singleExport = QWidget()

        layout = QHBoxLayout()

        self.singleExportButton = QRadioButton('导出单帧图像:')
        self.singleExportButton.setChecked(True)
        self.singleExportButton.clicked.connect(lambda :{
            self.multiExportButton.setChecked(False)
        })

        self.singleFrameEdit = QLineEdit()
        self.singleFrameEdit.setText('1')
        self.singleFrameEdit.setAlignment(Qt.AlignRight)
        self.singleFrameEdit.setFixedWidth(30)

        self.singleFrameEdit.textEdited.connect(self.frameTextEdit)
        self.singleFrameEdit.returnPressed.connect(self.singleFrameEdit.clearFocus)
        self.singleFrameEdit.editingFinished.connect(self.frameEditFinish)

        layout.addWidget(self.singleExportButton)
        layout.addWidget(self.singleFrameEdit)
        self.singleExport.setLayout(layout)

    def initMultiExport(self):
        self.multiExport = QWidget()

        layout = QHBoxLayout()

        self.multiExportButton = QRadioButton('导出多帧图像:')
        self.multiExportButton.clicked.connect(lambda: {
            self.singleExportButton.setChecked(False)
        })

        self.multiFrameEdit1 = QLineEdit()
        self.multiFrameEdit1.setText('1')
        self.multiFrameEdit1.setAlignment(Qt.AlignRight)
        self.multiFrameEdit1.setFixedWidth(30)

        self.multiFrameEdit1.textEdited.connect(self.frameTextEdit)
        self.multiFrameEdit1.returnPressed.connect(self.singleFrameEdit.clearFocus)
        self.multiFrameEdit1.editingFinished.connect(self.frameEditFinish)

        label = QLabel('-')

        self.multiFrameEdit2 = QLineEdit()
        self.multiFrameEdit2.setText('1')
        self.multiFrameEdit2.setAlignment(Qt.AlignRight)
        self.multiFrameEdit2.setFixedWidth(30)

        self.multiFrameEdit2.textEdited.connect(self.frameTextEdit)
        self.multiFrameEdit2.returnPressed.connect(self.singleFrameEdit.clearFocus)
        self.multiFrameEdit2.editingFinished.connect(self.frameEditFinish)

        layout.addWidget(self.multiExportButton)
        layout.addStretch(1)
        layout.addWidget(self.multiFrameEdit1)
        layout.addWidget(label)
        layout.addWidget(self.multiFrameEdit2)

        self.multiExport.setLayout(layout)

    def initAnnoSelect(self):
        self.annoSelect = QWidget()

        layout = QVBoxLayout()

        self.checkBox = QCheckBox('同时导出会厌软骨跟踪框')
        self.checkBox.setChecked(True)

        self.checkMarkers = QCheckBox('同时导出钡餐标记')
        self.checkMarkers.setChecked(True)

        layout.addWidget(self.checkBox)
        layout.addWidget(self.checkMarkers)

        self.annoSelect.setLayout(layout)

    def initBottomButtons(self):
        self.bottomButtons = QWidget()

        layout = QHBoxLayout()

        ok = QPushButton('ok', self)
        ok.clicked.connect(self.emitExportSignal)
        cancel = QPushButton('cancel', self)
        cancel.clicked.connect(lambda: {
            self.close()
        })

        layout.addStretch(1)
        layout.addWidget(ok)
        layout.addWidget(cancel)

        self.bottomButtons.setLayout(layout)
    
    def emitExportSignal(self):
        l = 1
        r = 1

        if self.singleExportButton.isChecked():
            l = r = int(self.singleFrameEdit.text())
        elif self.multiExportButton.isChecked():
            l = int(self.multiFrameEdit1.text())
            r = int(self.multiFrameEdit2.text())

        if l > r:
            l, r = r, l

        self.export_signal.emit(
            l, r,
            self.checkBox.isChecked(),
            self.checkMarkers.isChecked()
        )
        self.close()

    def show(self):
        # self.parent().mainWidget
        if not self.parent() is None:
            mainWidget = self.parent().mainWidget
            self.total_frames = mainWidget.total_frames
            self.multiFrameEdit2.setText(str(self.total_frames))
        super().show()

    def frameTextEdit(self):
        text = self.sender().text()

        if text == '':
            return
        elif text.isdecimal() == False:
            self.sender().setText('1')
        else:
            value = int(text)
            if value <= 0:
                value = 1

            if value > self.total_frames:
                value = self.total_frames
            self.sender().setText(str(value))

    def frameEditFinish(self):
        text = self.sender().text()
        if text == '':
            self.sender().setText('1')

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = ExportWidget()
    main.show()

    sys.exit(app.exec_())