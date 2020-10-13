#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H


#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
using namespace std;

void create(const char* path);
void close();

void writeln1(const char* line);
void writeln2(const char* line);

#endif //PROJECT_OUTPUTSTREAM_H
