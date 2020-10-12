#include "InputStream.h"


ifstream inputFile;


void open(string path){
    inputFile.open(path);
    //Gérer les exceptions ici
}

void seek(int pos){
    inputFile.seekg(pos);
}

bool end_of_stream(){
  return inputFile.eof();
}
