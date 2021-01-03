#include "OutputStream4.h"

OutputStream4::OutputStream4(){

  //Get the granularity of the system
  SYSTEM_INFO lpSystemInfo;
  GetSystemInfo(&lpSystemInfo);
  granularity = lpSystemInfo.dwAllocationGranularity;
  fileMappingSize=0;
  offsetBytesCounter = 0;
  fileMappingSize = 0;
}


bool OutputStream4::create(string path){
  // open a file in write only with some flags
  hfile = CreateFile(path.c_str(), //Path of the file
                          GENERIC_WRITE|GENERIC_READ, //open for writing and reading necessary to map
                          0,            //do not share
                          NULL,         //security by default
                          CREATE_ALWAYS, //open an existing file
                          FILE_ATTRIBUTE_NORMAL, //normal file
                          NULL); //no attribute template

  //Gestion d erreur
 if(hfile == INVALID_HANDLE_VALUE){std::cout << "Error while creating the file" << std::endl;return false;}
 if(!mappingFile()){return false;} //Map the file with the correct size
 if(!mapViewLink()){return false;} //Initialize the pointer to the map file

 return true;
}

bool OutputStream4::getTheFileSize(){
  DWORD lpFileOpenSizeHigh = 0;
  DWORD dwFileOpenSizeLow = 0;
  dwFileOpenSizeLow = GetFileSize(hfile,&lpFileOpenSizeHigh);

  fileOpenSize = dwFileOpenSizeLow +  (lpFileOpenSizeHigh * pow(2,32));
  return true;
}

/**
*This function create a mapping of the file in memory which is of PAGE_READWRITE type, with this access type the mapping can be of 
* bigger size than the file in order to write in it. When the memory will write back the file into the disk the size modification
* will also be done in the disk by allocating more space to the file.
* @return	TRUE the mapping was succesful, FALSE otherwise
*/

bool OutputStream4::mappingFile(){
  //Mapped the file and retrieve the Handler
  bool isNormal = true;
  fileMappingSize += numberBlockMapped*granularity; //Increment the size of the file with the size of the string

  hfileMapping = CreateFileMapping(hfile, //handler of the file to map
                                   NULL, // Security attribute
                                   PAGE_READWRITE, //Type of protection
                                   0, // High order Dword size
                                   fileMappingSize, //Low order Dword size if (0,0) map the file completely
                                   NULL); //Name of the fileMapping object

  IOCounter++;
  if(GetLastError() == ERROR_FILE_INVALID){std::cout<< "Error mapping invalid"<< std::endl; isNormal=false;}
  else if(hfileMapping == NULL){std::cout << "Error while mapping the file" << std::endl; isNormal =false;}

  return isNormal;
}

bool OutputStream4::mapViewLink(){
  /*
    The offset at which the mapView start,we need to start at a multiple off the
    granularity to correspond to a memory block. Here we round down the offset to
    the nearest block
  */
  FileMapViewStart =(startMapView/(granularity)) *(granularity); // The offset at which the mapView start
  long long int FileMapViewStartLowInt = FileMapViewStart & 0x00000000FFFFFFFF ;
  long long int FileMapViewStartHighInt = FileMapViewStart & 0xFFFFFFFF00000000;
  DWORD dwFileMapViewStartLow =  FileMapViewStartLowInt;// The offset at which the mapView start in bits
  DWORD dwFileMapViewStartHigh = FileMapViewStartHighInt;
  DWORD dwMapViewSize = numberBlockMapped*granularity;

  if( (FileMapViewStart + dwMapViewSize) > fileMappingSize){dwMapViewSize = fileMappingSize-FileMapViewStart;}

  //Create the FileView
  fileView = MapViewOfFile(hfileMapping, //Handle to the mapping object
                           FILE_MAP_WRITE, //Protection
                           dwFileMapViewStartHigh,             //High order 32 bits file offset
                           dwFileMapViewStartLow,           // Low order 32 bits file offset
                           dwMapViewSize);          // number of bytes to map

  if(fileView == NULL){std::cout << "Error while creating the view map" << std::endl; return false;}
  return true;
}

void OutputStream4::closeWindowsFile(){
  if(!CloseHandle(hfile)){std::cout << "Error while closing the file" <<std::endl;}
}

void OutputStream4::closeMappingFile(){
  if(!CloseHandle(hfileMapping)){std::cout << "Error in closing the mapping handle" << std::endl;}
}
void OutputStream4::closeMapView(){
  UnmapViewOfFile(fileView);
}

void OutputStream4::close(){
  closeMapView();
  closeMappingFile();
  closeWindowsFile();
}

/**
* This function takes a string and write it into the mapView link to the mapping of the file which handle is in the attribut of the class.
* In order ti limit the numbers of time thhe mapping is done, the mapping of the file is done only when the size of the actual file + the
* size of the next line to write is over the limit of the mapping size. Each time this case happened we have to remap the file in memory
* with an increase size and recreate a mapView and adjust it to be where the pointer was.
*@param string line   the line to write in the file
*/
void OutputStream4::writeln(string line){
  line += '\n';
  if(hfile==NULL){std::cout << "Empty file handle" << endl; return;}
  if(!getTheFileSize()){std::cout << "Error in retrieving the file size" << endl;}

  if(fileView == NULL){std::cout << "Error while trying to access fileView of file" << endl;}

  char* data = (char*) fileView;
  const char* lineChar = line.c_str() ;

  for(int i=0; i<line.size(); ++i){
    //Check if we need to remap the file
    if(FileMapViewStart+offsetBytesCounter >= fileOpenSize){
      if(!mappingFile()){std::cout << "Error in mapping the file" << endl; return;}
      if(!getTheFileSize()){std::cout << "Error in retriving the file size" << endl;}
    }
    //Check if we need to remap the view
    if( offsetBytesCounter >= numberBlockMapped*granularity){
      startMapView = FileMapViewStart+offsetBytesCounter;
      closeMapView();
      if(!mapViewLink()){return;}
      data = (char*) fileView;
      offsetBytesCounter=0;
    }
    *(data+offsetBytesCounter) = lineChar[i];
    ++offsetBytesCounter;
  }
  //closeMapView();
}
