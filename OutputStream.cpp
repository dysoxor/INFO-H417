#include "OutputStream.h"

ofstream outputFile;

void create(string path){
    outputFile.open(path);
}

void close(){
    outputFile.close();
}