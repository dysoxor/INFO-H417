
#include "OutputStream1.h"

#include <iostream>

using namespace std;

bool OutputStream1::create(string path){
    if ((fd = _open(path.c_str(), O_CREAT|O_WRONLY|O_TRUNC, _S_IREAD | _S_IWRITE )) <= 0){
        perror("Open failed");
        return false;
    }
    return true;
}

void OutputStream1::writeln(string text){
    text+='\n';
    for (int i = 0; i < text.size(); i++){
         _write(fd, &text.at(i), sizeof(char));
    }
}

void OutputStream1::close(){
    _close(fd);
}