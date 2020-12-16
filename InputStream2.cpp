#include "InputStream2.h"


bool InputStream2::open(string path){
  if ((fd = fopen(path.c_str(), "r")) == NULL){
    perror("Open failed");
    return false;
  }
  return true;
}

void InputStream2::seek(int pos){
  fseek(fd, pos, SEEK_SET);
}

bool InputStream2::end_of_stream(){
  return feof(fd);
}

bool InputStream2::close(){
  return fclose(fd);
}

string InputStream2::readln(){
 string result = "";
 string tempRes = "";
 do {
   if (fgets(buffer, BUFFER_SIZE_IS_2+1, fd) == NULL){
     break;
   }
   tempRes = buffer;
   result += tempRes;
 } while (tempRes.size() == BUFFER_SIZE_IS_2 && buffer[BUFFER_SIZE_IS_2-1] != '\n');
 result = result.substr(0, result.size()-1);
 return result;
}
