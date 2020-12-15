#ifndef PROJECT_OUTPUTSTREAM4_H
#define PROJECT_OUTPUTSTREAM4_H


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <math.h>
using namespace std;

class OutputStream4{
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

  //Private method concerning the mapping of the file
  bool mappingFile(int stringSize);
  bool getTheFileSize(); //Get the file size in the correct type
  bool mapViewLink();
  void closeWindowsFile();
  void closeMappingFile();
  void closeMapView();

public:

  OutputStream4();
  bool writeln(string lineToWrite); //Read the next line via mappingstring readln4(); //Read the next line via mapping
  void create(string path);//Create the file and store into hfile the link
  void close();
};

#endif //PROJECT_OUTPUTSTREAM4_H
