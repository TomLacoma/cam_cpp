# cam_cpp
Projet d'informatique : surveillance par webcam interposée. Les images sont transmises et visualisables sur une page HTML.

Setting up:
Les machines "clients" sont celles qui effectuent la surveillance. Le programme à lancer est capture_image_html_V2.py qui prend une image toutes les 5 secondes, et appelle le programme client.

Programme client :
Envoi de l'image et date de prise d'image au serveur. Syntaxe : ./client [ip du serveur] [nom de l'image à envoyer]

Serveur :
Ecoute les clients sur le port 25000. A la connexion d'un client, réceptionne l'image et les données nécessaires, puis rafraichit la page html correspondante avec la dernière image.
