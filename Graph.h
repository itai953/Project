#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <cassert>
#include "SparseCounter.h"
#include "Data.h"


using namespace std;
using std::vector;
typedef std::pair<int, int> Edge;
class Graph
{
private:
    enum{MAX_DEGREE = 3};
    vector<vector<int>> _g;
    mutable std::vector<SparseCounter> _counters;
    void reserve_and_reset_counters(int num, int counter_size) const;
    void num_nb_paths_step(const SparseCounter& cur,SparseCounter& next) const;
    void num_nb_paths_back_step(const SparseCounter& cur,SparseCounter& next) const;
    int expected_k4m_ball_size_v(int v_deg, int radius) const;
    int expected_k4m_ball_size_e(int v_deg, int u_deg, int radius) const;
    int ball_size_v(int v, int radius) const;
    int ball_size_e(const Edge& e, int radius) const;
    void distance_from(const Edge& e, int dist[]) const;
public:
    /* builds k4-edge */
    Graph();

    const vector<int>& get_neighbors(int v) const;
    const vector<vector<int>>& get_graph() const {return _g;}
    bool insert_edge(int u, int v);
    void remove_edge(int u, int v);
    bool is_neighbor(int u, int v);
    int add_vertex();
    int get_degree(int v) const;
    void distance_from(int v, int dist[]) const;
    int edge_index(int u, int v) const;
    int shortest_cycle(int u, int v);
    int size() const  {return _g.size();}
    void print(ostream& out) const;
    void num_closed_nb_walks(int u, int v, int l, int num_walks[]) const;
    bool is_k4m_graph(int n, int g) const;
    bool is_k4m_graph(int n) const;
    bool adjacent(int u, int v) const {
        for( int v_ : get_neighbors(u) )
        if (v_ == v)
        return true;
        return false;
    }
};

ostream& operator<<(ostream& out, const Graph& G);
#endif