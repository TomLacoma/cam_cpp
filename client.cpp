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
			  << " [ adresse IP/nom du serveur 1 ] ..." << std::endl;
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
	snprint(tmp, sizeof(tmp), "%s", acstime(T));

    	ssize_t size = sizeof(tmp);
	if (size != write(s, tmp, size)) {
		std::cout << "pb" << std::endl;
	}

//Envoie de l'image

	ssize_t size_Image;
	ssize_t size_taille;
	double taille;

	struct stat properties;
	if (0 == stat("test.jpg", &properties)) {
		char * Image = new char [properties.st_size];
		taille = properties.st_size;
		FILE * fp = fopen("test.jpg", "r");
		fread(Image, 1, properties.st_size, fp);
		fclose(fp);
	}

	size_taille = write(s, taille, sizeof(double));
	size_Image = write(s, Image, properties.st_size*sizeof(char));







	close(s);
	return 0;
}
