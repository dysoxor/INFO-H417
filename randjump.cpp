#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>

#include "InputStream1.h"
#include "InputStream2.h"
#include "InputStream3.h"
#include "InputStream4.h"

#include "GraphFileGenerator.h"

using namespace std;

void freeStreamPointer(InputStream *is)
{
    delete is;
    is = NULL;
}

double RandJump(string f, int j, unsigned int streamId, int t)
{
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;

    InputStream *is;
    switch (streamId)
    {
    case 1:
        is = new InputStream1();
        cout << "Input stream 1... " << endl;
        break;

    case 2:
        is = new InputStream2();
        cout << "Input stream 2... " << endl;
        break;

    case 3:
        is = new InputStream3();
        cout << "Input stream 3... " << endl;
        break;

    case 4:
        is = new InputStream4();
        cout << "Input stream 4... " << endl;
        break;

    default:
        perror("Error implementation id not valid");
        break;
    }
    if (is->open(f))
    {
        startTime = chrono::high_resolution_clock::now();
        long long int sum = 0;
        long long int randomMax = RAND_MAX;
        long long int it = 1;
        while (randomMax < is->getSize())
        {
            randomMax += RAND_MAX;
            it++;
        }
        long long int p;
        for (long long int i = 0; i < j; i++)
        {
            p = 0;

            for (long long int k = 0; k < it; k++)
            {
                srand(t + p * 5 + 8 * sum * rand());
                p += rand();
            }
            p = (p % is->getSize());
            is->seek(p);
            string str = is->readln();
            if (str.length() == 0)
            {
                p = ((p + 1) % is->getSize());
                is->seek(p);
                str = is->readln();
            }
            sum += str.length();
        }
        is->close();
        delete is;
        is = NULL;

        size_t pos = 0;
        string token;
        while ((pos = f.find("\\")) != string::npos)
        {
            token = f.substr(0, pos);
            f.erase(0, pos + 1);
        }
        cout << "Implementation " << streamId << " (" << f << ") sum: " << sum;
        endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> resultTimes = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        cout << " (time: " << resultTimes.count() << "s)" << endl;
        return resultTimes.count();
    }
    else
    {
        delete is;
        is = NULL;
        std::cout << "Error couldn t open the file : " << f << " with the InputStream" << streamId << endl;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *a = argv[1];
    int j = atoi(a);
    string paths[argc - 2];
    string fileNames[argc - 2];
    for (int i = 2; i < argc; i++)
    {
        paths[i - 2] = argv[i];
    }

    GraphFileGenerator *gfg = new GraphFileGenerator("graphOutput.txt");
    gfg->setTitle("Exp2 with buffer 1024");
    gfg->setAxis("file", "Time (s)");
    gfg->nextLine("IS1");
    int times[argc - 2];

    for (int i = 0; i < argc - 2; i++)
    {
        times[i] = time(nullptr);

        gfg->addPoint(i, RandJump(paths[i], j, 1, times[i]));
    }
    gfg->nextLine("IS2");
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 2, times[i]));
    }
    gfg->nextLine("IS3");
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 3, times[i]));
    }
    gfg->nextLine("IS4");
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 4, times[i]));
    }
    gfg->writeResult();
    delete gfg;

    return 0;
}