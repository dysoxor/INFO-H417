#include "InputStream2.h"
#include "OutputStream2.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  /*InputStream2 is;
  string path = "C:\\Users\\Franck\\Desktop\\ULB\\MA1\\Database systems architecture\\Projet\\Database\\movie_link.csv";

  if (!is.open(path)){
    return 0;
  }


  while (!is.end_of_stream()){
    cout << is.readln();
  }

  is.close();*/
  
 OutputStream2 os;

 if (!os.create("testF2.txt")){
   return 0;
 }

 os.writeln("Hello Franck");
 os.writeln("Hello World");

 os.close();


}