#include "InputStream1.h"
#include "OutputStream1.h"
#include "InputStream2.h"
#include "OutputStream2.h"
#include "InputStream3.h"
#include "OutputStream3.h"
#include "InputStream4.h"
#include "OutputStream4.h"


#include <chrono>

#include <iostream>

using namespace std;

/**
 * Return if there is at least one stream open in the given array
 * 
 * @param is    input streams
 * @param k     length of the array
 * 
 * @return  TRUE if at least one open, FALSE otherwise 
 */
bool areInputStreamsOpen(InputStream** is, int k) {
    for (int i = 0; i < k; i++){
        if (!is[i]->end_of_stream()){
            return true;
        }
    }
    return false;
}

/**
 * Get an outputstream with the given implementation
 * 
 * @param implementation    number of the implementation
 * 
 * @return outputstream of given implementation
 */ 
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
    case 4:
        result = new OutputStream4();
        break;

    default:
        cout << "Error" << endl;
        return NULL;
        break;
    }
    return result;
}


/**
 * Store in the given pointer an array of input streams of a given implementation with the given files already open
 * 
 * @param isList            pointer of the array of input streams
 * @param implementation    number of the implementation
 * @param fileList          array of files
 * @param length            length of the given list
 * 
 */ 
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
    case 4:
        for (int i = 0; i < length; i++) {
            isList[i] = new InputStream4();
            isList[i]->open(fileList[i]);
        }
        break;
    default:
        break;
    }
};


/**
 * Set the size of the input streams buffer
 * 
 * @param isList            array of input streams
 * @param implementation    number of the implementation
 * @param length            length of the list
 * @param bufferSize        new size of the buffer
 * 
 */ 
void setBufferSizeInputStreams(InputStream** isList, int implementation, int length, int bufferSize) {
    switch (implementation)
    {
    case 2:
        for (int i = 0; i < length; i++) {
            ((InputStream2*)isList[i])->setBufferSize(bufferSize);
        }
        break;
    case 3:
        for (int i = 0; i < length; i++) {
            ((InputStream3*)isList[i])->setBufferSize(bufferSize);
        }
        break;
    default:
        break;
    }
}

/**
 * Set the size of the output stream buffer
 * 
 * @param os                output stream
 * @param implementation    number of the implementation
 * @param bufferSize        new size of the buffer
 * 
 */ 
void setBufferSizeOutputStream(OutputStream* os, int implementation, int bufferSize) {
    switch (implementation)
    {
    case 3:
        ((OutputStream3*)os)->setBufferSize(bufferSize);
        break;
    }
}


/**
 * Merge files using a round-robin algorithm into a new file
 * 
 * @param fileList                      list of files
 * @param k                             number of files
 * @param inputStreamImplementation     number of the input stream
 * @param outputStreamImplementation    number of the output stream
 * @param outputFile                    path to the output file
 * @param bufferSize                    size of the buffers
 */ 
