#ifndef PROJECT_INPUTSTREAM2_H
#define PROJECT_INPUTSTREAM2_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#define BUFFER_SIZE 10

using namespace std;

class InputStream2
{
private:
    FILE *fd;

public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();

    string readln();
};

#endif //PROJECT_INPUTSTREAM2_H
