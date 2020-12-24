#include "InputStream2.h"
#include "OutputStream2.h"

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

struct element{ //This struct represent a line in the sorting algorithm
  char letter; //The letter on which we sort the line
  int number; //The line number
};

bool compareTwoElemementNumber(element a, element b){
  return (a.letter < b.letter);
}

void sortElements(element* elementLine, int numberOfLine){
  std::sort(elementLine, elementLine+numberOfLine,compareTwoElemementNumber);
}

string getLineNumber(char* data, int positionChar ,int number){
  string line = "";
  int lineCounter = 0;
  int pos = 0;
  while(lineCounter <=number && pos<=positionChar){
    char charTest = *(data+pos);
    if(number == lineCounter){line += charTest;}
    if( charTest == '\n'){++lineCounter;}
    ++pos;
  }
  if(line[line.size()-1] == '\n'){line = line.substr(0, line.size() - 1);} // Because writeln already add the \n
  return line;
}

bool writeIntoFile(char* data, element* elementLine, int numberLine, int positionChar, string fileName){
  OutputStream2 outs;
  element el;
  if(!outs.create(fileName)){std::cout << "Error in creating the file to write" << endl; return false;}
  for(int i=0; i<numberLine;++i){
    el = *(elementLine+i);
    outs.writeln(getLineNumber( data, positionChar, el.number));
  }
  outs.close();
  return true;
}

bool sort(string f, int k, int m )
{
  InputStream2 is;
  if(!is.open(f)){return false;}
  char* data = new char[m]; //Create a buffer with the max size possible
  element* elementLine = new element[m];
  string line = "";
  int positionChar = 0;
  int numberOfLine = 0;
  int fileNumber = 0;
  long long int positionInFile = 0;
  long long int numberOfLineTotal = 0;
  long long int fileSize = is.getSize();
  bool alreadyChecked = false; // Need it to avoid writing two times the same file
  is.seek(0);
  do{
    line = is.readln();
    if( (positionChar+line.size()-1) >= m){
      string fileName = "result\\sort\\" + to_string(fileNumber) + ".txt";
      ++fileNumber;
      sortElements(elementLine,numberOfLine);
      if(!writeIntoFile(data, elementLine, numberOfLine, positionChar,fileName)){return false;}
      delete data;
      delete elementLine;
      data = new char[m];
      elementLine = new element[m];
      alreadyChecked = true;
      positionChar = 0;
      numberOfLine = 0;
    }

    for(int i=0; i<line.size();++i){
      *(data+positionChar) = line[i];
      ++positionChar;
      ++positionInFile;
    }
    //We fill the struct representing this line
    element test;
    test.letter = line[k];
    test.number = numberOfLine;
    *(elementLine+numberOfLine) = test;
    ++numberOfLine;
    ++numberOfLineTotal;

    if(positionInFile+numberOfLineTotal >= fileSize && !alreadyChecked){
      string fileName = "result\\sort\\" + to_string(fileNumber) + ".txt";
      ++fileNumber;
      sortElements(elementLine,numberOfLine);
      if(!writeIntoFile(data, elementLine, numberOfLine, positionChar,fileName)){return false;}
      break;
    }
    alreadyChecked = false;
  }while(!is.end_of_stream());

  is.close();
  delete data;
  delete elementLine;
  data = NULL;
  elementLine = NULL;
  return true;
}

int main(int argc, char **argv)
{
  string file = "D:\\ulb\\MA1\\DatabaseProject\\imdb\\movie_link.csv";
  int bufferSize = 1024;
  int sortColumn = 4;
  if(!sort(file,sortColumn,bufferSize)){std::cout << "Error in sorting the file : " << file << endl;};
  return 0;
}
