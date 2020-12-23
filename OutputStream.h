#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H

#include <string>

using namespace std;

class OutputStream {
    protected:
        long long int IOCounter = 0;

    public:
        OutputStream(void) {};
        ~OutputStream(void) {};
        virtual bool create(string path) = 0;
        virtual void close() = 0;
        virtual void writeln(string line) = 0;
        long long int getIOCounter();
};

#endif //PROJECT_OUTPUTSTREAM_H
