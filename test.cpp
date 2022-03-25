#include <arpa/inet.h>
#include <iostream>
#include "base.h"
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>


using namespace std;

//Copie de fichiers avec lecture/écriture
int main(){

  int taille=0;

  struct stat st;
  if (0 == stat("test.jpg", &st)) {
    taille = st.st_size;
  }

  char img[taille];

  FILE * mFile = fopen("test.jpg", "r");
  size_t rez = fread(img, taille, 1, mFile);
  std::cout << "Read " << rez << "bytes" << '\n';
  fclose(mFile);

  const char* name = "test2.jpg";


  FILE * dest = fopen(name, "w");
  fwrite(img, taille, 1, dest);
  fclose(dest);

  return 0;
}
