#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>

#include "InputStream2.h"
#include "OutputStream2.h"

using namespace std;

struct element
{                //This struct represent a line in the sorting algorithm
    char letter; //The letter on which we sort the line
    int number;  //The line number
};

bool compareTwoElemementNumber(element a, element b)
{
    return (a.letter < b.letter);
}

void sortElements(element *elementLine, int numberOfLine)
{
    std::sort(elementLine, elementLine + numberOfLine, compareTwoElemementNumber);
}

string getLineNumber(char *data, int positionChar, int number)
{
    string line = "";
    int lineCounter = 0;
    int pos = 0;
    while (lineCounter <= number && pos <= positionChar)
    {
        char charTest = *(data + pos);
        if (number == lineCounter)
        {
            line += charTest;
        }
        if (charTest == '\n')
        {
            ++lineCounter;
        }
        ++pos;
    }
    if (line[line.size() - 1] == '\n')
    {
        line = line.substr(0, line.size() - 1);
    } // Because writeln already add the \n
    return line;
}

bool writeIntoFile(char *data, element *elementLine, int numberLine, int positionChar, string fileName)
{
    OutputStream2 outs;
    element el;
    if (!outs.create(fileName))
    {
        std::cout << "Error in creating the file to write" << endl;
        return false;
    }
    for (int i = 0; i < numberLine; ++i)
    {
        el = *(elementLine + i);
        outs.writeln(getLineNumber(data, positionChar, el.number));
    }
    outs.close();
    return true;
}

int sort(string f, int k, int m)
{
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;
    InputStream2 is;
    if (!is.open(f))
    {
        return -1;
    }
    char *data = new char[m]; //Create a buffer with the max size possible
    element *elementLine = new element[m];
    string line = "";
    int positionChar = 0;
    int numberOfLine = 0;
    int fileNumber = 0;
    long long int positionInFile = 0;
    long long int numberOfLineTotal = 0;
    long long int fileSize = is.getSize();
    bool alreadyChecked = false; // Need it to avoid writing two times the same file
    startTime = chrono::high_resolution_clock::now();
    do
    {
        line = is.readln() + "\n";

        if ((positionChar + line.size()) >= m)
        {
            string fileName = "result\\sort\\" + to_string(fileNumber) + ".txt";
            ++fileNumber;
            sortElements(elementLine, numberOfLine);
            if (!writeIntoFile(data, elementLine, numberOfLine, positionChar, fileName))
            {
                return -1;
            }
            delete data;
            delete elementLine;
            data = new char[m];
            elementLine = new element[m];
            alreadyChecked = true;
            positionChar = 0;
            numberOfLine = 0;
        }

        for (int i = 0; i < line.size(); ++i)
        {
            *(data + positionChar) = line[i];
            ++positionChar;
            ++positionInFile;
        }
        //We fill the struct representing this line
        element test;
        test.letter = line[k];
        test.number = numberOfLine;
        *(elementLine + numberOfLine) = test;
        ++numberOfLine;
        ++numberOfLineTotal;

        if (positionInFile >= fileSize && !alreadyChecked)
        {
            string fileName = "result\\sort\\" + to_string(fileNumber) + ".txt";
            ++fileNumber;
            sortElements(elementLine, numberOfLine);
            if (!writeIntoFile(data, elementLine, numberOfLine, positionChar, fileName))
            {
                return -1;
            }
            break;
        }
        alreadyChecked = false;
    } while (!is.end_of_stream());
    endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> resultTimes = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    cout << "sorting time: " << resultTimes.count() << "s" << endl;
    is.close();
    delete data;
    delete elementLine;
    data = NULL;
    elementLine = NULL;
    return fileNumber;
}

bool isEmpty(string l[], int d)
{
    for (int i = 0; i < d; i++)
    {
        if (!l[i].empty())
        {
            return false;
        }
    }

    return true;
}

bool merge(int files, int d, int k)
{
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;
    vector<InputStream2 *> is;
    string lines[d];
    vector<InputStream2 *>::iterator ptr;
    int pos = 0;
    int counter = 0;
    string prefixSorted = "result\\sort\\";
    string prefixMerged = "result\\merge\\";
    for (int i = 0; i < files; i++)
    {
        is.push_back(new InputStream2());
        is.at(i)->setFile(prefixSorted + to_string(i) + ".txt");
    }
    OutputStream2 *os = new OutputStream2();
    startTime = chrono::high_resolution_clock::now();
    while (is.size() > 1)
    {
        ptr = is.begin();
        advance(ptr, pos);
        int round = min(d, (int)is.size());
        for (int i = 0; i < round; i++)
        {
            if (!((*ptr)->open()))
            {
                cerr << "Could not open on reading file" << endl;
                return false;
            }
            if (!((*ptr)->end_of_stream()))
            {
                lines[i] = (*ptr)->readln();
            }
            else
            {
                lines[i] = "";
            }
            if (pos + i == is.size() - 1)
            {
                ptr = is.begin();
            }
            else
            {
                advance(ptr, 1);
            }
        }
        if (!os->create(prefixMerged + to_string(counter) + ".txt"))
        {
            cerr << "Error create" << endl;
            return false;
        }

        int best;
        int ptrBest;
        while (!isEmpty(lines, round))
        {
            ptr = is.begin();
            advance(ptr, pos);
            best = 99999;
            ptrBest = 0;
            for (int i = 0; i < round; i++)
            {
                if (lines[i].compare("") != 0 && (int)lines[i][k] < best)
                {
                    ptrBest = i;
                    best = (int)lines[i][k];
                }
            }
            os->writeln(lines[ptrBest]);
            ptr = is.begin();
            advance(ptr, (pos + ptrBest) % is.size());
            if (!(*ptr)->end_of_stream())
            {
                lines[ptrBest] = (*ptr)->readln();
            }
            else
            {
                lines[ptrBest] = "";
            }
        }
        ptr = is.begin();
        advance(ptr, pos);
        for (int i = 0; i < round - 1; i++)
        {
            (*ptr)->close();
            //delete (*ptr);
            is.erase(ptr);
            if (pos >= is.size())
            {
                pos = 0;
            }
            ptr = is.begin();
            advance(ptr, pos);
        }
        (*ptr)->close();
        os->close();
        (*ptr)->setFile(prefixMerged + to_string(counter) + ".txt");
        counter++;
        int posl = pos;
        pos = (pos + 1) % is.size();
    }
    endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> resultTimes = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    cout << "merging time: " << resultTimes.count() << "s" << endl;
    ptr = is.begin();
    (*ptr)->close();
    is.erase(ptr);
    delete os;
    return true;
}

int main(int argc, char **argv)
{
    string f = argv[1];
    int k = atoi(argv[2]);
    int M = atoi(argv[3]);
    int d = atoi(argv[4]);

    if (M < 0)
    {
        cerr << "Parameter M should be positive" << endl;
        return 1;
    }
    else if (k < 0)
    {
        cerr << "Parameter k should be positive" << endl;
        return 1;
    }
    else if (d < 0)
    {
        cerr << "Parameter d should be positive" << endl;
        return 1;
    }

    int fileNumber = sort(f, k, M);
    if (fileNumber == -1)
    {
        std::cout << "Error in sorting the file : " << f << endl;
    }

    if (!merge(fileNumber, d, k))
    {
        return 1;
    }

    return 0;
}