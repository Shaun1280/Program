from __future__ import absolute_import

import numpy as np
import cv2
import os

from .eco_tracker import ECO

def eco_track(images, bbox):
    tracker = ECO()

    for f, img in enumerate(images):
        if f == 0:
            tracker.init(img, bbox)
        else:
            bbox = tracker.update(img)
            bbox = list(map(int, bbox))
        
         # Tracking success
        p1 = (int(bbox[0]), int(bbox[1]))
        p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
        cv2.rectangle(img, p1, p2, (255, 255, 0), 2, 1)
        cv2.imshow("Tracking", img)
        cv2.waitKey(30)
