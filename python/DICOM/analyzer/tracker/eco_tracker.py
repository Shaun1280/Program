import numpy as np
from .eco.tracker import ECOTracker
from .eco.config.otb_hc_config import OTBHCConfig
import cv2

class ECO():
    def __init__(self):
        self.config = OTBHCConfig()

    def init(self,first_frame,bbox):
        if np.all(first_frame[:,:,0]==first_frame[:,:,1]):
            self.tracker = ECOTracker(is_color=False, config=self.config)
            first_frame=first_frame[:,:,:1]
        else:
            self.tracker=ECOTracker(is_color=True,config=self.config)
            first_frame=cv2.cvtColor(first_frame,cv2.COLOR_BGR2RGB)
        self.tracker.init(first_frame,bbox)


    def update(self,current_frame,vis=False):
        if self.tracker._is_color is True:
            current_frame=cv2.cvtColor(current_frame,cv2.COLOR_BGR2RGB)
        else:
            current_frame=current_frame[:,:,:1]

        # bbox=self.tracker.update(current_frame,train=True,vis=True)
        bbox=self.tracker.update(current_frame,train=True,vis=vis)

        if vis is True:
            self.score=self.tracker.score
            self.crop_size = tuple(self.tracker.crop_size.astype(np.int64))
        x1, y1, w, h = bbox[0], bbox[1], bbox[2] - bbox[0], bbox[3] - bbox[1]
        pos = [x1, y1, w, h]
        return pos



