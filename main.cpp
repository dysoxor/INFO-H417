#include <iostream>
using namespace std;

#include "InputStream.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\aka_name.csv" ;
  InputStream stream;
  if(!stream.openAndMapFile(filePath,0,1)){return 1;}; // Error in opening the files
  string text = ""; // Use to concatenate all the lines faster than displaying one by one
  for(int i=0; i<1000; ++i){
    std :: cout << stream.readln4() << std::endl;
  }

  std::cout << std::endl;
  stream.closeAllMappingRelatedObjects();

}
