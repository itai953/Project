#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <fstream>
#include "Algorithms.h"
using namespace std;


void writeData(vector<vector<int> > &walks, int edges, int g, const string &filePath);

void calclAverage(vector<vector<int> > &walks, vector<int> &avg, int edges, int g);




#endif