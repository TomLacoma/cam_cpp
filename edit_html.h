#include <string>


using namespace std;



class Client{
public:
  const char* ip; //ip client
  int f; //socket

  struct tm* last_seen;
  static int nb_clients;

  string last_pic; //path to last pic taken by client


  Client(char* _ip, int _f, string _last_pic);
  Client();
  ~Client();
  void update(int f);
};




void edit_html(std::string, std::string);
