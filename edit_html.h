#include <string>


using namespace std;



class Client{ //stores the data for a specific connected client
public:
  const char* ip; //ip client
  int f; //socket number

  struct tm* last_seen; //last time the client was seen
  static int nb_clients; //amount of clients


  string last_pic; //path to last pic taken by client
  int pic_count; //numper of received pictures since client connexion

  Client(char* _ip, int _f, string _last_pic);
  Client();
  ~Client();
  void update(int f);
  void new_pic();
};




void edit_html(Client*);
void edit_html_global(void** clients, int nb_clients);
