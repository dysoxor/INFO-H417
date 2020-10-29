#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <fcntl.h>
#include <string>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 1024

class InputStream3
{
private:
    int fd;
    char *buffer = new char[BUFFER_SIZE * sizeof(char)];
    int index;

public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();
    int getIndex();

    void readln();
};

#endif //PROJECT_INPUTSTREAM_H
