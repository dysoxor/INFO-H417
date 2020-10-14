#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class InputStream{

public :
  void open(string path);
  string readln(); // Voir si on envoie pas un parametre pour select le mode de read
  string readln4(string path, unsigned int numberOfByte);
  void seek(int pos);
  bool end_of_stream();
};

#endif //PROJECT_INPUTSTREAM_H
