
#include <chrono>

#include "InputStream1.h"
#include "InputStream2.h"
#include "InputStream3.h"
#include "InputStream4.h"

#include "GraphFileGenerator.h"

using namespace std;
/**
 * check if an array has only empty strings
 * 
 * @param f         input file
 * @param j         number of random jumps
 * @param streamId  the input stream to use
 * @param t         random parameter
 * 
 * @return          time needed to execute the experiment
 */
double RandJump(string f, int j, unsigned int streamId, int t)
{
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;

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
        startTime = chrono::high_resolution_clock::now();
        long long int sum = 0;
        long long int randomMax = RAND_MAX; // max value of the random number
        long long int it = 1;
        while (randomMax < is->getSize())
        {
            randomMax += RAND_MAX;
            it++; // number of times that the program must generate random number to be able to chose a number on the full size of the file
        }
        long long int p;
        for (long long int i = 0; i < j; i++)
        {
            p = 0;

            for (long long int k = 0; k < it; k++)
            {
                srand(t + p * 5 + 8 * sum * rand()); // because it is a pseudo random generator, there are some parameters to give to control it nd make it random in the same time
                p += rand();
            }
            p = (p % is->getSize()); // random position
            is->seek(p);
            string str = is->readln();
            if (str.length() == 0) // increment the position if the program reads an end of line otherwise the random number is stuck on the same number each round
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
    for (int i = 2; i < argc; i++)
    {
        paths[i - 2] = argv[i];
    }

    GraphFileGenerator *gfg = new GraphFileGenerator("graphOutput.txt"); // text file to generate graphs
    gfg->setTitle("Exp2 with buffer 1024");
    gfg->setAxis("file", "Time (s)");
    gfg->nextLine("IS1");
    int times[argc - 2];
    cout << "Input stream 1... " << endl;
    for (int i = 0; i < argc - 2; i++)
    {
        times[i] = time(nullptr);
        gfg->addPoint(i, RandJump(paths[i], j, 1, times[i]));
    }
    gfg->nextLine("IS2");
    cout << "Input stream 2... " << endl;
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 2, times[i]));
    }
    gfg->nextLine("IS3");
    cout << "Input stream 3... " << endl;
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 3, times[i]));
    }
    gfg->nextLine("IS4");
    cout << "Input stream 4... " << endl;
    for (int i = 0; i < argc - 2; i++)
    {
        gfg->addPoint(i, RandJump(paths[i], j, 4, times[i]));
    }
    gfg->writeResult();
    delete gfg;

    return 0;
}