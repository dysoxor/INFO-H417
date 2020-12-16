#include "experiment1.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\complete_cast.csv";
  //string f = "test.txt";
  Experiment1 exp1;
  exp1.length1(f);
  exp1.length2(f);
  exp1.length3(f);
  exp1.length4(f);
}
