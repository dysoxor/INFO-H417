#ifndef PROJECT_OUTPUTSTREAM2_H
#define PROJECT_OUTPUTSTREAM2_H

#include "OutputStream.h"


#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>


using namespace std;

class OutputStream2 : public OutputStream
{
private:
    FILE* fd;
public:
    bool create(string path);
    void close();
    void writeln(string line);
};



#endif //PROJECT_OUTPUTSTREAM2_H
