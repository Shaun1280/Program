import sys

from PyQt5.QtWidgets import QApplication, QMainWindow,\
    QDesktopWidget, QWidget, QHBoxLayout, QPushButton
from PyQt5.QtGui import QIcon

def onclick_btn():
    print("onclick_btn")
    print("1 widget.x()={}".format(widget.x())) # 窗口坐标
    print("1 widget.y()={}".format(widget.y())) # 窗口坐标
    print("1 widget.width()={}".format(widget.width())) # 工作区宽度
    print("1 widget.height()={}".format(widget.height())) # 工作区高度

    print("2 widget.x()={}".format(widget.geometry().x())) # 工作区坐标
    print("2 widget.y()={}".format(widget.geometry().y())) # 工作区坐标
    print("2 widget.width()={}".format(widget.geometry().width())) # 工作区宽度
    print("2 widget.height()={}".format(widget.geometry().height())) # 工作区高度

    print("3 widget.x()={}".format(widget.frameGeometry().x())) # 窗口区坐标
    print("3 widget.y()={}".format(widget.frameGeometry().y())) # 窗口区坐标
    print("3 widget.width()={}".format(widget.frameGeometry().width())) # 窗口宽度
    print("3 widget.height()={}".format(widget.frameGeometry().height())) # 窗口高度

app = QApplication(sys.argv)

widget = QWidget()
btn = QPushButton(widget)
btn.setText("按钮")
btn.clicked.connect(onclick_btn)

btn.move(24, 52)

widget.resize(300, 240)

widget.move(250, 200)

widget.setWindowTitle('Screen Gemometry')

widget.show()

sys.exit(app.exec_())