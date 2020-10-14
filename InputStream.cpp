#include "InputStream.h"


ifstream inputFile;


void InputStream::open(string path){
    inputFile.open(path);
    //Gérer les exceptions ici
}

void InputStream::seek(int pos){
    inputFile.seekg(pos);
}

bool InputStream::end_of_stream(){
  return inputFile.eof();
}


string InputStream::readln4(string path, unsigned int numberOfByte){
  string line = "";

  SYSTEM_INFO lpSystemInfo;
  GetSystemInfo(&lpSystemInfo);
  DWORD granularity = lpSystemInfo.dwAllocationGranularity;
  std::cout << "Granularite system : " << granularity << std::endl;

   // open a file with some flags
  HANDLE hfile = CreateFile(path.c_str(), //Path of the file
                           GENERIC_READ, //open for reading
                           0,            //do not share
                           NULL,         //security by default
                           OPEN_EXISTING, //open an existing file
                           FILE_ATTRIBUTE_NORMAL, //normal file
                           NULL); //no attribute template

  //Gestion d erreur

  //Mapped the file and retrieve the Handler
  HANDLE hfileMapping = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
  if(GetLastError() == NO_ERROR){std::cout<< "Mapping create succesfully"<< std::endl;}
  else{std::cout << "Error while mapping the file" << std::endl;}

  //Create the FileView
  LPCVOID fileView = MapViewOfFile(hfileMapping, FILE_MAP_READ, 0, 0, 0);
  if(fileView != NULL){std::cout << "MapView succesfully create " << std::endl;}
  else{std::cout << "Error while creating the  view map" << std::endl;}

  //Read the file
  char* data = (char*) fileView;
  unsigned int limit = (granularity/8);
  unsigned int i = 0;
  std::cout << "First line of the file : ";
  while(i<limit){
    if( *(data+i) !='\n'){
      std::cout <<*(data+i);
    }
    else{break;}
    ++i;
  }
  std::cout << std::endl;

 //Close qnd destroy all the created objects
  UnmapViewOfFile(fileView);
  if(CloseHandle(hfileMapping)){std::cout << "The mapping of the file : " << path << " is now closed" << std::endl;}
  else{std::cout << "Error in closing the mapping handle" << std::endl;}
  if(CloseHandle(hfile)){std::cout << "The file : " << path << " is now closed" <<std::endl;}
  return line;
}
