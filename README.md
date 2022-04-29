# cam_cpp
Projet d'informatique : surveillance par webcam interposée.
Un ou plusieurs clients font tourner un programme qui prend des photos périodiques. Ces photos sont envoyées à un serveur;
Le serveur groupe les images et les affiche sur une page html rafraichie périodiquement.
Par défaut les échanges s'effectuent sur le port 25000, ce paramètre est échangeable dans le fichier base.h qui définit le port d'usage.

Prérequis:
Clients : python + module cv2 (pip install opencv-python)
Serveur : port 25000 ouvert

Installation :

Clients :
Cloner le dépot github sur la machine cliente, recompiler les fichiers client et server.
Lancer capture_send.py (help : python3 capture_send.py -h)

Serveur :
Cloner le dépot github sur la machine serveur, recompiler server.cpp.
Lancer server



Missing/ongoing :
Log des envois des clients dans un fichier unique pour la session
Séparation des fichiers des clients en dossiers
Détection des clients déconnectés pour spécifier l'info sur global.html après un certain timeout entre deux images
