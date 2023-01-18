#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include "SparseCounter.h"
#include "Data.h"


using namespace std;
using std::vector;
class Graph
{
private:
    enum{MAX_DEGREE = 3};
    vector<vector<int>> _g;
    mutable std::vector<SparseCounter> _counters;
    void reserve_and_reset_counters(int num, int counter_size) const;
    void num_nb_paths_step(const SparseCounter& cur,SparseCounter& next) const;
    void num_nb_paths_back_step(const SparseCounter& cur,SparseCounter& next) const;
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
    int edge_index(int u, int v) const;
    int shortest_cycle(int u, int v);
    int size() const  {return _g.size();}
    void print(ostream& out) const;
    void num_closed_nb_walks(int u, int v, int l, int num_walks[]) const;
};

ostream& operator<<(ostream& out, const Graph& G);
#endif