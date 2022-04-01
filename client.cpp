#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "base.h"
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono;


//Fonction permettant de créer un socket
int
create_socket (const char * server_name)

{
    struct sockaddr_in saddr;
    struct hostent * server;
    int ret;
        int s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
                std::cerr << "cannot create socket" << std::endl;
                return 0;
        }

        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(DEFAULT_PORT);
        server = gethostbyname(server_name);
        if (server == NULL) {
                std::cerr << "gethostbyname() failed" << std::endl;
				close(s);
                return 0;
        }
        else {
                memcpy(&saddr.sin_addr, server->h_addr, 4);
        }

        ret = connect(s, (struct sockaddr *)&saddr, sizeof(saddr));
        if (ret < 0) {
                std::cerr << "cannot connect to remote server" << std::endl;
                close(s);
                return 0;
        }

        return s;
}


int main (int argc, char * argv[])

{
//Creation d'un socket, etc...
	if (argc == 1) {
		std::cerr << "usage: " << argv[0]
			  << " [ adresse IP/nom du serveur 1 ] [ nom du fichier ]" << std::endl;
		return 0;
	}

	int s;
	s = create_socket(argv[1]);
    if (s <= 0) {
        std::cerr << "cannot create socket" << std::endl;
        return 0;
    }


// Creation et envoie de la variable tmp permettant de stocker heure & date
	char tmp[100];
	time_t t;
	struct tm * T;
	time(&t);
	T=localtime(&t);
	snprintf(tmp, sizeof(tmp), "%s", asctime(T));

    	ssize_t size = sizeof(tmp);
	if (size != write(s, tmp, size)) {
		std::cout << "pb" << std::endl;
	}
  //cout << "envoi date/heure " << size << endl;

//Envoie de l'image      argv[2] correspond au nom de l'image à envoyer

	ssize_t size_Image;
	ssize_t size_taille;
  char * Image = NULL;

	struct stat properties;
  //cout  << sizeof(properties.st_size) << " " << sizeof(unsigned long) <<  endl;
	if (0 == stat(argv[2], &properties)) {
		Image = new char[properties.st_size];
		FILE * fp = fopen(argv[2], "r");
		int rez = fread(Image, 1, properties.st_size, fp);
    if(rez!=properties.st_size){std::cout << "Problème" << '\n';}
		fclose(fp);
	}

  if (Image != NULL) {
/*
    FILE * fp = fopen("client.log", "w"); //debug
    for (unsigned i = 0; i < properties.st_size; i++) fprintf(fp, "%d ", Image[i]);
    fprintf(fp, "\n");
    fclose(fp);
*/
    size_taille = write(s, &properties.st_size, sizeof(properties.st_size));
    if(size_taille!=sizeof(properties.st_size)){std::cout << "Problème" << '\n';}

    long unsigned int remain = properties.st_size;
    size_t img_offset = 0;
    while (remain > 0) {
      size_Image = write(s, Image + img_offset, remain);
      //cout << "ret " << size_Image << " remain " << remain << endl;
      remain -= size_Image;
      img_offset += size_Image;
    }



  	//size_Image = write(s, Image, properties.st_size);
    delete [] Image;
  }
//  std::cout << size_Image << endl << "<-image" << size_taille << '\n';



	close(s);
	return 0;
}
