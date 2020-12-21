#include "InputStream2.h"
#include "OutputStream4.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
  string file = "../db/complete_cast.csv";
  string writeFile = "test.txt";
  InputStream2 is;
  OutputStream4 outs;
  if(is.open(file) && outs.create(writeFile)){
    string line = "";
  while(!is.end_of_stream()){
    line = is.readln();
    outs.writeln(line);
  }
  is.close();
  outs.close();
  }
  else{std::cout << "Cannot open the file" << '\n';}

  return 0;
}
