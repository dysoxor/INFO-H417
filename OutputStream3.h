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

#define BUFFER_SIZE_OS_3 1024

class OutputStream3 : public OutputStream
{
private:
    int fd;
    char *buffer = new char[BUFFER_SIZE_OS_3 * sizeof(char)];
    int index;
    void write(string line);

public:
    bool create(string path);
    void close();
    void writeln(string line);
};

#endif //PROJECT_OUTPUTSTREAM3_H
