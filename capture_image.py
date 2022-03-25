#!/usr/local/anaconda3/bin/python3

import cv2
import time
import os

now = str(time.time()).split(".")[0]

print(now)

cam = cv2.VideoCapture(0)
ret, img = cam.read()
cv2.imwrite(f"{now}.jpg", img)
cam.release()


#os.system(f"./client {server} {path_to_img}")
