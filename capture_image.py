#!/usr/local/anaconda3/bin/python3

import cv2
import os

cam = cv2.VideoCapture(0)
ret, img = cam.read()
cv2.imwrite('test.jpg', img)
cam.release()

os.system(f"./client {server} {nom_image}")
