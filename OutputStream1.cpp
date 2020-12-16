
#include "OutputStream1.h"

bool OutputStream1::create(string path){
    if ((fd = _open(path.c_str(), _O_RDWR | _O_CREAT | _O_TRUNC)) < 0){
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