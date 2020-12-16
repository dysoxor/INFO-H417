#include "InputStream1.h"
#include "OutputStream1.h"
#include "InputStream2.h"
#include "OutputStream2.h"
#include "InputStream3.h"
#include "OutputStream3.h"

#include <chrono>

#include <iostream>
using namespace std;

bool areInputStreamsOpen(InputStream** is, int k) {
    for (int i = 0; i < k; i++){
        if (!is[i]->end_of_stream()){
            return true;
        }
    }
    return false;
}

OutputStream* getOutputStream(int implementation) {
    OutputStream* result;
    switch (implementation)
    {
    case 1:
        result = new OutputStream1();
        break;
    case 2:
        result = new OutputStream2();
        break;
    case 3:
        result = new OutputStream3();
        break;
    
    default:
        cout << "Error" << endl;
        return NULL;
        break;
    }
    return result;
}

void getInputStreams(InputStream** isList, int implementation, string fileList[], int length) {
    switch (implementation)
    {
    case 1:
        for (int i = 0; i < length; i++) {
            isList[i] = new InputStream1();
            isList[i]->open(fileList[i]);
        }
        break;
    case 2:
        for (int i = 0; i < length; i++) {
            isList[i] = new InputStream2();
            isList[i]->open(fileList[i]);
        }
        break;
    case 3:
        for (int i = 0; i < length; i++) {
            isList[i] = new InputStream3();
            isList[i]->open(fileList[i]);
        }
        break;
    
    default:
        break;
    }
}; 





void rrmerge(string fileList[], int k, int inputStreamImplementation, int outputStreamImplementation, string outputFile) {
    InputStream* is[k];
    getInputStreams(is, inputStreamImplementation, fileList, k);
    OutputStream* os = getOutputStream(outputStreamImplementation);
    if (!os->create(outputFile)) {
        cout << "Error create" << endl;
    }
    string line;
    while (areInputStreamsOpen(is, k)) {
        for (int i = 0; i < k ; i++){
            if (is[i]->end_of_stream()) {
                continue;
            }
            line = is[i]->readln();
            if (line.size() > 0) {
                os->writeln(line);
            }
        }
    }
    for (int i = 0; i < k; i++){
        is[i]->close();
        delete is[i];
    }
    os->close();
    delete os;
};


int main(int argc, char **argv){
    /* Arguments manager */
    int numberOfFiles = argc-1;
    string fileList[numberOfFiles];

    for (int i = 1; i < argc; i++) {
           fileList[i-1] = argv[i];
    }

    /* Number of IO implementations */
    int numberOfImplementations = 3;

    /* Setup times */
    chrono::time_point<chrono::system_clock> startTime;
    chrono::time_point<chrono::system_clock> endTime;
    int numberOfTimes = numberOfImplementations*numberOfImplementations;
    double resultTimes[numberOfTimes];
    int timeIndex = 0;
    string path;

    cout << "Start..0.." ;
    
    for (int i = 1; i <= numberOfImplementations; i++) {
        for (int j = 1; j <= numberOfImplementations; j++) {
            path = "rrmerge/is_"+to_string(i)+"_os_"+to_string(j)+".txt";
            startTime = chrono::system_clock::now();
            rrmerge(fileList, numberOfFiles, i, j, path);
            endTime = chrono::system_clock::now();
            resultTimes[timeIndex] = (double)(chrono::duration_cast<chrono::microseconds>(endTime-startTime).count())/1000;
            timeIndex++;
            cout << (100*timeIndex)/numberOfTimes << "..";
        }
    }
    cout <<"End" << endl;

    timeIndex = 0;

    for (int i = 1; i <= numberOfImplementations; i++) {
        for (int j = 1; j <= numberOfImplementations; j++) {
            cout << "IS : " << i << ", OS : " << j << ", Time : " << resultTimes[timeIndex] << "ms"<< endl;
            timeIndex++;
        }
    }

    return 0;
}



