#ifndef PROJECT_OUTPUTSTREAM3_H
#define PROJECT_OUTPUTSTREAM3_H

#include "OutputStream.h"


#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <iostream>


using namespace std;

class OutputStream3 : public OutputStream
{
private:
    int fd;
    char* buffer;
    const int DEFAULT_BUFFER_SIZE = 20;
    int bufferSize;
    int index;
    void write(string line);

public:
    OutputStream3();
    bool create(string path);
    void close();
    void writeln(string line);
    void setBufferSize(int size);
};

#endif //PROJECT_OUTPUTSTREAM3_H
