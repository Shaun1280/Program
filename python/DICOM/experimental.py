import cv2
import numpy as np
import os
import json
from numba import jit
import matplotlib.pyplot as plt

def calculate_iou(box1, box2):
    """
    Calculate Intersection over Union (IoU) of two bounding boxes.

    Arguments:
    box1 -- tuple of (x1, y1, x2, y2) coordinates of the first box
    box2 -- tuple of (x1, y1, x2, y2) coordinates of the second box

    Returns:
    iou -- Intersection over Union (IoU) of box1 and box2
    """
    # Calculate the coordinates of the intersection rectangle
    x_left = max(box1[0], box2[0])
    y_top = max(box1[1], box2[1])
    x_right = min(box1[2], box2[2])
    y_bottom = min(box1[3], box2[3])

    # If the boxes don't overlap, return 0
    if x_right < x_left or y_bottom < y_top:
        return 0.0

    # Calculate the area of intersection rectangle
    intersection_area = (x_right - x_left) * (y_bottom - y_top)

    # Calculate the area of both boxes
    box1_area = (box1[2] - box1[0]) * (box1[3] - box1[1])
    box2_area = (box2[2] - box2[0]) * (box2[3] - box2[1])

    # Calculate the intersection over union
    iou = intersection_area / float(box1_area + box2_area - intersection_area)

    return iou

@jit
def calculate_precision_pbc_recall_aor(pred, gt, label):
    true_positives = 0
    false_positives = 0
    false_negatives = 0
    bad_classifications = 0
    
    for i in range(480):
        for j in range(480):
            if pred[i, j] == label and gt[i, j] == label:
                true_positives += 1
            elif pred[i, j] == label and gt[i, j] != label:
                false_positives += 1
                bad_classifications += 1
            elif pred[i, j] != label and gt[i, j] == label:
                false_negatives += 1
                bad_classifications += 1

    if true_positives + false_positives == 0:
        precision = 1
    else:
        precision = true_positives / (true_positives + false_positives)
    
    if true_positives + false_negatives == 0:
        recall = 1
    else:
        recall = true_positives / (true_positives + false_negatives)
    
    percentage_bad = bad_classifications / (480 * 480) * 100

    idx1 = (pred == label)
    idx2 = (gt == label)
    overlap = idx1 & idx2
    total = idx1 | idx2
    overlap_rate = (np.sum(overlap) + 1e-6) / (np.sum(total) + 1e-6)

    return precision, percentage_bad, recall, overlap_rate

def calculate_precision_pbc_recall2(markers, jsons, roi, label):
    true_positives = 0
    false_positives = 0
    false_negatives = 0
    bad_classifications = 0

    for i in range(markers.shape[0]):
        img1 = np.zeros((480, 480), np.uint8)
        gt = np.zeros((480, 480), np.uint8) # Ground Truth

        marker, json = markers[i], jsons[i]

        roi = [int(round(x) + 1e-6) for x in roi]
        img1[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]] = marker

        shapes = json['shapes']
        for shape in shapes:
            if shape['shape_type'] == 'polygon':
                _, pts = shape['label'], shape['points']
                pts = np.array(pts, np.int32)
                gt = cv2.fillPoly(gt, [pts], int(_))

        sum1 = np.sum(np.equal(img1, label), axis=None)
        sum2 = np.sum(np.equal(gt, label), axis=None)

        sum1 = (sum1 > 0)
        sum2 = (sum2 > 0)

        if sum1 and sum2:
            true_positives += 1
        elif sum1 and not sum2:
            false_positives += 1
            bad_classifications += 1
        elif not sum1 and sum2:
            false_negatives += 1
            bad_classifications += 1
    
    print(true_positives, false_positives)

    if true_positives + false_positives == 0:
        precision = 1
    else:
        precision = true_positives / (true_positives + false_positives)
    
    if true_positives + false_negatives == 0:
        recall = 1
    else:
        recall = true_positives / (true_positives + false_negatives)

    percentage_bad = bad_classifications / markers.shape[0] * 100

    return precision, percentage_bad, recall

def read_boxes(boxes_dir):
    res = []
    f = open(boxes_dir, 'r')
    while (True):
        line = f.readline()
        if not line:
            break
        box = np.array(list(map(float, (line.split('\n')[0]).split(','))))
        res.append(box)
    f.close()
    return np.array(res)

