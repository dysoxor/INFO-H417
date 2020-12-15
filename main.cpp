#include <iostream>
using namespace std;

#include "InputStream4.h"
#include "OutputStream4.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\test1.txt" ;

  //Read sequentially
  /*InputStream4 rstream;
  string text = "";
  rstream.open(filePath); // Error in opening the files
  do {
    text = rstream.readln();
    std::cout << text << std::endl;
  } while(!rstream.end_of_stream());

  std::cout << std::endl;
  rstream.close();*/

  //Write to a file
  OutputStream4 wstream;
  wstream.create(filePath);
  string testS = "Test of write function et voir si le saut de ligne fct\n";

  if(wstream.writeln(testS)){cout << "Success" << endl;}
  if(wstream.writeln(testS)){cout << "Success" << endl;}
  if(wstream.writeln(testS)){cout << "Success" << endl;}
  wstream.close();

return 0;
}
