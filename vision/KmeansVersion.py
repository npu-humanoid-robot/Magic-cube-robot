import cv2
import numpy as np
import glob
from sklearn.cluster import KMeans
import configparser

from Pretreat import *

class Img2Status:
    def __init__(self, scalars):
        self.scalars = scalars 
        # for i in self.scalars:
        #     i = (i[1], i[2])
        self.Cluster()
        return 
    def Cluster(self):
        init_center = np.ndarray((6, 3))
        for i in range(6):
            init_center[i] = self.scalars[6*i+4]
        kmeans_cluster = KMeans(n_clusters=6, init=init_center)
        kmeans_cluster.fit(self.scalars)
        self.labels = kmeans_cluster.labels_
        return
    def ToStatus(self):
        label2str = {}
        faces = ['U', 'R', 'F', 'D', 'L', 'B']
        for i in range(6):
            label2str[self.labels[i*9+4]] = faces[i]
            print(self.labels[i*9+4], faces[i])

        status = [label2str[i] for i in self.labels]
        self.status = "".join(status)

if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")
    
    pi_pic_root_path  = "../BackupSource/"
    pic_path = "../BackupSource/*.jpg"
    #pic_paths = [i for i in glob.glob(pic_path)]
    pic_paths = [pi_pic_root_path+"%d.jpg"%i for i in range(4)]
    pics = []
    for i in pic_paths:
        img = cv2.imread(i)
        print(i)

        pics.append(img)

        cv2.imshow("233", img)
        cv2.waitKey(0)
    pp = Pretreat(pics, config)
    result = pp.GetResult()
    for i in pp.perspectived_imgs:
        cv2.imshow("233", i)
        cv2.waitKey()

    ya = Img2Status(result)
    ya.Cluster()
    labels = ya.labels
    for i in range(6):
        for j in range(9):
            print(labels[i*9+j], end=" ")
        print()
    ya.ToStatus()
    print(ya.status)
