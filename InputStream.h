#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class InputStream{
private:
  ifstream inputFile;
  HANDLE hfile;
  HANDLE hfileMapping;
  LPVOID fileView = NULL;
  DWORD fileOpenSize;
  DWORD granularity; //Granularity of the system used to know the size of each memory block
  DWORD startMapView = 0; //Number of bits at which we create the view in the file, starting value 0
  int numberOfBlockMapped = 1; //Base one but can be chosen by the user
  int offsetBytesCounter = 0;

public:
  InputStream(); // Constructor

  void open(string path);

 //Method concerning readln4 for the mapping method
  bool openAndMapFile(string path, DWORD offsetInTheFile=0, int numberOfBlock=1);
  bool openFile(string path); //Open the file and store into hfile the link
  bool mappingFile();
  bool mapViewLink();
  void closeWindowsFile();
  void closeMappingFile();
  void closeMapView();
  void closeAllMappingRelatedObjects();
  string readln4(); //Read the next line via mappingstring readln4(); //Read the next line via mapping

  string readln(); // Voir si on envoie pas un parametre pour select le mode de read
  void seek(int pos);
  bool end_of_stream();
};

#endif //PROJECT_INPUTSTREAM_H
