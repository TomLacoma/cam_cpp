#!/usr/local/anaconda3/bin/python3

import cv2
import os
import sys
from datetime import datetime
import time

#n =0 pour éviter la boucle infinie, !=0 rentre dans la boucle
n=1

#template = open('client1.tmpl', 'r') #template du html
#html_file = open('client1.html', 'w+') #html écrit à partir du template
cam = cv2.VideoCapture(0)

#string1 = '<!--  Date et heure: -->' #String pour cibler où écrire la date dans le html

# Boucle infinie pour rafraichir la page html

ret, img = cam.read()
cv2.imwrite('test.jpg', img)
#os.system(f"./client {server} {nom_image}")

while(n!=0):

    ret, img = cam.read()
    cv2.imwrite('test.jpg', img)
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
