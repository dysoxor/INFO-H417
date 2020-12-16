#ifndef PROJECT_OUTPUTSTREAM1_H
#define PROJECT_OUTPUTSTREAM1_H

#include "OutputStream.h"

#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <sys/stat.h>



using namespace std;

class OutputStream1 : public OutputStream
{
private:
    int fd;
public:
    bool create(string path);
    void close();
    void writeln(string line);
};



#endif //PROJECT_OUTPUTSTREAM1_H
