#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//check

void writeData(vector<vector<int> > &walks, int edges, int g, ofstream &filePath, int n);

void calclAverage(vector<vector<int> > &walks, vector<int> &avg, int edges, int g, int n);




#endif