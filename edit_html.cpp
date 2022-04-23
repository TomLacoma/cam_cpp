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


void edit_html(Client* client)
{
  ofstream html_file;
  ifstream html_template;
  html_file.open((string) client->ip +".html");
  html_template.open("template.tmpl");

  vector<string> lines;
  string line;
  string Date_indice = "<!--Date et heure:-->";
  string Client_indice = "<!-- Client -->";
  string Pic_indice = "<!-- Pic -->";
  string Meta_indice = "<!--meta-->";


  while(getline(html_template, line)){
    lines.push_back(line);
    if (line.find(Date_indice)!=string::npos){
      html_file << asctime(client->last_seen) << endl; //adds date to the html file
    }
    else if(line.find(Client_indice)!=string::npos){
      html_file << "<h1>" << client->ip << "</h1>" << endl; //add the client ip to the html file
    }
    else if(line.find(Pic_indice)!=string::npos){
      html_file << "<img src=\"" << client->last_pic << "\" width=\"400\" height=\"400\" alt=\"" << client->ip <<"\">" << endl; //add the client ip to the html file
    }
    else if(line.find(Meta_indice)!=string::npos){
      html_file << "<meta http-equiv=\"refresh\" content=\"5; url="<< (string) client->ip +".html" << "\" charset=\"utf-8\">" << endl; //add the client ip to the html file
    }
    else{
          html_file << line << endl;
    }
  }
  html_template.close();
  html_file.close();
}

Client::Client(){
  std::cout << "Empty client created" << '\n';
  ip = "NONE";
  f=0;


  time_t t = 0;
  last_seen = localtime(&t);
  pic_count=0;
  last_pic = "NONE";
}

Client::Client(char* ip_addr, int _f, string img){
  std::cout << "Client created" << '\n';
  ip = ip_addr;
  f = _f;

  time_t t;
  time(&t);
  last_seen = localtime(&t);


  pic_count=0;
  last_pic = img;
}

Client::~Client(){
  std::cout << "destroyed client" << '\n';
}

void Client::update(int _f){
  f = _f;
  time_t t;
  time(&t);
  last_seen = localtime(&t);
}

void Client::new_pic(){
  pic_count++;
}
