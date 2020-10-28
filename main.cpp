#include <iostream>
using namespace std;

//#include "InputStream.h"
#include "OutputStream.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\test.txt" ;

  //Read sequentially
  /*InputStream rstream;
  string text = "";
  if(!rstream.openAndMapFile(filePath,0,1)){return 1;}; // Error in opening the files
  do {
    text = rstream.readln4();
    std::cout << text << std::endl;
  } while(text != "");

  std::cout << std::endl;
  rstream.closeAllMappingRelatedObjects();*/

  //Write to a file
  /*OutputStream wstream;
  string testS = "Test of write function et voir si\nle saut de ligne fct";

  if(wstream.writeln4(filePath, testS)){cout << "Success" << endl;}*/

return 0;
}
