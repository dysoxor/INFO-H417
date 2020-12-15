#include "InputStream3.h"
#include "OutputStream3.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  InputStream3 is;
  string path = "C:\\Users\\Andre\\Documents\\imdb\\movie_link.csv";
  if (!is.open(path))
  {
    return 0;
  }
  cout << is.readln() << endl;

  is.close();

  OutputStream3 os;
  if (!os.create("testF2.txt"))
  {
    return 0;
  }
  os.writeln("bonsoir je suis Andrey et je fais de superbes projets de database yeay, alo? je suis dans un tunnel.....");
  os.writeln("crrrrr");
  os.close();
}