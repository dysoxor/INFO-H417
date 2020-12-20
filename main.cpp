#include "OutputStream4.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
  string file = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  std::ifstream fs( file );
  OutputStream4 outs;
  if(outs.create("test.txt")){
  for( std::string line; getline( fs, line ); )
  {
    outs.writeln(line);
  }
  outs.close();
  }
  fs.close();

  std::ifstream fs1( file );
  OutputStream4 outs1;
  if(outs1.create("test1.txt")){
  for( std::string line; getline( fs1, line ); )
  {
    outs1.writeln(line);
  }
  outs1.close();
  }
  fs1.close();

  return 0;
}
