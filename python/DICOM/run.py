from __future__ import absolute_import, division, print_function

from dicom.image import DicomImage
from analyzer.analyze import Analyzer
import cv2

mode_list = ["epiglottis", "detect", "show", "barium", "analyze"]

mode = mode_list[4]

if __name__ == '__main__':
    image = DicomImage()
    analyzer = Analyzer()
    image.load('data/L18070487-0006/607D1E32BD694C338FBF5E9F724329CA.dic')
    # L18120071-0001/B0A17BA47F2C4B7EAFC596F2F7B4D6D2
    # image.load('data/L18120071-0001/B0A17BA47F2C4B7EAFC596F2F7B4D6D2.dic')
    
    images = image.get_images()
    images_gray = image.get_gray_images()

    # image.show_images(2.0)
    # image.track_barium()
    if mode == "epiglottis":
        print("epiglottis...")
        analyzer.track_epiglottis(images)
    elif mode == "detect":
        print("detect...")
        analyzer.detect_all_boxes(images)
    elif mode == "show":
        print("show...")
        analyzer.show_track_epiglottis_result(images)
    elif mode == "barium":
        print("barium...")
        analyzer.track_barium(images_gray)
    elif mode == "analyze":
        print("analyzing...")
        analyzer.init_analyze(images_gray, images, _new=False, _detect=False, save=False) 
        analyzer.analyze_all(
            images_gray, images
        )
        # img = analyzer.frame_image_analyzed(images, 0, True, True)
        # cv2.imshow('img', img)
        # cv2.waitKey(0)
