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


void writeDataFromCheckPoint(vector<vector<int> >& walks, int edges, int g, ofstream& filepath, int n)
{
    vector<vector<int> > filtered_walks(walks.size());
    auto iter = std::copy_if(walks.begin(), walks.end(),filtered_walks.begin(),
                [](const vector<int>& vec)
                {
                    auto first = vec.begin();
                    auto last = vec.end();
                    first++;
                    while(first != last)
                    {
                        if(*first != 0) return true;
                        first++;
                    }
                    return false;
                });
    filtered_walks.resize(iter - filtered_walks.begin());
    std::sort(filtered_walks.begin(), filtered_walks.end(),[](const vector<int>& a,const vector<int> &b)
    {
        return std::lexicographical_compare(a.begin(), a.end(),b.begin(),b.end());
    });
    filepath << n << "\n";
    int trailing_zeros=0;
    auto max_walk = (*(--filtered_walks.end()));
    for(trailing_zeros=0; trailing_zeros < g-1; trailing_zeros++)
    {
        if(max_walk[trailing_zeros+1] != 0)
            break;
    }
    for(auto &walk: filtered_walks)
    {
        for(int i=trailing_zeros+1; i < g; i++)
        {
            filepath << walk[i] << " ";
        }
        filepath << "\n";
    }
}