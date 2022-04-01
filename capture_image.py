#!/usr/local/anaconda3/bin/python3

import cv2
import time
import os

cam = cv2.VideoCapture(0)
ret, img = cam.read()
cv2.imwrite("client.jpg", img)
cam.release()


os.system("./client localhost client.jpg")
