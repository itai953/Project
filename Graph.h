#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <unordered_set>

typedef std::unordered_set<int> vertex_set;
typedef std::unordered_map<int,vertex_set> adj_list;

class Graph
{
private:
    int g,n;
    adj_list list;
public:
    Graph(int g):g(g),n(4),list{} {}
    vertex_set* get_neighbors(int v);
    const adj_list& get_adjacency_list() const {return list;}
    void insert_edge(int u, int v);
    void remove_edge(int u, int v);
    bool is_neighbor(int u, int v);
    void add_vertex(int v);
    int get_degree(int v);
};


#endif