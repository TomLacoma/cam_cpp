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


#include <fstream>
#include <vector>

#include "edit_html.h"

using namespace std;


using namespace std::chrono;


void edit_html(string client, string date)
{
  ofstream html_file;
  ifstream html_template;
  html_file.open(client +".html");
  html_template.open(client +".tmpl");

  vector<string> lines;
  string line;
  string Date_indice = "<!--Date et heure:-->";

  while(getline(html_template, line)){
    lines.push_back(line);
    html_file << line << endl;
    if (line.find(Date_indice)!=string::npos){
      html_file << date << endl;
    }
  }
  html_template.close();
  html_file.close();
}

Client::Client(){
  ip = "NONE";
  f=0;

  time_t t = 0;
  last_seen = localtime(&t);

  last_pic = "NONE";
}

Client::Client(char* ip_addr, int _f, string img){
  ip = ip_addr;
  f = _f;

  time_t t;
  time(&t);
  last_seen = localtime(&t);

  nb_clients++;

  last_pic = img;
}

Client::~Client(){
  nb_clients--;
}

void Client::update(int _f){
  f = _f;
  time_t t;
  time(&t);
  last_seen = localtime(&t);
}
