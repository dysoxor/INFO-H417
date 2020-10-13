#include "OutputStream.h"

FILE* outputFile;

void create(const char* path){
    outputFile = fopen(path, "w");
}

void close(){
    fclose(outputFile);
}

void writeln1(const char* line){
    int index = 0;
    while (line[index] != '\0') {
        write(outputFile, &line[index], sizeof(char));
    }
}
void writeln2(const char* line){
    fputs(line,outputFile);
}