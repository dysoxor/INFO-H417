#ifndef PROJECT_INPUTSTREAM1_H
#define PROJECT_INPUTSTREAM1_H

#include "InputStream.h"

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <fcntl.h>

using namespace std;

class InputStream1 : public InputStream
{
private:
    int fd;
    long long int size;

public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();
    long long int getSize();
    string readln();
};

#endif //PROJECT_INPUTSTREAM1_H
