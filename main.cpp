#include <iostream>
using namespace std;

#include "InputStream.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\aka_name.csv" ;
  InputStream stream;
  if(!stream.openAndMapFile(filePath,0,1)){return 1;}; // Error in opening the files
  for(int i=0; i<901343; ++i){
    //std::cout <<stream.readln4() << std::endl;
    stream.readln4();
  }

  std::cout << std::endl;
  stream.closeAllMappingRelatedObjects();

return 0;
}
