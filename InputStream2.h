#ifndef PROJECT_INPUTSTREAM2_H
#define PROJECT_INPUTSTREAM2_H

#include "InputStream.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class InputStream2 : public InputStream
{
private:
    FILE *fd;
    int bufferSize;
    const int DEFAULT_BUFFER_SIZE = 4096;
    char *buffer;
    long long int size;

public:
    InputStream2();
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();
    void setBufferSize(int size);
    long long int getSize();
    int getBufferSize();
    string readln();
};

#endif //PROJECT_INPUTSTREAM2_H
