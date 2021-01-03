#ifndef PROJECT_OUTPUTSTREAM4_H
#define PROJECT_OUTPUTSTREAM4_H

#include "OutputStream.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <math.h>
using namespace std;

class OutputStream4 : public OutputStream {
private:
  HANDLE hfile = NULL;
  HANDLE hfileMapping;
  LPVOID fileView = NULL;
  long long int fileOpenSize;
  DWORD fileMappingSize; //Real size of the mapped object
  long long int FileMapViewStart; //Start of the map view objects
  DWORD granularity; //Granularity of the system used to know the size of each memory block
  long long int startMapView = 0; //Number of bits at which we create the view in the file, starting value 0
  int offsetBytesCounter = 0;
  int numberBlockMapped = 1; //Number of numberBlockMapped add

  //Private method concerning the mapping of the file
  bool mappingFile();
  bool getTheFileSize(); //Get the file size in the correct type
  bool mapViewLink();
  void closeWindowsFile();
  void closeMappingFile();
  void closeMapView();

public:

  OutputStream4();
  void writeln(string line);//Write to the file the content of the string into a next line
  bool create(string path);//Create the file and store into hfile the link
  void close();
};

#endif //PROJECT_OUTPUTSTREAM4_H
