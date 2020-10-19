#include <iostream>
using namespace std;

#include "InputStream.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\aka_name.csv" ;
  InputStream stream;
  string text = "";
  if(!stream.openAndMapFile(filePath,0,1)){return 1;}; // Error in opening the files
  do {
    text = stream.readln4();
    std::cout << text << std::endl;
  } while(text != "");

  std::cout << std::endl;
  stream.closeAllMappingRelatedObjects();

return 0;
}
