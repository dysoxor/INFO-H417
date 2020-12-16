#include "experiment1.h"

void Experiment1::length1(string f){
  long long int sum = 0;
  InputStream1 is1;
  int counter = 0;
  string line = "";
  if(is1.open(f)){
    while (!is1.end_of_stream()) {
      line = is1.readln();
      sum += line.length();
      counter +=1;
      if(counter < 10 ) {cout << " Lines :" << counter << " : " << line  << endl;}
    }
    is1.close();
    cout << " Length1 :" << sum << endl;
  }
  else{std::cout << "Error couldn t open the file (length1) : " << f << endl; return;}
}

void Experiment1::length2(string f){
  long long int sum = 0;
  InputStream2 is2;
  int counter = 0;
  string line = "";
  if(is2.open(f)){
    while (!is2.end_of_stream()) {
      line = is2.readln();
      sum += line.length();
      counter +=1;
      if(counter < 10 ) {cout << " Lines :" << counter << " : " << line  << endl;}
    }
    is2.close();
    cout << " Length2 :" << sum <<  endl;
  }
  else{std::cout << "Error couldn t open the file (length2) : " << f << endl;}
}

void Experiment1::length3(string f){
  long long int sum = 0;
  InputStream3 is3;
  int counter = 0;
  string line = "";
  if(is3.open(f)){
    while (!is3.end_of_stream()) {
      line = is3.readln();
      sum += line.length();
      counter +=1;
      if(counter < 10 ) {cout << " Lines :" << counter << " : " << line  << endl;}
    }
    is3.close();
    cout << " Length3 :" << sum << endl;
  }
  else{std::cout << "Error couldn t open the file (length3) : " << f << endl;}
}

void Experiment1::length4(string f){
  long long int sum = 0;
  InputStream4 is4;
  int counter = 0;
  string line = "";
  is4.open(f);
  while (!is4.end_of_stream()) {
    line = is4.readln();
    sum += line.length();
    counter +=1;
    if(counter < 10 ) {cout << " Lines :" << counter << " : " << line  << endl;}
  }
    is4.close();
    cout << " Length4 :" << sum << endl;
}
