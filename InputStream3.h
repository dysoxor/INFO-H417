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

#define BUFFER_SIZE_3 20

class InputStream3
{
private:
    int fd;
    char *buffer = new char[BUFFER_SIZE_3 * sizeof(char)];
    int position;
    int size;
    int offset;

public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();

    string readln();
};

#endif //PROJECT_INPUTSTREAM_H
