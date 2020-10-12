#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void open(string path);
string readln();
void seek(int pos);
bool end_of_stream();

#endif //PROJECT_INPUTSTREAM_H
