#ifndef GRAPH_H
#define GRAPH_H
#include <algorithm>
#include <vector>

using std::vector;
class Graph
{
private:
    enum{MAX_DEGREE = 3};
    vector<vector<int>> _g;
public:
    /* builds k4-edge */
    Graph();

    const vector<int>& get_neighbors(int v) const;
    const vector<vector<int>>& get_graph() const {return _g;}
    bool insert_edge(int u, int v);
    void remove_edge(int u, int v);
    bool is_neighbor(int u, int v);
    int add_vertex();
    int get_degree(int v);
    void distance_from(int v, int dist[]) const;
    int shortest_cycle(int u, int v);
    int size() const  {return _g.size();}
};


#endif