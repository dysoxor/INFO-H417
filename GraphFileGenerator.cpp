#include "GraphFileGenerator.h"
#include <iostream>

GraphFileGenerator::GraphFileGenerator(string fileName) {
    setFileName(fileName);
}

void GraphFileGenerator::setAxis(string axis1, string axis2) {
    this->axis1 = axis1;
    this->axis2 = axis2;
}

void GraphFileGenerator::setFileName(string fileName) {
    this->fileName = fileName;
}

void GraphFileGenerator::setTitle(string title) {
    this->title = title;
}

void GraphFileGenerator::addPoint(double x, double y) {
    if (lineIndex == -1) {
        std::cout << "Erreur, no lines defined" << std::endl;
        return;
    }
    vector<double> point;
    point.push_back(x);
    point.push_back(y);
    lines.at(lineIndex).push_back(point);
}

void GraphFileGenerator::nextLine(string name){
    names.push_back(name);
    lineIndex += 1;
    lines.push_back(vector<vector<double>>());
}

void GraphFileGenerator::writeResult() {
    OutputStream2* os = new OutputStream2();
    if (fileName.size() == 0) {
        std::cout << "Erreur, no fileName defined" << std::endl;
        return;
    }
    if (!os->create(fileName)) {
        perror("Error writing result");
        return;
    }
    if (title.size() == 0) {
        std::cout << "Title not defined" << std::endl;
        return;
    }
    if (axis1.size() == 0 || axis2.size() == 0) {
        std::cout << "Axis not defined" << std::endl;
        return;
    }
    os->writeln(title);
    os->writeln(axis1+","+axis2);
    os->writeln("#");
    for (int i = 0; i < lines.size(); i++) {
        os->writeln(names.at(i));
        for (int j = 0; j < lines.at(i).size(); j++) {
            os->writeln(to_string(lines.at(i).at(j).at(0))+","+to_string(lines.at(i).at(j).at(1)));
        }
        os->writeln("#");
    }
    os->close();
}