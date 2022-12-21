#include "Data.h"
//check
void calclAverage(vector<vector<int> > &walks, vector<double> &avg, int edges, int g, int n) {
    for (auto &walk : walks) {
        for (int i = 0; i < g; ++i) {
            avg[i] += walk[i];
        }
    }
    for (auto &sum: avg) {
        sum /= edges;
    }
}

void writeData(vector<vector<int> > &walks, int edges, int g, ofstream &dataFile, int n) {
    // std::ofstream dataFile(filePath + ".txt");
    std::vector<double> avg(g);
    std::vector<int> maxWalk = walks[0];
    // calculate average for each c(i) of the edges
    calclAverage(walks, avg, edges, g, n);
    // getting max vector by lexicography order
    for (int i = 1; i < edges; ++i) {
        if (std::lexicographical_compare(begin(maxWalk), end(maxWalk), begin(walks[i]), end(walks[i]))) {
            maxWalk = walks[i];
        }
    }
    dataFile << n << "\n";
    for (int i = 0; i < g; ++i) {
        dataFile << avg[i] << " ";
    }
    dataFile << "\n";
    for (int i = 0; i < g; ++i) {
        dataFile << maxWalk[i] << " ";
    }
    dataFile << "\n";
    // dataFile.close();
}