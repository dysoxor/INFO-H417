#include "OutputStream4.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
  string file = "../db/complete_cast.csv";
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
  return 0;
}