#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>

#include "InputStream1.h"
#include "InputStream2.h"
#include "InputStream3.h"
#include "InputStream4.h"

using namespace std;

void freeStreamPointer(InputStream *is)
{
    delete is;
    is = NULL;
}

void RandJump(string f, int j, unsigned int streamId)
{
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;
    startTime = chrono::high_resolution_clock::now();
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
        perror("Error implementation id not valid");
        break;
    }
    if (is->open(f))
    {
        long long int sum = 0;
        long long int randomMax = RAND_MAX;
        int it = 1;
        while (randomMax < is->getSize())
        {
            randomMax += RAND_MAX;
            it++;
        }
        //cout << "size file: " << is.getSize() << " rand " << RAND_MAX << " it " << it << endl;
        long long int p;
        for (int i = 0; i < j; i++)
        {
            p = 0;

            for (int k = 0; k < it; k++)
            {
                srand(time(nullptr) + p * 5 + 8 * sum * rand());
                p += rand();
            }
            //p = 243;
            p = p % is->getSize();
            //cout << p << endl;
            is->seek(p);
            string str = is->readln();
            //cout << str << endl;
            sum += str.length();
        }
        if (!is->close())
        {
            std::cout << "Error couldn t close the file : " << f << " with the InputStream" << streamId << endl;
        }
        freeStreamPointer(is);
        cout << "Implementation " << streamId << " sum: " << sum;
        endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> resultTimes = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        cout << "(time: " << resultTimes.count() << ")" << endl;
    }
    else
    {
        freeStreamPointer(is);
        std::cout << "Error couldn t open the file : " << f << " with the InputStream" << streamId << endl;
    }
}

int main(int argc, char **argv)
{
    string path = "C:\\Users\\Andre\\Documents\\imdb\\aka_name.csv";
    cout << "is1 " << endl;
    RandJump(path, 50000, 1);
    cout << "is2 " << endl;
    RandJump(path, 50000, 2);
    cout << "is3 " << endl;
    RandJump(path, 50000, 3);
    cout << "is4 " << endl;
    RandJump(path, 50000, 4);
}