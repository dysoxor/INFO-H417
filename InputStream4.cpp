#include "InputStream4.h"

InputStream4::InputStream4(){
  //Get the granularity of the system
  SYSTEM_INFO lpSystemInfo;
  GetSystemInfo(&lpSystemInfo);
  granularity = lpSystemInfo.dwAllocationGranularity;
}

bool InputStream4::open(string path){
    return openAndMapFile(path);
}

void InputStream4::seek(int pos){
  startMapView = pos ;
  long long int multipleGranularity = (startMapView/(granularity)) * granularity;
  offsetBytesCounter = startMapView - multipleGranularity;
  closeMapView();
  if(!mapViewLink()){std::cout << "Error while seeking the pos" << '\n';}
}

bool InputStream4::end_of_stream(){
  if(startMapView + offsetBytesCounter >= fileOpenSize){return true;}
  return false;
}


bool InputStream4::openAndMapFile(string path, long long int offsetInTheFile, int numberOfBlock){
  if(!openFile(path)){return false;};
  if(!mappingFile()){return false;}; //Map the file Open with CreateOpen
  startMapView = offsetInTheFile; // Starting point of the view
  numberOfBlockMapped = numberOfBlock;
  if(!mapViewLink()){return false;}; //Initialize the pointer to the map file
  return true;
}

bool InputStream4::openFile(string path){
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
 if(hfile == INVALID_HANDLE_VALUE){std::cout << "Error while creating the file" << std::endl; isNormal =false;}
 else{getTheFileSize();}

  return isNormal;
}

bool InputStream4::getTheFileSize(){
  DWORD lpFileOpenSizeHigh = 0;
  DWORD dwFileOpenSizeLow = 0;
  dwFileOpenSizeLow = GetFileSize(hfile,&lpFileOpenSizeHigh);

  fileOpenSize = dwFileOpenSizeLow +  (lpFileOpenSizeHigh * pow(2,32));
  return true;
}

bool InputStream4::mappingFile(){
  //Mapped the file and retrieve the Handler
  bool isNormal = true;
  hfileMapping = CreateFileMapping(hfile, //handler of the file to map
                                   NULL, // Security attribute
                                   PAGE_READONLY, //Type of protection
                                   0, // High order Dword size
                                   0, //Low order Dword size if (0,0) map the file completely
                                   NULL); //Name of the fileMapping object

  if(GetLastError() == ERROR_FILE_INVALID){std::cout<< "Error mapping invalid"<< std::endl; isNormal=false;}
  else if(hfileMapping == NULL){std::cout << "Error while mapping the file" << std::endl; isNormal =false;}

  return isNormal;
}

/*
  This is where we have to be careful with the size, the MapView is reserved
  space in the virtual memory of the process and must not be too big. We need
  to map only the part that we are going to use. (Must respect the syst granularity)
*/
bool InputStream4::mapViewLink(){
  /*
    The offset at which the mapView start,we need to start at a multiple off the
    granularity to correspond to a memory block. Here we round down the offset to
    the nearest block
  */
  bool isNormal = true;
  long long int FileMapStart = (startMapView/(granularity)) *(granularity);
  long long int FileMapStartLowInt = FileMapStart & 0x00000000FFFFFFFF ;
  long long int FileMapStartHighInt = FileMapStart & 0xFFFFFFFF00000000;
  DWORD dwFileMapStartLow =  FileMapStartLowInt;// The offset at which the mapView start in bits
  DWORD dwFileMapStartHigh = FileMapStartHighInt;
  DWORD dwMapViewSize = (numberOfBlockMapped*(granularity)); //In bytes !!

  if( (FileMapStart + dwMapViewSize) > fileOpenSize){dwMapViewSize = fileOpenSize-FileMapStart;}
  //Create the FileView
  fileView = MapViewOfFile(hfileMapping, //Handle to the mapping object
                           FILE_MAP_READ, //Protection
                           dwFileMapStartHigh,             //High order 32 bits file offset
                           dwFileMapStartLow,           // Low order 32 bits file offset
                           dwMapViewSize);          // number of bytes to map

  if(fileView == NULL){std::cout << "Error while creating the  view map" << std::endl; isNormal=false;}

  return isNormal;
}

bool InputStream4::closeWindowsFile(){
  return CloseHandle(hfile);
}

bool InputStream4::closeMappingFile(){
  return CloseHandle(hfileMapping);
}

void InputStream4::closeMapView(){
  UnmapViewOfFile(fileView);
}

bool InputStream4::close(){
  closeMapView();
  if(!closeMappingFile()){return false;}
  if(closeWindowsFile()){return false;}
  return true;
}


string InputStream4::readln(){
  string line = "";

  if(fileView == NULL){return NULL;}

  //Read the file
  char* data = (char*) fileView;
  unsigned int j = 0;
  bool endOfRead = false;
  while(!endOfRead){

    if( ((offsetBytesCounter)+startMapView) >= (fileOpenSize)){ // If the end is reached
      endOfRead=true;
      line = "";
    }
    else if( (offsetBytesCounter+j) >= (numberOfBlockMapped*(granularity))){
      startMapView += (offsetBytesCounter+j);
      closeMapView();
      if(!mapViewLink()){endOfRead=true;}
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
  if(!line.empty()){line.erase(line.length()-1);}
  return line;
}
