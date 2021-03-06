#ifndef PROJECT_INPUTSTREAM3_H
#define PROJECT_INPUTSTREAM3_H

#include "InputStream.h"

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

class InputStream3 : public InputStream
{
private:
    int fd;
    char *buffer;
    int position;
    int bufferFill;
    long long int offset;
    const int DEFAULT_BUFFER_SIZE = 4096;
    int bufferSize;
    long long int size;

public:
    InputStream3();
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();

    long long int getSize();
    void setBufferSize(int size);
    int getBufferSize();
    string readln();
};

#endif //PROJECT_INPUTSTREAM3_H
