#ifndef PROJECT_INPUTSTREAM2_H
#define PROJECT_INPUTSTREAM2_H

#include "InputStream.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class InputStream2 : public InputStream
{
private:
    FILE *fd;
    int bufferSize;
    const int DEFAULT_BUFFER_SIZE = 1024;
    char *buffer;
    string file;

public:
    InputStream2();
    ~InputStream2();
    bool open(string path);
    bool open();
    void seek(int pos);
    bool end_of_stream();
    bool close();
    void setBufferSize(int size);
    long long int getSize();
    int getBufferSize();
    string readln();
    void setFile(string f);
};

#endif //PROJECT_INPUTSTREAM2_H
