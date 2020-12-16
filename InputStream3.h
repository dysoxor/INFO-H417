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

#define BUFFER_SIZE_IS_3 1024

class InputStream3 : public InputStream
{
private:
    int fd;
    char *buffer = new char[BUFFER_SIZE_IS_3 * sizeof(char)];
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

#endif //PROJECT_INPUTSTREAM3_H
