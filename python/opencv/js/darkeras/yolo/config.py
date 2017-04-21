# Global config variables
import os

model_name = 'yolo-tiny'
classes_name = ["aeroplane", "bicycle", "bird", "boat", "bottle", "bus", "car", "cat", "chair", "cow", "diningtable", "dog", "horse", "motorbike", "person", "pottedplant", "sheep", "sofa", "train","tvmonitor"]

dataset_abs_location = os.path.join('C:\\\\','Users','SoMa','myworkspace','voc_dataset','VOCdevkit', 'VOC2007')
ann_location = os.path.join(dataset_abs_location, 'Annotations')
imageset_location = os.path.join(dataset_abs_location, 'JPEGImages')

cell_size = 7
num_classes = 20
boxes_per_cell = 2

class_scale = 1
object_scale = 1
noobject_scale = 0.5
coord_scale = 5

inp_size = 448, 448, 3
batch_size = 32
epochs=100

