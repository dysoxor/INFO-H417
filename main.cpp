#include "OutputStream4.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  string f = "test_write.txt";
  OutputStream4 outs;
  if(outs.create(f)){
    for(int i=0; i<10000;++i){
      outs.writeln("Test de write ln");
    }
    outs.close();
  }

}
