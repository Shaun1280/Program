from .dicom import Dicom
import numpy as np

from . import utils
import cv2
import os

class DicomImage:
    def __init__(self):
        self.dicom = Dicom()

        self.origin_gray_images = None
        self.images = None

    def load(self, path):
        self.origin_gray_images = None
        self.images = None
        
        self.dicom.load_dicom(path)
        self.info, self.origin_gray_images = self.dicom.get_dicom()

        str = path.split('/', 1)[1]
        str = str.split('.')[0]
        self.info['ImageName'] = str

        print(self.info['ImageName'])
        print("dicom {} loaded\n UID = {}".format(path, self.info['SOPInstanceUID']))

        self.images = self.image_processing(self.origin_gray_images)

        print(self.images.nbytes) # 296 MB

    def image_processing(self, images):
        images2 = np.zeros((images.shape[0], images.shape[1], images.shape[2], 3), dtype=np.uint8)
        # images3 = np.zeros((images.shape[0], images.shape[1], images.shape[2], 3), dtype=np.uint8)

        print(images2.shape)

        for f, img in enumerate(images):
            images2[f] = cv2.cvtColor(utils.laplacian(img), cv2.COLOR_BGR2RGB)
            # images3[f] = cv2.cvtColor(utils.inv(img), cv2.COLOR_BGR2RGB)
            # histogram, bins = np.histogram(img2, bins=255, range=[0, 255])
            # plt.plot(histogram, color="g")
            # plt.axis([0, 255, 0, np.max(histogram)])
            # plt.xlabel("gray level")
            # plt.ylabel("number of pixels")
            # plt.show()

        return images2

    def get_frame_img(self, frame_num=0):
        assert self.images is not None
        return self.images[frame_num]

    def get_gray_images(self): # c = 1
        return self.origin_gray_images

    def get_images(self): # c = 3
        return self.images

    def show_images(self, speed=1.0):
        milliseconds_per_sec = 1000
        patient_id = self.info['PatientID']
        patient_name = self.info['PatientName']
        series_num = self.info['SeriesNumber']
        display_frame_rate = self.info['RecommendedDisplayFrameRate']

        winname = 'window_{}_{}_{}'.format(
            patient_id, patient_name, series_num)

        assert self.images is not None

        for img in self.images:
            cv2.imshow(winname, img)
            cv2.waitKey(int(milliseconds_per_sec / display_frame_rate / speed))

    def save_images(self):
        print('saving images ...')

        print(os.path.join('jpg', self.info['ImageName'], '{}.jpg'.format(0)))

        image_file = os.path.join(os.path.join('jpg', self.info['ImageName']))
        if not os.path.exists(image_file):
            os.makedirs(image_file)

        for f, img in enumerate(self.images):
            cv2.imwrite(os.path.join(
                image_file, 
                '{}.jpg'.format(f)
            ), img)
        
        print('saving images done.')
