import numpy as np
import pickle
import os
import cv2

from ..config import gpu_config
from . import _gradient
from ..config import otb_hc_config,otb_deep_config

def mround(x):
    x_ = x.copy()
    idx = (x - np.floor(x)) >= 0.5
    x_[idx] = np.floor(x[idx]) + 1
    idx = ~idx
    x_[idx] = np.floor(x[idx])
    return x_

class Feature:
    def __init__(self,config=otb_hc_config.OTBHCConfig()):
        self.config=config

    def init_size(self, img_sample_sz, cell_size=None):
        if cell_size is not None:
            max_cell_size = max(cell_size)
            new_img_sample_sz = (1 + 2 * mround(img_sample_sz / ( 2 * max_cell_size))) * max_cell_size
            feature_sz_choices = np.array([(new_img_sample_sz.reshape(-1, 1) + np.arange(0, max_cell_size).reshape(1, -1)) // x for x in cell_size])
            num_odd_dimensions = np.sum((feature_sz_choices % 2) == 1, axis=(0,1))
            best_choice = np.argmax(num_odd_dimensions.flatten())
            img_sample_sz = mround(new_img_sample_sz + best_choice)

        self.sample_sz = img_sample_sz
        self.data_sz = [img_sample_sz // self._cell_size]
        return img_sample_sz

    def _sample_patch(self, im, pos, sample_sz, output_sz):
        pos = np.floor(pos)
        sample_sz = np.maximum(mround(sample_sz), 1)
        xs = np.floor(pos[1]) + np.arange(0, sample_sz[1]+1) - np.floor((sample_sz[1]+1)/2)
        ys = np.floor(pos[0]) + np.arange(0, sample_sz[0]+1) - np.floor((sample_sz[0]+1)/2)
        xmin = max(0, int(xs.min()))
        xmax = min(im.shape[1], int(xs.max()))
        ymin = max(0, int(ys.min()))
        ymax = min(im.shape[0], int(ys.max()))
        # extract image
        im_patch = im[ymin:ymax, xmin:xmax, :]
        left = right = top = down = 0
        if xs.min() < 0:
            left = int(abs(xs.min()))
        if xs.max() > im.shape[1]:
            right = int(xs.max() - im.shape[1])
        if ys.min() < 0:
            top = int(abs(ys.min()))
        if ys.max() > im.shape[0]:
            down = int(ys.max() - im.shape[0])
        if left != 0 or right != 0 or top != 0 or down != 0:
            im_patch = cv2.copyMakeBorder(im_patch, top, down, left, right, cv2.BORDER_REPLICATE)
        # im_patch = cv2.resize(im_patch, (int(output_sz[0]), int(output_sz[1])))
        im_patch = cv2.resize(im_patch, (int(output_sz[1]), int(output_sz[0])), cv2.INTER_CUBIC)
        if len(im_patch.shape) == 2:
            im_patch = im_patch[:, :, np.newaxis]
        return im_patch

    def _feature_normalization(self, x):
        if hasattr(self.config, 'normalize_power') and self.config.normalize_power > 0:
            if self.config.normalize_power == 2:
                x = x * np.sqrt((x.shape[0]*x.shape[1]) ** self.config.normalize_size * (x.shape[2] ** self.config.normalize_dim) / (x ** 2).sum(axis=(0, 1, 2)))
            else:
                x = x * ((x.shape[0]*x.shape[1]) ** self.config.normalize_size) * (x.shape[2] ** self.config.normalize_dim) / ((np.abs(x) ** (1. / self.config.normalize_power)).sum(axis=(0, 1, 2)))

        if self.config.square_root_normalization:
            x = np.sign(x) * np.sqrt(np.abs(x))
        return x.astype(np.float32)

def fhog(I, bin_size=8, num_orients=9, clip=0.2, crop=False):
    soft_bin = -1
    M, O = _gradient.gradMag(I.astype(np.float32), 0, True)
    H = _gradient.fhog(M, O, bin_size, num_orients, soft_bin, clip)
    return H

class GrayFeature(Feature):
    def __init__(self, fname, cell_size=1, config=otb_hc_config.OTBHCConfig()):
        super(GrayFeature,self).__init__(config)
        self.fname = fname
        self._cell_size = cell_size
        self.min_cell_size = self._cell_size
        self._compressed_dim = [1]
        self.num_dim = [1]

    def get_features(self, img, pos, sample_sz, scales,normalization=True):
        feat = []
        if not isinstance(scales, list) and not isinstance(scales, np.ndarray):
            scales = [scales]
        for scale in scales:
            patch = self._sample_patch(img, pos, sample_sz*scale, sample_sz)
            # h, w, c = patch.shape
            if patch.shape[2]==3:
                gray=cv2.cvtColor(patch,cv2.COLOR_RGB2GRAY)[:,:,np.newaxis]
            else:
                gray=patch
            if self._cell_size > 1:
                gray = self.average_feature_region(gray.astype(np.uint8), self._cell_size)
            feat.append(gray/255-0.5)
        feat=np.stack(feat,axis=3)
        if normalization is True:
            feat = self._feature_normalization(feat)
        return [feat]

    def integralVecImage(self, img):
        w, h, c = img.shape
        intImage = np.zeros((w+1, h+1, c), dtype=img.dtype)
        intImage[1:, 1:, :] = np.cumsum(np.cumsum(img, 0), 1)
        return intImage

    def average_feature_region(self, features, region_size):
        region_area = region_size ** 2
        if features.dtype == np.float32:
            maxval = 1.
        else:
            maxval = 255
        intImage = self.integralVecImage(features)
        i1 = np.arange(region_size, features.shape[0]+1, region_size).reshape(-1, 1)
        i2 = np.arange(region_size, features.shape[1]+1, region_size).reshape(1, -1)
        region_image = (intImage[i1, i2, :] - intImage[i1, i2-region_size,:] - intImage[i1-region_size, i2, :] + intImage[i1-region_size, i2-region_size, :])  / (region_area * maxval)
        return region_image


class FHogFeature(Feature):
    def __init__(self, fname, cell_size=6, compressed_dim=10, num_orients=9, clip=.2,config=otb_hc_config.OTBHCConfig()):
        super(FHogFeature,self).__init__(config)
        self.fname = fname
        self._cell_size = cell_size
        self._compressed_dim = [compressed_dim]
        self._soft_bin = -1
        self._bin_size = cell_size
        self._num_orients = num_orients
        self._clip = clip

        self.min_cell_size = self._cell_size
        self.num_dim = [3 * num_orients + 5 - 1]
        self.penalty = [0.]


    def get_features(self, img, pos, sample_sz, scales,normalization=True):
        feat = []
        if not isinstance(scales, list) and not isinstance(scales, np.ndarray):
            scales = [scales]
        for scale in scales:
            patch = self._sample_patch(img, pos, sample_sz*scale, sample_sz)
            # h, w, c = patch.shape
            M, O = _gradient.gradMag(patch.astype(np.float32), 0, True)
            H = _gradient.fhog(M, O, self._bin_size, self._num_orients, self._soft_bin, self._clip)
            # drop the last dimension
            H = H[:, :, :-1]
            feat.append(H)
        feat=np.stack(feat,axis=3)
        if normalization is True:
            feat = self._feature_normalization(feat)
        return [feat]

class TableFeature(Feature):
    def __init__(self, fname, compressed_dim, table_name, use_for_color, cell_size=1,config=otb_hc_config.OTBHCConfig()):
        super(TableFeature,self).__init__(config)
        self.fname = fname
        self._table_name = table_name
        self._color = use_for_color
        self._cell_size = cell_size
        self._compressed_dim = [compressed_dim]
        self._factor = 32
        self._den = 8
        # load table
        dir_path = os.path.dirname(os.path.realpath(__file__))
        self._table = pickle.load(open(os.path.join(dir_path, "lookup_tables", self._table_name+".pkl"), "rb"))

        self.num_dim = [self._table.shape[1]]
        self.min_cell_size = self._cell_size
        self.penalty = [0.]
        self.sample_sz = None
        self.data_sz = None


    def integralVecImage(self, img):
        w, h, c = img.shape
        intImage = np.zeros((w+1, h+1, c), dtype=img.dtype)
        intImage[1:, 1:, :] = np.cumsum(np.cumsum(img, 0), 1)
        return intImage

    def average_feature_region(self, features, region_size):
        region_area = region_size ** 2
        if features.dtype == np.float32:
            maxval = 1.
        else:
            maxval = 255
        intImage = self.integralVecImage(features)
        i1 = np.arange(region_size, features.shape[0]+1, region_size).reshape(-1, 1)
        i2 = np.arange(region_size, features.shape[1]+1, region_size).reshape(1, -1)
        region_image = (intImage[i1, i2, :] - intImage[i1, i2-region_size,:] - intImage[i1-region_size, i2, :] + intImage[i1-region_size, i2-region_size, :])  / (region_area * maxval)
        return region_image

    def get_features(self, img, pos, sample_sz, scales,normalization=True):
        feat = []
        if not isinstance(scales, list) and not isinstance(scales, np.ndarray):
            scales = [scales]
        for scale in scales:
            patch = self._sample_patch(img, pos, sample_sz*scale, sample_sz)
            h, w, c = patch.shape
            if c == 3:
                RR = patch[:, :, 0].astype(np.int32)
                GG = patch[:, :, 1].astype(np.int32)
                BB = patch[:, :, 2].astype(np.int32)
                index = RR // self._den + (GG // self._den) * self._factor + (BB // self._den) * self._factor * self._factor
                features = self._table[index.flatten()].reshape((h, w, self._table.shape[1]))
            else:
                features = self._table[patch.flatten()].reshape((h, w, self._table.shape[1]))
            if self._cell_size > 1:
                features = self.average_feature_region(features, self._cell_size)
            feat.append(features)
        feat=np.stack(feat, axis=3)
        if normalization is True:
            feat = self._feature_normalization(feat)
        return [feat]

