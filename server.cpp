#include <arpa/inet.h>
#include <iostream>
#include "base.h"
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include "edit_html.h"




#define MAX_CLIENTS 128 //arbitraire, pour ne pas avoir trop de clients connectés

using namespace std;


int Client::nb_clients = 0; //initialize at -1 so the indexes in void* clients are not messed up (indexed by static int nb_clients)

void * hconnect (void * fd)

{
	//std::cout << "Début du thread" << '\n';

	Client* client = (Client*)fd;
	int f = client->f;
	char buf[100]; //file name = date
  int ret;
  ret = read(f, buf, sizeof(buf)); //receive the date the picture was taken

	string name = string(client->ip) + "img" + to_string(client->pic_count) + ".jpg";
	client->last_pic = name; //update name and picture counts
	client->pic_count ++;


  long unsigned int taille=0;
  ret = read(f, &taille, sizeof(taille)); //receive the image size


  char img[taille];

	long unsigned int remain = taille;
	size_t img_offset = 0;
	while (remain > 0) { //receive the image data (in several reads if needed), prevents the limitation from tcp buffer size
		ret = read(f, img + img_offset, remain);
		remain -= ret;
		img_offset += ret;
	}

  FILE * dest = fopen(name.c_str(), "w"); //write the image to the file
  fwrite(img, taille, 1, dest);
  fclose(dest);

	edit_html(client); //updates the image path in the html file for the iframe

	close(f);

	//free(fd);
	pthread_detach(pthread_self());
	return NULL;
}

int main (int argc, char ** argv)

{
        const char * server = "0.0.0.0";
        struct sockaddr_in sin;
        int s, f, ret;
				pthread_t tid;
				int optval = 1;

				bool new_client = true;
				int index;

				void** clients = new void*[MAX_CLIENTS];
				for(int i=0; i<MAX_CLIENTS; i++){
					clients[i] = NULL;
				}

        sin.sin_family = AF_INET;
        sin.sin_port = htons(DEFAULT_PORT);
        ret = inet_aton(server, &sin.sin_addr);
        if (ret == 0) {
		fprintf(stderr, "address %s invalid\n", server);
		return 0;
	}

        s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
		fprintf(stderr, "cannot create socket\n");
		return 0;
	}

        ret = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (ret != 0) {
                fprintf(stderr, "setsockopt() failed\n");
                return 0;
        }

        ret = bind(s, (struct sockaddr *)&sin, sizeof(sin));
        if (ret != 0) {
		fprintf(stderr, "bind() failed\n");
		return 0;
	}

        ret = listen(s, 10);
        if (ret != 0) {
		fprintf(stderr, "listen() failed\n");
		return 0;
	}

        while (1) {
					if(Client::nb_clients>MAX_CLIENTS){
						std::cout << "Reached maximum number of clients, exiting..." << '\n';
						return 0;
					}

                struct sockaddr addr;
		socklen_t addrsize = sizeof(addr);
                f = accept(s, &addr, &addrsize);
		struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&addr;
		struct in_addr ipAddr = pV4Addr->sin_addr;
		char AdressIP[INET_ADDRSTRLEN];
		inet_ntop( AF_INET, &ipAddr, AdressIP, INET_ADDRSTRLEN );   //L'adresse IP est stocké dans la variable AdressIP
                if (f == -1) {
			fprintf(stderr, "accept() failed\n");
			return 0;
		}

		new_client=true;
		int i=0;

		while(clients[i]!=NULL){ //runs through all the memorized clients in void** clients
			if(strcmp(((Client*)clients[i])->ip, AdressIP) == 0){ //if ip matches one of the memorized clients
				(*(Client*)clients[i]).update(f); //updates client _i with the new socket number
				new_client=false;
				index=i; //set the index to be given to the receiving thread
			}
			i++;
		}


		if(new_client || Client::nb_clients==0){ //On the first client connexion or if a new client is seen
			clients[Client::nb_clients] = new Client(AdressIP, f, "NONE"); //creates a new client
			index=Client::nb_clients;
			Client::nb_clients++;

			edit_html_global(clients, Client::nb_clients); //adds an iframe in the global.html for the new client
		}

		pthread_create(&tid, NULL, hconnect, clients[index]); //creates a thread for the image to be received
        }

        return 0;
}