def read_saved_data(path):
    files = os.listdir(path)
    boxes = None
    markers = None
    roi = None
    for f in files:
        f_lower = f.lower()
        if f_lower.endswith('.boxes'):
            boxes = read_boxes(os.path.join(path, f))

        elif f_lower.endswith('.npy'):
            markers = np.load(os.path.join(path, f))

        elif f_lower.endswith('roi'):
            roi = read_boxes(os.path.join(path, f))
            roi = roi[0]

    return boxes, markers, roi

def metrics_boxes(boxes, jsons):
    success_rates = []
    _iou = [0] * boxes.shape[0]
    average_overlap_rate = 0

    for i in range(boxes.shape[0]):
        box, json = boxes[i], jsons[i]

        box1 = (box[0], box[1], box[0] + box[2], box[1] + box[3])

        shapes = json['shapes']
        for shape in shapes:
            if shape['shape_type'] == 'rectangle':
                box2 = shape['points']
                box2 = (box2[0][0], box2[0][1], box2[1][0], box2[1][1])
                _iou[i] = calculate_iou(box1, box2)
        
        average_overlap_rate += _iou[i] / boxes.shape[0]

    for iou in range(50, 100, 5):
        iou /= 100

        success_rate = 0

        for i in range(boxes.shape[0]):
            # print(box1, box2, _iou)
            if _iou[i] > iou - 1e-6:
                success_rate += 1.0 / boxes.shape[0]

        success_rates.append(success_rate)

    return success_rates, average_overlap_rate

def metrics_markers(markers, jsons, roi):
    # marker1 marker2 hold sideleakage
    precision = [0, 0, 0, 0]
    percentage_bad = [0, 0, 0, 0]
    recall = [0, 0, 0, 0]
    aor = [0, 0]

    for i in range(markers.shape[0]):
        img1 = np.zeros((480, 480), np.uint8)
        gt = np.zeros((480, 480), np.uint8) # Ground Truth

        marker, json = markers[i], jsons[i]

        roi = [int(round(x) + 1e-6) for x in roi]
        img1[roi[1]:roi[1] + roi[3], roi[0]:roi[0] + roi[2]] = marker

        shapes = json['shapes']
        for shape in shapes:
            if shape['shape_type'] == 'polygon':
                label, pts = shape['label'], shape['points']
                pts = np.array(pts, np.int32)
                gt = cv2.fillPoly(gt, [pts], int(label))

        # marker1
        precision1, percentage_bad1, recall1, overlap_rate = calculate_precision_pbc_recall_aor(img1, gt, 1)
        precision[0] += precision1 / markers.shape[0]
        percentage_bad[0] += percentage_bad1 / markers.shape[0]
        recall[0] += recall1 / markers.shape[0]
        aor[0] += overlap_rate / markers.shape[0]

        # marker2
        precision2, percentage_bad2, recall2, overlap_rate = calculate_precision_pbc_recall_aor(img1, gt, 2)
        precision[1] += precision2 / markers.shape[0]
        percentage_bad[1] += percentage_bad2 / markers.shape[0]
        recall[1] += recall2 / markers.shape[0]
        aor[1] += overlap_rate / markers.shape[0]

        # cv2.imshow('Polygon1', img1)
        # cv2.imshow('Polygon2', img2)
        # if cv2.waitKey(30) == ord('q'):
        #     break

    # hold
    precision[2], percentage_bad[2], recall[2] = calculate_precision_pbc_recall2(markers, jsons, roi, 1)
    # sideleakage
    precision[3], percentage_bad[3], recall[3] = calculate_precision_pbc_recall2(markers, jsons, roi, 2)

    return precision, percentage_bad, recall, aor

