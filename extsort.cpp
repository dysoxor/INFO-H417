#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "InputStream2.h"
#include "OutputStream2.h"

using namespace std;

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

void merge(int files, int d, int k)
{
    vector<InputStream2 *> is;
    string lines[d];
    vector<InputStream2 *>::iterator ptr;
    int pos = 0;
    int counter = 0;
    string prefixSorted = "sorted";
    string prefixMerged = "merged";
    for (int i = 0; i < files; i++)
    {
        is.push_back(new InputStream2());
        if (!is.at(i)->open(prefixSorted + to_string(i)))
        {
            cerr << "Could not open on reading the file:" << (prefixSorted + to_string(i)) << endl;
        }
    }
    OutputStream2 *os = new OutputStream2();
    while (is.size() > 1)
    {
        cout << is.size() << endl;
        ptr = is.begin();
        advance(ptr, pos);
        for (int i = 0; i < d; i++)
        {

            if (!(*ptr)->end_of_stream())
            {
                lines[i] = (*ptr)->readln();
            }
            else
            {
                lines[i] = "";
            }
            cout << lines[i] << endl;
            if (pos + i == is.size() - 1)
            {
                ptr = is.begin();
            }
            else
            {
                advance(ptr, 1);
            }
        }

        if (!os->create(prefixMerged + to_string(counter)))
        {
            cout << "Error create" << endl;
        }

        int best;
        int ptrBest;
        while (!isEmpty(lines, d))
        {
            ptr = is.begin();
            advance(ptr, pos);
            best = 99999;
            ptrBest = 0;
            for (int i = 0; i < d; i++)
            {
                if (!lines[i].empty() && (int)lines[i][k] < best)
                {
                    ptrBest = i;
                    best = (int)lines[i][k];
                }
            }
            os->writeln(lines[ptrBest]);
            if (pos + ptrBest >= is.size())
            {
                ptr = is.begin();
                advance(ptr, (pos + ptrBest) - is.size());
            }
            else
            {
                advance(ptr, pos + ptrBest);
            }
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
        for (int i = 0; i < d - 1; i++)
        {
            (*ptr)->close();
            delete (*ptr);
            is.erase(ptr);
            ptr = is.begin();
            advance(ptr, pos);
        }
        (*ptr)->close();
        os->close();
        if (!(*ptr)->open(prefixMerged + to_string(counter)))
        {
            cerr << "Could not open on reading the file:" << (prefixMerged + to_string(counter)) << endl;
        }
        counter++;
        pos = (pos + 1) % is.size();
    }
    delete os;
}

int main(int argc, char **argv)
{
    /*string f = argv[1];
    char *a = argv[2];
    int k = atoi(a);
    char *b = argv[3];
    int M = atoi(a);
    char *c = argv[4];
    int d = atoi(a);*/

    merge(4, 2, 2);

    return 0;
}