from PyQt5.QtWidgets import (QDockWidget, QTabWidget, QWidget, QLabel, QGridLayout)
from PyQt5.QtGui import QPalette, QColor

class InfoTab(QTabWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.tab1 = QWidget()
        self.tab2 = QWidget()

        self.addTab(self.tab1, 'tab1')
        self.addTab(self.tab2, 'tab2')

        self.tab1UI()
        self.tab2UI()

        self.setStyleSheet('''
            QTabWidget {
                width: 290px;
            }
        ''')

    def tab1UI(self):
        layout = QGridLayout()

        tag1 = QLabel('PatientName:')
        tag1.setWordWrap(True)

        tag2 = QLabel('PatientID:')
        tag2.setWordWrap(True)

        tag3 = QLabel('PatientBirthDate:')
        tag3.setWordWrap(True)

        tag4 = QLabel('PatientSex:')
        tag4.setWordWrap(True)

        tag5 = QLabel('PatientAge:')
        tag5.setWordWrap(True)

        tag6 = QLabel('PatientWeight:')
        tag6.setWordWrap(True)
        
        tag7 = QLabel('StudyDate:')
        tag7.setWordWrap(True)

        tag8 = QLabel('StudyTime:')
        tag8.setWordWrap(True)

        tag9 = QLabel('StudyID:')
        tag9.setWordWrap(True)

        tag10 = QLabel('StudyModality:')
        tag10.setWordWrap(True)

        self.PatientName = QLabel('None')
        self.PatientName.setWordWrap(True)

        self.PatientID = QLabel('None')
        self.PatientID.setWordWrap(True)

        self.PatientBirthDate = QLabel('None')
        self.PatientBirthDate.setWordWrap(True)
        
        self.PatientSex = QLabel('None')
        self.PatientSex.setWordWrap(True)

        self.PatientAge = QLabel('None')
        self.PatientAge.setWordWrap(True)

        self.PatientWeight = QLabel('None')
        self.PatientWeight.setWordWrap(True)

        self.StudyDate = QLabel('None')
        self.StudyDate.setWordWrap(True)

        self.StudyTime = QLabel('None')
        self.StudyTime.setWordWrap(True)

        self.StudyID = QLabel('None')
        self.StudyID.setWordWrap(True)

        self.StudyModality = QLabel('None')
        self.StudyModality.setWordWrap(True)

        layout.addWidget(tag1, 0, 0, 1, 1)
        layout.addWidget(self.PatientName, 0, 1, 1, 2)
        layout.addWidget(tag2, 1, 0, 1, 1)
        layout.addWidget(self.PatientID, 1, 1, 1, 2)
        layout.addWidget(tag3, 2, 0, 1, 1)
        layout.addWidget(self.PatientBirthDate, 2, 1, 1, 2)
        layout.addWidget(tag4, 3, 0, 1, 1)
        layout.addWidget(self.PatientSex, 3, 1, 1, 2)
        layout.addWidget(tag5, 4, 0, 1, 1)
        layout.addWidget(self.PatientAge, 4, 1, 1, 2)
        layout.addWidget(tag6, 5, 0, 1, 1)
        layout.addWidget(self.PatientWeight, 5, 1, 1, 2)
        layout.addWidget(tag7, 6, 0, 1, 1)
        layout.addWidget(self.StudyDate, 6, 1, 1, 2)
        layout.addWidget(tag8, 7, 0, 1, 1)
        layout.addWidget(self.StudyTime, 7, 1, 1, 2)
        layout.addWidget(tag9, 8, 0, 1, 1)
        layout.addWidget(self.StudyID, 8, 1, 1, 2)
        layout.addWidget(tag10, 9, 0, 1, 1)
        layout.addWidget(self.StudyModality, 9, 1, 1, 2)

        layout.setColumnStretch(0, 2)
        layout.setColumnStretch(1, 3)

        self.setTabText(0, '患者信息')
        self.tab1.setLayout(layout)

    def tab2UI(self):
        layout = QGridLayout()

        palette1 = QPalette()
        palette2 = QPalette()

        palette1.setColor(QPalette.WindowText, QColor(int(238 / 1.7), int(221 / 1.8), int(130 / 1.8)))
        palette2.setColor(QPalette.WindowText, QColor(int(255 / 1.3), int(127 / 1.3), int(80 / 1.3)))

        tag1 = QLabel('Frame:')
        tag1.setWordWrap(True)

        tag2 = QLabel('会厌软骨区域:')
        tag2.setWordWrap(True)

        tag3 = QLabel('兜住钡餐:')
        tag3.setPalette(palette1)
        tag3.setWordWrap(True)

        tag4 = QLabel('侧漏钡餐:')
        tag4.setPalette(palette2)
        tag4.setWordWrap(True)

        self.frame = QLabel('')
        self.frame.setWordWrap(True)

        self.box = QLabel('')
        self.box.setWordWrap(True)

        self.barium1 = QLabel('')
        self.barium1.setPalette(palette1)
        self.barium1.setWordWrap(True)

        self.barium2 = QLabel('')
        self.barium2.setPalette(palette2)
        self.barium2.setWordWrap(True)

        layout.addWidget(tag1, 0, 0, 1, 1)
        layout.addWidget(self.frame, 0, 1, 1, 2)
        layout.addWidget(tag2, 1, 0, 1, 1)
        layout.addWidget(self.box, 1, 1, 1, 2)
        layout.addWidget(tag3, 2, 0, 1, 1)
        layout.addWidget(self.barium1, 2, 1, 1, 2)
        layout.addWidget(tag4, 3, 0, 1, 1)
        layout.addWidget(self.barium2, 3, 1, 1, 2)

        layout.setColumnStretch(0, 2)
        layout.setColumnStretch(1, 3)
        
        self.setTabText(1, '分析结果')
        self.tab2.setLayout(layout)

class InfoDockWidget(QDockWidget):
    def __init__(self, setting, text, parent):
        super().__init__(text, parent)
        self.initUI()

    def initUI(self):
        self.infoTab = InfoTab()

        self.setWidget(self.infoTab)

        self.setStyleSheet('''
            QDockWidget {
                width: 290px;
                border: 1px solid lightgray;
            }
            QDockWidget::title {
                text-align: center;
                background: rgb(250, 250, 250);
                border-bottom: 1.5px solid #C2C7CB;
            }
        ''')

        # self.addDockWidget(Qt.RightDockWidgetArea, self.items)'
    
    def setTab1Info(self, info):
        if not info is None:
            self.infoTab.PatientName.setText(str(info['PatientName']))
            self.infoTab.PatientID.setText(str(info['PatientID']))
            self.infoTab.PatientBirthDate.setText(str(info['PatientBirthDate']))
            self.infoTab.PatientSex.setText(str(info['PatientSex'])) 
            self.infoTab.PatientAge.setText(str(info['PatientAge']))
            self.infoTab.PatientWeight.setText(str(info['PatientWeight']))

            self.infoTab.StudyDate.setText(str(info['StudyDate']))
            self.infoTab.StudyTime.setText(str(info['StudyTime']))
            self.infoTab.StudyID.setText(str(info['StudyID']))
            self.infoTab.StudyModality.setText(str(info['StudyModality']))

    def setTab2Info(self, frame=None, box=None, barium1=None, barium2=None):
        if not frame is None:
            self.infoTab.frame.setText(str(frame))
        else:
            self.infoTab.frame.setText('')

        if not box is None:
            self.infoTab.box.setText('(x: {}, y: {}, w: {}, h: {})'.format(
                int(box[0]), int(box[1]), int(box[2]), int(box[3])
            ))
        else:
            self.infoTab.box.setText('')

        if not barium1 is None:
            self.infoTab.barium1.setText('{} px'.format(barium1))
        else:
            self.infoTab.barium1.setText('')

        if not barium2 is None:
            self.infoTab.barium2.setText('{} px'.format(barium2))
        else:
            self.infoTab.barium2.setText('')



