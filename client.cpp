#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "base.h"
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <math.h>

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
	time(&t)
	T=localtime(&t);
	snprint(tmp, sizeof(tmp), "%s", acstime(T));

    write(s, tmp, 1 + strlen(tmp));
	
//Envoie de l'image
	
	char* Image[9999999];
	sprintf(Image, "", gettype(capture), taill_fichier(capture));
	
    
  
		
		
	

	close(s);
	return 0;
}




        
