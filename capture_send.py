#!/usr/local/anaconda3/bin/python3
import cv2
import os
import sys
import argparse

##Parser declaration for arguments
parser = argparse.ArgumentParser(description='Captures and sends a webcam picture to a server with specific delay.')

parser.add_argument('server', metavar='ip', default='localhost', help='ip adress of the destination server for pictures (default is localhost)')
parser.add_argument('--cam', '-c', metavar="cam_id", type=int, default=0, help='id of the camera used to take pictures, default is 0 (system default camera)')
parser.add_argument('--delay', '-d', metavar="delay", type=int, default=5, help="delay between two pictures in seconds, default is 5s")

args = parser.parse_args()

print(args)

#Definition of capture peripheral (default is 0)
cam = cv2.VideoCapture(args.cam)

while(True):
    ret, img = cam.read()
    cv2.imwrite('test.jpg', img)
    os.system(f"./client {args.server} test.jpg")

    time.sleep(args.delay)
cam.release()
