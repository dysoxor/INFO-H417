#include "InputStream3.h"
#include "InputStream4.h"
#include <chrono>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\aka_name.csv";
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\complete_cast.csv";
  InputStream3 is;
  double result = 0.0;
  long long int sum = 0;
  string line = "";
  if(is.open(f)){
    auto start = chrono::steady_clock::now();

    while (!is.end_of_stream()) {
      line = is.readln();
      sum += line.length();
    }
    is.close();

    auto end = chrono::steady_clock::now();
    result = (double) (chrono::duration_cast<chrono::microseconds>(end-start).count())/1000;
    std::cout << "Result time : " << result <<endl;
  }

}
