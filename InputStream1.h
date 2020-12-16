#ifndef PROJECT_INPUTSTREAM1_H
#define PROJECT_INPUTSTREAM1_H

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <fcntl.h>
#include <string>

using namespace std;

class InputStream1
{
private:
    int fd;
public:
    bool open(string path);
    void seek(int pos);
    bool end_of_stream();
    bool close();

    string readln();
};





#endif //PROJECT_INPUTSTREAM1s_H
