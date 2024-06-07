import os
import cv2
import numpy as np
import random

data = []

def dataset_gen(dir):
    global data
    # print(dir)

    files = os.listdir(dir)
    for f in files:
        if f.lower().endswith(('.jpg')):
            img = cv2.imread(os.path.join(dir, f))
            # print(img.shape)
            data.append(img)

            if len(data) % 500 == 0:
                print("reading images, total number = {}".format(len(data)))
        else:
            dataset_gen(os.path.join(dir, f))

dataset_gen('./jpg')
print("reading images, total number = {}".format(len(data)))

random.shuffle(data)
train_size = int(0.7 * len(data))

# train_dataset
for i in range(train_size):
    image_file = 'dataset/images/train'

    if not os.path.exists(image_file):
            os.makedirs(image_file)

    cv2.imwrite(os.path.join(
            image_file, 
            '{}.jpg'.format(str(i).zfill(5))
    ), data[i])

    if i % 500 == 0:
        print("saving train images, num = {}".format(i))

# val_dataset
for i in range(train_size, len(data)):
    image_file = 'dataset/images/val'

    if not os.path.exists(image_file):
            os.makedirs(image_file)

    cv2.imwrite(os.path.join(
            image_file, 
            '{}.jpg'.format(str(i - train_size).zfill(5))
    ), data[i])

    if (i - train_size) % 500 == 0:
        print("saving val images, num = {}".format(i - train_size))
