#include "InputStream1.h"
#include "InputStream2.h"
#include "InputStream3.h"
#include "InputStream4.h"
#include <iostream>
#include <chrono>
using namespace std;

void freeStreamPointer(InputStream *is)
{
  delete is;
  is = NULL;
}

double length(string f, unsigned int streamId)
{

  InputStream *is;

  switch (streamId)
  {
  case 1:
    is = new InputStream1();
    break;

  case 2:
    is = new InputStream2();
    break;

  case 3:
    is = new InputStream3();
    break;

  case 4:
    is = new InputStream4();
    break;

  default:
    std::cout << "Error implementation id not valid" << endl;
    return 0;
    break;
  }

  double result = 0.0;
  long long int sum = 0;
  string line = "";
  if (is->open(f))
  {
    auto start = chrono::steady_clock::now();

    while (!is->end_of_stream())
    {
      line = is->readln();
      sum += line.length();
    }
    is->close();

    auto end = chrono::steady_clock::now();
    result = (double)(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000;
  }
  else
  {
    freeStreamPointer(is);
    std::cout << "Error couldn t open the file : " << f << " with the InputStream" << streamId << endl;
    return 0;
  }

  freeStreamPointer(is);
  std::cout << "Implementation num" << streamId << " Sum total : " << sum << endl;
  return result;
}

void readFileMultipleTimes(string f, int numberOfTimes, string resultStreamPath)
{

  double resultList[numberOfTimes * 4];

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < numberOfTimes; ++j)
    {
      resultList[i * numberOfTimes + j] = length(f, i + 1);
    }
  }

  ofstream resultStream;
  resultStream.open(resultStreamPath);
  double resultMean = 0.0;
  for (int i = 0; i < 4; ++i)
  {
    resultMean = 0.0;
    for (int j = 0; j < numberOfTimes; ++j)
    {
      resultMean += resultList[i * numberOfTimes + j];
    }
    resultMean = resultMean / numberOfTimes;
    resultStream << "Mean time (in ms) for implementation " + to_string(i + 1) + " : " + to_string(resultMean) + '\n';
  }
  resultStream.close();
}

int main(int argc, char **argv)
{
  //string f = "C:\\Users\\Asus ROG\\Documents\\ulb\\MA1\\DatabaseProject\\imdb\\keyword.csv";
  string f = "C:\\Users\\Andre\\Documents\\imdb\\complete_cast.csv";
  string resultFile = "result\\resultExp1.txt";
  unsigned int numberOfRun = 4;
  readFileMultipleTimes(f, numberOfRun, resultFile);
}
