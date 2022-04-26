#include <string>


using namespace std;



class Client{
public:
  const char* ip; //ip client
  int f; //socket

  struct tm* last_seen;
  static int nb_clients;


  string last_pic; //path to last pic taken by client
  int pic_count;

  Client(char* _ip, int _f, string _last_pic);
  Client();
  ~Client();
  void update(int f);
  void new_pic();
};




void edit_html(Client*);
void edit_html_global(void** clients, int nb_clients);
