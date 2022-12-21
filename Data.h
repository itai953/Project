#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <fstream>
#include "Algorithms.h"
using namespace std;
//check

void writeData(vector<vector<int> > &walks, int edges, int g, const string &filePath, int n);

void calclAverage(vector<vector<int> > &walks, vector<int> &avg, int edges, int g, int n);




#endif