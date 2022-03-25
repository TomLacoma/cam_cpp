#include <arpa/inet.h>
#include <iostream>
#include "base.h"
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <fstream>

using namespace std;

void * hconnect (void * fd)

{
	int f = *((int *)fd);
	char buf[256]; //file name = date
  int ret;
  ret = read(f, buf, sizeof(buf));
  string name = (string) buf + ".jpg";//file name

  std::cout << buf << endl << ret << std::endl;

  long unsigned int taille;
  ret = read(f, &taille, sizeof(taille)); //receive the image size


  char img[taille];

  ret = read(f, img, sizeof(img)); //receive the image

  FILE * dest = fopen(name.c_str(), "w"); //write the image
  fwrite(img, taille, 1, dest);
  fclose(dest);

	close(f);

	free(fd);
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
                f = accept(s, NULL, 0);
                if (f == -1) {
			fprintf(stderr, "accept() failed\n");
			return 0;
		}

		int * fd = new int;
		*fd = f;
		pthread_create(&tid, NULL, hconnect, (void *)fd);
        }

        return 0;
}
