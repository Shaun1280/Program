import pydicom
import cv2
import numpy as np

#调整图像窗宽窗位
def window_transform(ct_array, window_width, window_center, normal=False):
    min_window = float(window_center) - 0.5*float(window_width)
    new_img = (ct_array - min_window) / float(window_width)
    new_img[new_img < 0] = 0
    new_img[new_img > 1] = 1
    if not normal:
        new_img = (new_img * 255).astype('uint8')
    return new_img

class Dicom:
    def load_dicom(self, dicom_path):
        '''
        dicom 读取，保存在内存中
        '''
        self.__info = {}
        self.images = None
        ds = pydicom.read_file(dicom_path)

        self.__info['PatientID'] = ds.PatientID               # 患者ID
        self.__info['PatientName'] = ds.PatientName           # 患者姓名
        self.__info['PatientBirthDate'] = ds.PatientBirthDate  # 患者出生日期
        self.__info['PatientAge'] = ds.PatientAge             # 患者年龄
        self.__info['PatientSex'] = ds.PatientSex             # 患者性别
        self.__info['PatientWeight'] = ds.PatientWeight       # 患者体重
        self.__info['StudyID'] = ds.StudyID                   # 检查ID
        self.__info['StudyDate'] = ds.StudyDate               # 检查日期
        self.__info['StudyTime'] = ds.StudyTime               # 检查时间
        self.__info['StudyModality'] = ds.Modality
        self.__info['InstitutionName'] = ds.InstitutionName   # 机构名称
        self.__info['Manufacturer'] = ds.Manufacturer         # 设备制造商
        self.__info['StudyDescription'] = ds.StudyDescription  # 检查项目描述
        self.__info['SeriesNumber'] = ds.SeriesNumber         # 序列号
        self.__info['RecommendedDisplayFrameRate'] = ds.RecommendedDisplayFrameRate
        self.__info['SOPInstanceUID'] = ds.SOPInstanceUID # 获取图像唯一标识
        # self.__info['WindowWidth'] = ds.WindowWidth
        # self.__info['WindowCenter'] = ds.WindowCenter
        self.__images = np.array(ds.pixel_array)
        #print(ds.WindowWidth, ds.WindowCenter)
        for f, img in enumerate(self.__images):
            self.__images[f] = window_transform(img, ds.WindowWidth, ds.WindowCenter)

    def get_dicom(self):
        return self.__info, self.__images

if __name__ == '__main__':
    dicom = Dicom()
    dicom.load_dicom('data/607D1E32BD694C338FBF5E9F724329CA.dic')
    dicom.show_images()
