#include "OutputStream.h"

OutputStream::OutputStream(){
  //Get the granularity of the system
  SYSTEM_INFO lpSystemInfo;
  GetSystemInfo(&lpSystemInfo);
  granularity = lpSystemInfo.dwAllocationGranularity;
}


bool OutputStream::openFile(string path){
  // open a file in write only with some flags
  bool isNormal = true;
  hfile = CreateFile(path.c_str(), //Path of the file
                          GENERIC_WRITE|GENERIC_READ, //open for writing and reading necessary to map
                          0,            //do not share
                          NULL,         //security by default
                          OPEN_EXISTING, //open an existing file
                          FILE_ATTRIBUTE_NORMAL, //normal file
                          NULL); //no attribute template

  //Gestion d erreur
 if(hfile == INVALID_HANDLE_VALUE){std::cout << "Error while creating the file" << std::endl; isNormal =false;}
 else{fileOpenSize = GetFileSize(hfile,NULL);}
 return isNormal;
}

bool OutputStream::mappingFile(int stringSize){
  //Mapped the file and retrieve the Handler
  bool isNormal = true;
  fileMappingSize = fileOpenSize+stringSize+2; //Increment the size of the file with the size of the string + 2 for \n

  hfileMapping = CreateFileMapping(hfile, //handler of the file to map
                                   NULL, // Security attribute
                                   PAGE_READWRITE, //Type of protection
                                   0, // High order Dword size
                                   fileMappingSize, //Low order Dword size if (0,0) map the file completely
                                   NULL); //Name of the fileMapping object


  if(GetLastError() == ERROR_FILE_INVALID){std::cout<< "Error mapping invalid"<< std::endl; isNormal=false;}
  else if(hfileMapping == NULL){std::cout << "Error while mapping the file" << std::endl; isNormal =false;}

  return isNormal;
}

bool OutputStream::mapViewLink(){
  /*
    The offset at which the mapView start,we need to start at a multiple off the
    granularity to correspond to a memory block. Here we round down the offset to
    the nearest block
  */
  bool isNormal = true;
  dwFileMapViewStart =(startMapView/(granularity)) *(granularity); // The offset at which the mapView start in bits
  DWORD dwMapViewSize = 1*granularity; //In bytes !!

  if( (dwFileMapViewStart + dwMapViewSize) > fileMappingSize){dwMapViewSize = fileMappingSize-dwFileMapViewStart;}

  //Create the FileView
  fileView = MapViewOfFile(hfileMapping, //Handle to the mapping object
                           FILE_MAP_WRITE, //Protection
                           0,             //High order 32 bits file offset
                           dwFileMapViewStart,           // Low order 32 bits file offset
                           dwMapViewSize);          // number of bytes to map

  if(fileView == NULL){std::cout << "Error while creating the  view map" << std::endl; isNormal=false;}

  return isNormal;
}

void OutputStream::closeWindowsFile(){
  if(CloseHandle(hfile)){std::cout << "The open file is now closed" <<std::endl;}
}

void OutputStream::closeMappingFile(){
  if(CloseHandle(hfileMapping)){std::cout << "The mapping of the file is now closed" << std::endl;}
  else{std::cout << "Error in closing the mapping handle" << std::endl;}
}
void OutputStream::closeMapView(){
  UnmapViewOfFile(fileView);
}

void OutputStream::closeAllMappingRelatedObjects(){
  closeMapView();
  closeMappingFile();
  closeWindowsFile();
}

bool OutputStream::writeln4(string pathToFile, string lineToWrite){

  if(!openFile(pathToFile)){return false;}
  if(!mappingFile(lineToWrite.size())){return false;} //Map the file with the correct size
  startMapView = fileOpenSize; // Starting point of the view
  if(!mapViewLink()){return false;} //Initialize the pointer to the map file

  if(fileView == NULL){std::cout << "Error while acceding fileView of file" << '\n';;}

  char* data = (char*) fileView;
  const char* lineChar = lineToWrite.c_str() ;
  int basicOffset = fileOpenSize - dwFileMapViewStart;
  *(data+basicOffset+1) = '\n';
  for(int i=2; i<lineToWrite.size()+2; ++i){
    *(data+i+basicOffset) = lineChar[i-2];
  }

  closeAllMappingRelatedObjects();
  return true;
}
