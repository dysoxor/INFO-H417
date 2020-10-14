#include <iostream>
using namespace std;

#include "InputStream.h"

int main()
{
  string filePath = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\aka_name.csv" ;
  InputStream stream;
  stream.readln4(filePath,0);

  /*cout << "Hello World! ";
  cout << "I'm a C++ program";*/
}
