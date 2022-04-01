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


void edit(string client)
{
  ofstream html_file;
  ifstream html_template;
  html_file.open(client +".html");
  html_template.open(client +".tmpl");

  vector<string> lines;
  string line;
  string Date_indice = "    <!--  Date et heure: -->";

  time_t t;
  struct tm * T;
  time(&t);
  T=localtime(&t);

  while(getline(html_template, line)){
    lines.push_back(line);
    html_file << line << endl;
    if (line==Date_indice){
      html_file << asctime(T) << endl;
    }
  }
  html_template.close();
  html_file.close();
}
