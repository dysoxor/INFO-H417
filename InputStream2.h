#ifndef PROJECT_INPUTSTREAM2_H
#define PROJECT_INPUTSTREAM2_H

#include "InputStream.h"

#include <stdio.h>
#include <stdlib.h>



#define BUFFER_SIZE_IS_2 10

using namespace std;

class InputStream2 : public InputStream
{
private:
    FILE *fd;
    char buffer[BUFFER_SIZE_IS_2];
public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();

    string readln();
};

#endif //PROJECT_INPUTSTREAM2_H
