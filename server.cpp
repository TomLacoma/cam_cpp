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


int Client::nb_clients = -1; //initialize at -1 so the indexes in void* clients are not messed up (indexed by static int nb_clients)

void * hconnect (void * fd)

{
	std::cout << "Début du thread" << '\n';
	//Client* client = new Client();
	std::cout << "debug1" << '\n';
	Client* client = (Client*)fd;
	int f = client->f;
	std::cout << "debug2" << '\n';
	char buf[100]; //file name = date
  int ret;
  ret = read(f, buf, sizeof(buf));

	string name = string(client->ip) + "img" + to_string(client->pic_count) + ".jpg";
	std::cout << buf << '\n';
	client->last_pic = name;
	client->pic_count ++;
	std::cout << "pic count "<<  client->pic_count << '\n';
  //std::cout << buf << " " << sizeof(buf) << endl << ret << std::endl;

  long unsigned int taille;
  ret = read(f, &taille, sizeof(taille)); //receive the image size

	//std::cout << "taille image reçue" << taille << '\n';

  char img[taille];
	//memset(img, 0, taille);

	long unsigned int remain = taille;
	size_t img_offset = 0;
	while (remain > 0) {
		ret = read(f, img + img_offset, remain);
		//cout << "ret " << ret << " remain " << remain << endl;
		remain -= ret;
		img_offset += ret;
	}
//  ret = read(f, img, taille); //receive the image
	/*printf("ret = %d taille = %lu\n", ret, taille);
	FILE * fp = fopen("server.log", "w");
	for (unsigned i = 0; i < taille; i++) fprintf(fp, "%d ", img[i]);
	fprintf(fp, "\n");
	fclose(fp);*/

  FILE * dest = fopen(name.c_str(), "w"); //write the image
  fwrite(img, taille, 1, dest);
  fclose(dest);

	edit_html(client);

	//rajouter ici : save changes, qui migre tout le contenu de la classe client locale vers celle de la liste
	std::cout << "End of thread, closing \n" << '\n';
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

				void* clients[MAX_CLIENTS];

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
					new_client=true;
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


		/*void* client;
		Client c(AdressIP, f, "NONE");
		client = &c;*/


		std::cout << "coucou" << '\n';

		for(int _i=0; _i<Client::nb_clients; _i++){
			if((*(Client*)clients[_i]).ip == AdressIP){
				(*(Client*)clients[_i]).update(f);//updates client _i with the new socket number
				new_client=false;
				index=_i;
				std::cout << "updated" << '\n';
			}
		}
		if(new_client){
			Client::nb_clients++;
			clients[Client::nb_clients]= new Client(AdressIP, f, "NONE");
			index=Client::nb_clients;
			std::cout << "created" << '\n';
		}
		std::cout << "coucou2" << '\n';

		//std::cout << AdressIP << '\n';
		/*int * fd = new int;
		*fd = f;
		pthread_create(&tid, NULL, hconnect, (void *)fd);*/
		pthread_create(&tid, NULL, hconnect, clients[index]);
		std::cout << "Client count " << Client::nb_clients << '\n';
		//pthread_create(&tid, NULL, hconnect, client);

        }

        return 0;
}
