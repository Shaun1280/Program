from PyQt5.QtCore import QThread, pyqtSignal

from analyzer.analyze import Analyzer

import cv2

class ImageLoadThread(QThread):
    load_finish_signal = pyqtSignal()
    exception_signal = pyqtSignal(str)

    def __init__(self, fname, parent=None):
        super().__init__(parent)
        self.fname = fname

    def run(self):
        # 读取影像
        try:
            self.parent().image.load(self.fname)

            self.load_finish_signal.emit()

        except Exception as e:
            self.exception_signal.emit(str(e))

class SaveAnnoThread(QThread):
    save_finish_signal = pyqtSignal()

    def __init__(self, dirname, parent=None):
        super().__init__(parent)
        self.dirname = dirname

    def run(self):
        self.parent().analyzer.save_anno(self.dirname)

        self.save_finish_signal.emit()

class AnalyzerCreateThread(QThread):
    analyzer_create_finish_signal = pyqtSignal()
    exception_signal = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)

    def run(self):
        try:
            self.parent().analyzer = Analyzer()
            self.analyzer_create_finish_signal.emit()
        except Exception as e:
            self.exception_signal.emit(str(e))

class AnalyzerInitFirstFrameThread(QThread):
    first_frame_init_finish_signal = pyqtSignal()
    exception_signal = pyqtSignal(str)

    def __init__(self, _new=True, _detect=False, _dir='', parent=None):
        super().__init__(parent)
        self._new = _new
        self._detect= _detect
        self.dir = _dir

    def run(self):
        if self.parent().hasImage() == True and self.parent().hasAnalyzer() == True:
            try:
                self.parent().analyzer.init_analyze(
                    self.parent().images_gray,
                    self.parent().images,
                    _new=self._new,
                    _detect=self._detect,
                    _dir=self.dir
                )
                self.parent().analyzer.analyze_one_frame(
                    self.parent().images_gray,
                    self.parent().images
                )
            except Exception as e:
                self.exception_signal.emit(str(e))

        self.first_frame_init_finish_signal.emit()

class AnalyzerResetThread(QThread):
    analyzer_reset_signal = pyqtSignal()
    exception_signal = pyqtSignal(str)

    def __init__(self, _new=True, _detect=False, box=None, _dir='', parent=None):
        super().__init__(parent)
        self._new = _new
        self._detect= _detect
        self.box = box
        self.dir = _dir

    def run(self):
        if self.parent().hasImage() == True and self.parent().hasAnalyzer() == True:
            try:
                self.parent().analyzer.reset(
                    self.parent().images_gray,
                    self.parent().images,
                    _new=self._new,
                    _detect=self._detect,
                    box=self.box,
                    _dir=self.dir
                )
                self.parent().analyzer.analyze_one_frame(
                    self.parent().images_gray,
                    self.parent().images
                )
            except Exception as e:
                self.exception_signal.emit(str(e))

        self.analyzer_reset_signal.emit()

class AnalyzeFramesThread(QThread):
    # frame_num_signal = pyqtSignal(int)

    def __init__(self, parent=None):
        super().__init__(parent)

    def run(self):
        if self.parent().hasAnalyzer() == False or self.parent().hasImage() == False:
            return
        
        self.parent().analyzer.analyze_all(
            self.parent().images_gray,
            self.parent().images
        )

class AnalyzeFramesThread2(QThread):
    analyzed_frames_signal = pyqtSignal(int)
    exception_signal = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)

    def run(self):
        while True:
            if self.parent().hasAnalyzer() == False or self.parent().hasImage() == False:
                break
            
            if self.parent().stop_analyze_frame_by_frame == True:
                cv2.destroyAllWindows()
                break

            if self.parent().analyzer.analyzed_frame + 1 == self.parent().total_frames:
                break
            
            try:
                self.parent().analyzer.analyze_one_frame(
                    self.parent().images_gray,
                    self.parent().images
                )

                self.analyzed_frames_signal.emit(self.parent().analyzer.analyzed_frame)
            
            except Exception as e:
                self.exception_signal.emit(str(e))