#include "InputStream1.h"
#include "InputStream2.h"
#include "InputStream3.h"
#include "InputStream4.h"
#include <iostream>
using namespace std;

void length1(string f){
  long long int sum = 0;
  InputStream1 is1;
  string line = "";
  if(is1.open(f)){
    while (!is1.end_of_stream()) {
      line = is1.readln();
      sum += line.length();
      
    }
    is1.close();
    cout << " Length1 :" << sum <<  endl;
  }
  else{std::cout << "Error couldn t open the file (length1) : " << f << endl; return;}
}

void length2(string f){
  long long int sum = 0;
  InputStream2 is2;
  string line = "";
  if(is2.open(f)){
    while (!is2.end_of_stream()) {
      line = is2.readln();
      sum += line.length();
    }
    is2.close();
    cout << " Length2 :" << sum <<  endl;
  }
  else{std::cout << "Error couldn t open the file (length2) : " << f << endl;}
}

void length3(string f){
  long long int sum = 0;
  InputStream3 is3;
  string line = "";
  if(is3.open(f)){
    while (!is3.end_of_stream()) {
      line = is3.readln();
      sum += line.length();
    }
    is3.close();
    cout << " Length3 :" << sum << endl;
  }
  else{std::cout << "Error couldn t open the file (length3) : " << f << endl;}
}

void length4(string f){
  long long int sum = 0;
  InputStream4 is4;
  string line = "";
  if(is4.open(f)){
  while (!is4.end_of_stream()) {
    line = is4.readln();
    sum += line.length();
  }
    is4.close();
    cout << " Length4 :" << sum << endl;
  }
  else{std::cout << "Error couldn t open the file (length4) : " << f << endl;}
}

int main(int argc, char **argv)
{
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\complete_cast.csv";
  //string f = "test.txt";
  length1(f);
  length2(f);
  length3(f);
  length4(f);
}
