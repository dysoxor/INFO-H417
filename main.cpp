#include "OutputStream4.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\complete_cast.csv";
  string f = "test.txt";
  OutputStream4 outs;
  if(outs.create(f)){
    string test = "Hello j ecris\n";
    outs.writeln(test);
    outs.close();
  }
  else{std::cout << "Error opening" << '\n';}

}
