#include "InputStream.h"

InputStream::InputStream(){
  //Get the granularity of the system
  SYSTEM_INFO lpSystemInfo;
  GetSystemInfo(&lpSystemInfo);
  granularity = lpSystemInfo.dwAllocationGranularity;

}

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


bool InputStream::openAndMapFile(string path, DWORD offsetInTheFile, int numberOfBlock){
  if(!openFile(path)){return false;};
  if(mappingFile()){return false;}; //Map the file Open with CreateOpen
  startMapView = offsetInTheFile; // Starting point of the view
  numberOfBlockMapped = numberOfBlock;
  if(!mapViewLink()){return false;}; //Initialize the pointer to the map file3}
  return true;
}

bool InputStream::openFile(string path){
  // open a file in read only with some flags
  bool isNormal = true;
  hfile = CreateFile(path.c_str(), //Path of the file
                          GENERIC_READ, //open for reading
                          0,            //do not share
                          NULL,         //security by default
                          OPEN_EXISTING, //open an existing file
                          FILE_ATTRIBUTE_NORMAL, //normal file
                          NULL); //no attribute template

  //Gestion d erreur

  //Store the file size
  fileOpenSize = GetFileSize(hfile,NULL);

  return isNormal;
}

bool InputStream::mappingFile(){
  //Mapped the file and retrieve the Handler
  bool isNormal = true;
  hfileMapping = CreateFileMapping(hfile, //handler of the file to map
                                   NULL, // Security attribute
                                   PAGE_READONLY, //Type of protection
                                   0, // High order Dword size
                                   0, //Low order Dword size if (0,0) map the file completely
                                   NULL); //Name of the fileMapping object

  if(GetLastError() == ERROR_FILE_INVALID){std::cout<< "Error mapping invalid"<< std::endl; isNormal=false;}
  else{std::cout << "Error while mapping the file" << std::endl; isNormal =false;}

  return isNormal;
}

/*
  This is where we have to be careful with the size, the MapView is reserved
  space in the virtual memory of the process and must not be too big. We need
  to map only the part that we are going to use. (Must respect the syst granularity)
*/
bool InputStream::mapViewLink(){
  /*
    The offset at which the mapView start,we need to start at a multiple off the
    granularity to correspond to a memory block. Here we round down the offset to
    the nearest block
  */
  bool isNormal = true;
  DWORD dwFileMapStart =(startMapView/granularity) *granularity; // The offset at which the mapView start in bits
  DWORD dwMapViewSize = (numberOfBlockMapped*granularity); //In bytes !!

  //Create the FileView
  fileView = MapViewOfFile(hfileMapping, //Handle to the mapping object
                           FILE_MAP_READ, //Protection
                           0,             //High order 32 bits file offset
                           dwFileMapStart,           // Low order 32 bits file offset
                           dwMapViewSize);          // number of bytes to map

  if(fileView == NULL){std::cout << "Error while creating the  view map" << std::endl; isNormal=false;}

  return isNormal;
}

void InputStream::closeWindowsFile(){
  if(CloseHandle(hfile)){std::cout << "The open file is now closed" <<std::endl;}
}

void InputStream::closeMappingFile(){
  if(CloseHandle(hfileMapping)){std::cout << "The mapping of the file is now closed" << std::endl;}
  else{std::cout << "Error in closing the mapping handle" << std::endl;}
}
void InputStream::closeMapView(){
  UnmapViewOfFile(fileView);
  //Gestion d erreur
  std::cout << "MapViewClose" << std::endl;
}

void InputStream::closeAllMappingRelatedObjects(){
  closeMapView();
  closeMappingFile();
  closeWindowsFile();
}


string InputStream::readln4(){
  string line = "";

  if(fileView == NULL){return NULL;}

  //Read the file
  char* data = (char*) fileView;
  unsigned int j = 0;
  bool endOfRead = false;
  while(!endOfRead){

    if( offsetBytesCounter+j > numberOfBlockMapped*granularity){
      startMapView = offsetBytesCounter+j;
      closeMapView();
      mapViewLink();
      j=0;
      offsetBytesCounter = 0;
    }
    else{
      if( *(data+j+offsetBytesCounter) == '\n'){endOfRead=true;}
      else{line += *(data+j+offsetBytesCounter);}
      ++j;
    }
  }
  offsetBytesCounter += j;

  return line;
}
