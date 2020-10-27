#include "InputStream2.h"

bool InputStream2::open(string path){
  if ((fd = fopen(path.c_str(), "r")) == NULL){
    perror("Open failed");
    return false;
  }
  return true;
}

void InputStream2::seek(int pos){
  fseek(fd,pos, SEEK_SET);
}

bool InputStream2::end_of_stream(){
  return feof(fd);
}

bool InputStream2::close(){
  return fclose(fd);
}

string InputStream2::readln(){
 
 char buffer[BUFFER_SIZE];
 string result = "";
 string tempRes = "";
 do {
   if (fgets(buffer, BUFFER_SIZE*sizeof(char), fd) == NULL){
     break;
   }
   tempRes = buffer;
   result += tempRes;
 } while (tempRes.size() == BUFFER_SIZE);
 return result;
}