#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
using namespace std;

class OutputStream{
private:
  HANDLE hfile;
  HANDLE hfileMapping;
  LPVOID fileView = NULL;
  DWORD fileOpenSize;
  DWORD fileMappingSize; //Real size of the mapped object
  DWORD dwFileMapViewStart; //Start of the map view objects
  DWORD granularity; //Granularity of the system used to know the size of each memory block
  DWORD startMapView = 0; //Number of bits at which we create the view in the file, starting value 0
  int offsetBytesCounter = 0;

public:

  OutputStream();

  //Method concerning readln4 for the mapping method
   bool openFile(string path); //Open the file and store into hfile the link
   bool mappingFile(int stringSize);
   bool mapViewLink();
   void closeWindowsFile();
   void closeMappingFile();
   void closeMapView();
   void closeAllMappingRelatedObjects();
   bool writeln4(string pathToFile, string lineToWrite); //Read the next line via mappingstring readln4(); //Read the next line via mapping


   void create();
   void writeln(string line);
   void close();

};

#endif //PROJECT_OUTPUTSTREAM_H
