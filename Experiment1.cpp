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

/**
* This function is called when a run on a certain implementation and with a specific file is needed. This function use the chrono
* library to calculate the execution time.
* @param string f      the name of the file on which the run will be done
* @param int streamId  the number if the implementation to test (1,2,3,4)
* @return	a double corresponding to the execution time
*/
double readImplementId(string f, unsigned int streamId)
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

/**
* First implementation of the length function which is used to test all the 4 implementation on the file for
* a specific numbers of runs and write it to a result file.
* @param string f                the path to the test file
* @param int numberOfTimes       the number of runs for each implementation
* @param string resultStreamPath the path to the result file in which this function will write
*/
void length0(string f, int numberOfTimes, string resultStreamPath)
{

  double resultList[numberOfTimes * 4];

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < numberOfTimes; ++j)
    {
      resultList[i * numberOfTimes + j] = readImplementId(f, i + 1);
    }
  }
  ofstream resultStream;
  resultStream.open(resultStreamPath);
  resultStream << "Number of runs : " << numberOfTimes << endl;
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

/**
* Second implementation of the length function but here it tests only the implementation 3 and 4 in order to see the impact of the paramaters
* of this two methods on the execution time. The parameters of the two implementation are modified manualy between each call of this function.
* @param string f                the path to the test file
* @param int numberOfTimes       the number of runs for each implementation
* @param string resultStreamPath the path to the result file in which this function will write
*/
void length3_4(string f, int numberOfTimes, string resultStreamPath)
{

  double resultList[numberOfTimes * 2];

  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < numberOfTimes; ++j)
    {
      resultList[i * numberOfTimes + j] = readImplementId(f, i + 3);
    }
  }

  ofstream resultStream;
  resultStream.open(resultStreamPath);
  resultStream << "Number of runs : " << numberOfTimes << endl;
  double resultMean = 0.0;
  for (int i = 0; i < 2; ++i)
  {
    resultMean = 0.0;
    for (int j = 0; j < numberOfTimes; ++j)
    {
      resultMean += resultList[i * numberOfTimes + j];
    }
    resultMean = resultMean / numberOfTimes;
    resultStream << "Mean time (in ms) for implementation " + to_string(i + 3) + " : " + to_string(resultMean) + '\n';
  }
  resultStream.close();
}

int main(int argc, char **argv)
{
  string inputFile = argv[1];
  string fileName = inputFile.substr(inputFile.find_last_of("/\\")+1);
  fileName = fileName.substr(0,fileName.find_last_of("."));
  string resultFile = "result\\" + fileName + "_resultExp1_length.txt";
  unsigned int numberOfRun = 4; //The number of successive runs, the result will be the mean of the results of those runs.
  length0(inputFile, numberOfRun, resultFile); //The method to call between the two possible
  //length3_4(f,numberOfRun,resultFile);
}
