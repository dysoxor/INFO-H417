
#include "OutputStream2.h"

bool OutputStream2::create(string path){
    if ((fd = fopen(path.c_str(), "w")) == NULL){
        perror("Open failed");
        return false;
    }
    return true;
}

void OutputStream2::writeln(string text){
    text+='\n';
    fputs(text.c_str(), fd);
    IOCounter++;
}

void OutputStream2::close(){
    fclose(fd);
}