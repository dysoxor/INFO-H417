#include "InputStream.h"


FILE* inputFile;


void open(const char* path){
    //inputFile = fopen(path,"r");
    int fh;
    //Gérer les exceptions ici
}

void seek(int pos){
    fseek(inputFile, pos, SEEK_SET);
}

bool end_of_stream(){
  return feof(inputFile);
}

string readln1(){
  string result = "";
  char c;
  do {
    _read(inputFile,&c,sizeof(char));
    result+=c;
    cout <<c;
  } while (c != '\n' && !end_of_stream());
  return result;
}

string readln2(){
    char line[100];
    return fgets(line,100,inputFile);
}