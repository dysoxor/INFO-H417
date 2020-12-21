#ifndef PROJECT_INPUTSTREAM4_H
#define PROJECT_INPUTSTREAM4_H

#include "InputStream.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
using namespace std;

class InputStream4 : public InputStream
{
private:
  ifstream inputFile;
  HANDLE hfile;
  HANDLE hfileMapping;
  LPVOID fileView = NULL;
  long long int fileOpenSize;
  DWORD granularity;              //Granularity of the system used to know the size of each memory block
  long long int startMapView = 0; //Number of bits at which we create the view in the file, starting value 0
  int numberOfBlockMapped = 32;    //Base one but can be chosen by the user
  int offsetBytesCounter = 0;

  //Private éethod concerning the method of reading the file with mapping
  bool openAndMapFile(string path, long long int offsetInTheFile = 0, int numberOfBlock = 1);
  bool openFile(string path); //Open the file and store into hfile the link
  bool getTheFileSize();      //Get the file size in the correct type
  bool mappingFile();
  bool mapViewLink();
  bool closeWindowsFile();
  bool closeMappingFile();
  void closeMapView();

public:
  InputStream4(); // Constructor
  bool open(string path);
  bool close();    //Close all object related to the stream
  string readln(); //Read the next line via mappingstring readln4(); //Read the next line via mapping
  void seek(int pos);
  bool end_of_stream();
  long long int getSize();
};

#endif //PROJECT_INPUTSTREAM4_H
