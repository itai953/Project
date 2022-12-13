#include "Data.h"
//check
void calclAverage(vector<vector<int> > &walks, vector<int> &avg, int edges, int g) {
    for (auto &walk : walks) {
        for (int i = 0; i < g; ++i) {
            avg[i] += walk[i];
        }
    }
    for (int &sum: avg) {
        sum /= edges;
    }
}

void writeData(vector<vector<int> > &walks, int edges, int g, const string &filePath) {
    std::ofstream dataFile(filePath + ".txt");
    std::vector<int> avg(g - 1);
    std::vector<int> maxWalk = walks[0];
    // calculate average for each c(i) of the edges
    calclAverage(walks, avg, edges, g);
    // getting max vector by lexicography order
    for (int i = 1; i < edges; ++i) {
        if (std::lexicographical_compare(begin(maxWalk), end(maxWalk), begin(walks[i]), end(walks[i]))) {
            maxWalk = walks[i];
        }
    }
    for (int i = 0; i < g - 1; ++i) {
        dataFile << avg[i] << " ";
    }
    dataFile << "\n";
    for (int i = 0; i < g - 1; ++i) {
        dataFile << maxWalk[i] << " ";
    }
    dataFile.close();
}