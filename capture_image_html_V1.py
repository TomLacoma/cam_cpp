#!/usr/local/anaconda3/bin/python3

import cv2
import os
import sys
from datetime import datetime
import time

n=1

template = open('client1.tmpl', 'r')
html_file = open('client1_V2.html', 'w+')



for line in template:
        html_file.write(line)

# Boucle infinie pour rafraichir la page html
while(n!=0):

    cam = cv2.VideoCapture(0)
    date=str(datetime.now())
    ret, img = cam.read()
    cv2.imwrite('client1_V2.jpg', img)

    print(date)
    cam.release()
    time.sleep(5)

#os.system(f"./client {server} {nom_image}")
