#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include "base.h"
#include <cstring>
#include <unistd.h>

using namespace std;

int main (int argc, char * argv[])

{
        struct sockaddr_in saddr;
        struct hostent * server;
        int s, ret;


	if (argc == 1) {
		std::cerr << "usage: " << argv[0]
			  << " [ adresse IP/nom du serveur ]" << std::endl;
		return 0;
	}

        s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
                std::cerr << "cannot create socket" << std::endl;
                return 0;
        }

        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(DEFAULT_PORT);
        server = gethostbyname(argv[1]);
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

  time_t t;
	struct tm * T;
  char tmp[100];

  time(&t);
  T = localtime(&t);
  snprintf(tmp, sizeof(tmp), "%s", asctime(T));

  ret=write(s, tmp, 1 + strlen(tmp));
  std::cout << ret << '\n';



	close(s);
	return 0;
}
