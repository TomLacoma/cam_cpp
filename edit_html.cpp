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

void edit_html_global(void** clients, int nb_clients){
  //refreshes the global.html file with all the current clients store in void** clients
  ofstream html_file;
  ifstream html_template;
  html_file.open("global.html");
  html_template.open("global.tmpl");

  vector<string> lines;
  string line;
  string client_flag = "<!--clients-->";


  while(getline(html_template, line)){
    lines.push_back(line);
    if (line.find(client_flag)!=string::npos){ //if the client_flag string is found in current line...
      for(int i=0; i<nb_clients; i++){
      html_file <<   "<body>" << endl <<
      "<iframe src=\""<< (*(Client*)clients[i]).ip << ".html\" width=\"400\" height=\"400\"></iframe>" << endl << //...adds all the client iframes paths to the html file
      "</body>" << endl;
    }

      html_file << line << endl;
    }
    else{
      html_file << line << endl;
    }
  }
  html_template.close();
  html_file.close();

}


void edit_html(Client* client) //Edits specific client tmpl file to refresh the client file with the last pic
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
  ip = strdup(ip_addr);
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
