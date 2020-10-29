#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 1024

class OutputStream3
{
private:
    int fd;
    char *buffer = new char[BUFFER_SIZE * sizeof(char)];
    int index;

public:
    bool create(string path);
    void close();

    void writeln(string line);
};

#endif //PROJECT_OUTPUTSTREAM_H
