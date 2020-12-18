#ifndef PROJECT_OUTPUTSTREAM_H
#define PROJECT_OUTPUTSTREAM_H

#include <string>

using namespace std;

class OutputStream {
    public:
        OutputStream(void) {};
        ~OutputStream(void) {};
        virtual bool create(string path) = 0;
        virtual void close() = 0;
        virtual void writeln(string line) = 0;
};

#endif //PROJECT_OUTPUTSTREAM_H