void rrmerge(string fileList[], int k, int inputStreamImplementation, int outputStreamImplementation, string outputFile, int bufferSize) {
    InputStream* is[k];
    getInputStreams(is, inputStreamImplementation, fileList, k);
    OutputStream* os = getOutputStream(outputStreamImplementation);
    if (bufferSize != -1) {
        setBufferSizeInputStreams(is, inputStreamImplementation, k, bufferSize);
        setBufferSizeOutputStream(os, outputStreamImplementation, bufferSize);
    }

    if (!os->create(outputFile)) {
        cout << "Error create" << endl;
        return;
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


/**
 * Merge files using a round-robin algorithm into a new file
 * 
 * @param fileList                      list of files
 * @param k                             number of files
 * @param inputStreamImplementation     number of the input stream
 * @param outputStreamImplementation    number of the output stream
 * @param outputFile                    path to the output file
 */ 
void rrmerge(string fileList[], int k, int inputStreamImplementation, int outputStreamImplementation, string outputFile) {
    rrmerge(fileList, k, inputStreamImplementation, outputStreamImplementation, outputFile, -1);
}

int main(int argc, char **argv){
    /* Arguments manager */
    int numberOfFiles = argc-1;
    string fileList[numberOfFiles];

    for (int i = 1; i < argc; i++) {
           fileList[i-1] = argv[i];
    }

    /* IO implementations */
    int numberOfInputImplementations = 4;
    int numberOfOutputImplementations = 4;
    int numberOfBuffers = 1;

    int inputImplementations[] = {1,2,3,4};
    int outputImplementations[] = {1,2,3,4};
    int bufferSizes[] = {4096};

    /* Setup times */
    chrono::time_point<chrono::system_clock> startTime;
    chrono::time_point<chrono::system_clock> endTime;
    int numberOfTimesMajor = numberOfInputImplementations*numberOfOutputImplementations*numberOfBuffers;
    double resultTimes[numberOfTimesMajor];
    int timeIndex = 0;
    string path;

    cout << "Start..0.." ;


    for (int i = 0; i < numberOfInputImplementations; i++) {
        for (int j = 0; j < numberOfOutputImplementations; j++) {
            if (inputImplementations[i] == 2 || inputImplementations[i] == 3 || outputImplementations[j] == 3) {
                for (int k = 0; k < numberOfBuffers; k++) {
                    path = "rrmergeRep/is_"+to_string(inputImplementations[i])+"_os_"+to_string(outputImplementations[j])+"_buffer_"+to_string(bufferSizes[k])+".txt";
                    startTime = chrono::system_clock::now();
                    rrmerge(fileList, numberOfFiles, inputImplementations[i], outputImplementations[j], path, bufferSizes[k]);
                    endTime = chrono::system_clock::now();
                    resultTimes[timeIndex] = ((double)(chrono::duration_cast<chrono::nanoseconds>(endTime-startTime).count()))/1000000;
                    timeIndex++;
                    cout << (100*timeIndex)/numberOfTimesMajor << "..";
                }
            } else {
                path = "rrmergeRep/is_"+to_string(inputImplementations[i])+"_os_"+to_string(outputImplementations[j])+".txt";
                startTime = chrono::system_clock::now();
                rrmerge(fileList, numberOfFiles, inputImplementations[i], outputImplementations[j], path);
                endTime = chrono::system_clock::now();
                resultTimes[timeIndex] = ((double)(chrono::duration_cast<chrono::nanoseconds>(endTime-startTime).count()))/1000000;
                timeIndex++;
                cout << (100*timeIndex)/numberOfTimesMajor << "..";
            }
        }
    }
    cout <<"End" << endl;

    /* Display results */
    
    timeIndex = 0;
    int minTimeIndex = 0;
    string result = "Best : IS"+to_string(inputImplementations[0])+", OS"+to_string(outputImplementations[0])+", Time :"+to_string(resultTimes[0])+"ms";


    for (int i = 0; i < numberOfInputImplementations; i++) {
        for (int j = 0; j < numberOfOutputImplementations; j++) {
            if (inputImplementations[i] == 2 || inputImplementations[i] == 3 || outputImplementations[j] == 3) {
                for (int k = 0; k < numberOfBuffers; k++) {
                    cout << "IS : " << inputImplementations[i] << ", OS : " << outputImplementations[j] << ", Buffer size : " << bufferSizes[k] << ", Time : " << resultTimes[timeIndex] << "ms"<< endl;
                    if (resultTimes[timeIndex] < resultTimes[minTimeIndex]) {
                        result = "Best : IS"+to_string(inputImplementations[i])+", OS"+to_string(outputImplementations[j])+", Buffer size :"+ to_string(bufferSizes[k])+", Time :"+to_string(resultTimes[timeIndex])+"ms";
                        minTimeIndex = timeIndex;
                    }
                    timeIndex++;
                }
            } else {
                cout << "IS : " << inputImplementations[i] << ", OS : " << outputImplementations[j] << ", Time : " << resultTimes[timeIndex] << "ms"<< endl;
                if (resultTimes[timeIndex] < resultTimes[minTimeIndex]) {
                    result = "Best : IS"+to_string(inputImplementations[i])+", OS"+to_string(outputImplementations[j])+", Time : "+to_string(resultTimes[timeIndex])+"ms";
                    minTimeIndex = timeIndex;
                }
                timeIndex++;
            }
        }
    }

    cout << result << endl;

    return 0;
}
