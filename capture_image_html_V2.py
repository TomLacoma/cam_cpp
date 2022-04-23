#!/usr/local/anaconda3/bin/python3

import cv2
import os
import sys
from datetime import datetime
import time

cam = cv2.VideoCapture(0)
server = "localhost" #Switch with server ip


while(True):

    ret, img = cam.read()
    cv2.imwrite('test.jpg', img)
    os.system(f"./client {server} test.jpg")
    #date=str(datetime.now())
    #cam.release()

    #html_file = open('client1.html', 'w+')
    # Boucle qui écrit de nouveau entièrement html, pas très propre mais fonctionne
    #for line in template:
    #    html_file.write(line)
    #    if string1 in line:
        #    html_file.write('\n   '+date)
    #template.seek(0)
    #html_file.close()

    time.sleep(5)
cam.release()
