#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
using namespace std;


void open(const char* path);
void seek(int pos);
bool end_of_stream();

string readln1();
string readln2();

#endif //PROJECT_INPUTSTREAM_H
