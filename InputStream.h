#ifndef PROJECT_INPUTSTREAM_H
#define PROJECT_INPUTSTREAM_H

#include <string>

using namespace std;

class InputStream
{
public:
    InputStream(void){};
    ~InputStream(void){};
    virtual bool open(string path) = 0;
    virtual void seek(int pos) = 0;
    virtual bool end_of_stream() = 0;
    virtual bool close() = 0;
    virtual string readln() = 0;
    virtual long long int getSize() = 0;
};

#endif //PROJECT_INPUTSTREAM_H