def save_result(path, dir, start, end,
                success_rates, mean_success_rate, precision,
                percentage_bad, recall, aor_boxes, aor_markers):

    # Define the filename and the file mode ('w' for write)
    filename = os.path.join(path, 'result-{}-{}-{}.txt'.format(dir, start, end))
    file_mode = 'w'

    # Open the file in the specified mode
    with open(filename, file_mode) as file:

        # Write the success_rates array to the file
        file.write('success_rates: ')
        for rate in success_rates:
            file.write(f'{rate:.3f} ')
        file.write('\n')

        # Write the mean_success_rate to the file
        file.write('mean_success_rate: ')
        file.write(f'{mean_success_rate:.3f}\n')

        # Write the average overlap rate to the file
        file.write('aor: ')
        file.write(f'{aor_boxes:.3f}\n')

        # Write the precision array to the file
        file.write('precision(marker1, marker2, hold, sideleakage): ')
        for p in precision:
            file.write(f'{p:.3f} ')
        file.write('\n')

        # Write the percentage_bad array to the file
        file.write('pbc(marker1, marker2, hold, sideleakage): ')
        for p in percentage_bad:
            file.write(f'{p:.3f} ')
        file.write('\n')

        # Write the recall array to the file
        file.write('recall(marker1, marker2, hold, sideleakage): ')
        for p in recall:
            file.write(f'{p:.3f} ')
        file.write('\n')

        # Write the recall array to the file
        file.write('aor(marker1, marker2): ')
        for p in aor_markers:
            file.write(f'{p:.3f} ')
        file.write('\n')

    x_axis = np.arange(0.50, 1.00, 0.05)

    # Plot the success_rates array
    plt.clf()

    plt.plot(x_axis, success_rates)

    # Set y-axis limits to 0.0 and 1.0
    plt.ylim(0.0, 1.0)

    # Add chart title and axis labels
    plt.title('Success Rates')
    plt.xlabel('IoU')
    plt.ylabel('Success Rate')

    # Save the chart as a JPG file
    plt_save_path = os.path.join(path, 'success_rates_chart-{}.jpg'.format(dir))
    # plt.savefig(plt_save_path)

    # Display the chart
    # plt.show()

def metrics(path, sample_len=60):
    print('Metrics {} ......'.format(path))
    files = os.listdir(path)
    files = [x for x in files if x.lower().endswith('.json')]
    files = sorted(files, key=lambda x: int(x.split('.')[0]))

    for f in os.listdir(path):
        if f.lower().endswith('.txt'):
            os.remove(os.path.join(path, f))
            # print('{} removed'.format(os.path.join(path, f)))

    jsons = []
    for f in files:
        if f.lower().endswith('.json'):
            with open(os.path.join(path, f), 'r') as json_file:
                str = json_file.read()
                anno = json.loads(str)
                jsons.append(anno)

    dirs = ['eco', 'yolo']
    # dirs = ['eco']

    starts = []
    ends = []
    start, end = 0, -1
    while True:
        start = end + 1 + np.random.randint(0, sample_len / 2)
        end = start + sample_len - 1

        if start >= len(jsons) or end >= len(jsons):
            break

        starts.append(start)
        ends.append(end)

    for dir in dirs:
        print('checking {} ...'.format(dir))
        boxes, markers, roi = read_saved_data(os.path.join(path, dir))

        assert not boxes is None
        assert not markers is None
        assert not roi is None

        if boxes.shape[0] != markers.shape[0]:
            print('Failed because of nBoxes != nMarkers', boxes.shape[0], markers.shape[0], '\n')
            return

        if boxes.shape[0] != len(jsons):
            print('Failed because of nBoxes != nJson', boxes.shape[0], len(jsons), '\n')
            return
            
        for i in range(len(starts)):
            start = starts[i]
            end = ends[i]

            boxes_sample = boxes[start:end + 1]
            markers_sample = markers[start:end + 1]
            jsons_sample = jsons[start:end + 1]

            print('checking [{}, {}]'.format(start, end))
        
            success_rates, average_overlap_rate = metrics_boxes(boxes_sample, jsons_sample)
            print('success rates: ', np.array(success_rates))
            print('mean success rates: {:.3f}'.format(sum(success_rates) / len(success_rates)))
            print('AOR: {:.3f}'.format(average_overlap_rate))

            precision, percentage_bad, recall, aor = metrics_markers(markers_sample, jsons_sample, roi)
            print('precision(marker1, marker2, hold, sideleakage): ', np.array(precision))
            print('pbc(marker1, marker2, hold, sideleakage): ', np.array(percentage_bad))
            print('recall(marker1, marker2, hold, sideleakage): ', np.array(recall))
            print('aor(marker1, marker2)', np.array(aor))

            save_result(path, dir, start, end,
                        np.array(success_rates),
                        sum(success_rates) / len(success_rates),
                        np.array(precision),
                        np.array(percentage_bad),
                        np.array(recall),
                        average_overlap_rate,
                        np.array(aor))

            print('\n')

    print('Done.', '\n')

def traverse_data(path):
    files = os.listdir(path)
    for f in files:
        if f == 'experimental':
            metrics(os.path.join(path, f), sample_len=20)
        elif f.lower().endswith('.dic') or f.lower().endswith('.jpg'):
            pass
        elif f.lower().endswith('.boxes') or f.lower().endswith('.npy') or f.lower().endswith('.roi'):
            pass
        else:
            traverse_data(os.path.join(path, f))
        # break

if __name__ == '__main__':
    np.set_printoptions(precision=3, suppress=True, floatmode='fixed')
    traverse_data('.\\data')