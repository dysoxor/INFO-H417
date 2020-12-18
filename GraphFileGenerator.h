#ifndef PROJECT_GRAPH_FILE_GENERATOR_H
#define PROJECT_GRAPH_FILE_GENERATOR_H


#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "OutputStream2.h"

using namespace std;

class GraphFileGenerator
{
private:
    string axis1 = "";
    string axis2 = "";
    vector<string> names;
    string fileName;
    vector<vector<vector<double>>> lines;
    int lineIndex = -1;

public:
    GraphFileGenerator(string fileName);
    void setAxis(string axis1, string axis2);
    void setFileName(string fileName);
    void addPoint(double x, double y);
    void nextLine(string name);
    void writeResult();
};

#endif //PROJECT_GRAPH_FILE_GENERATOR_H