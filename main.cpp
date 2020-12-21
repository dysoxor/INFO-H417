#include "InputStream4.h"
#include "OutputStream4.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
  string file = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  string writeFile = "test.txt";
  InputStream4 is;
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
