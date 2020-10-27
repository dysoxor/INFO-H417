#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <io.h>
#include <direct.h>
#include <fcntl.h>

using namespace std;

class OutputStream2
{
private:
    FILE* fd;
public:
    bool create(string path);
    void close();

    void writeln(string line);
};



#endif //PROJECT_OUTPUTSTREAM_H
