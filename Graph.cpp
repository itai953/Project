#include "Graph.h"

vertex_set* Graph::get_neighbors(int v)
{
    if (list.find(v) != list.end())
    {
        return &(list[v]);
    }
    return nullptr;
}

void Graph::insert_edge(int u, int v)
{
    list[u].insert(v);
    list[v].insert(u);
}


bool Graph::is_neighbor(int u, int v)
{
    auto it = list[u].end();
    return (list[u].find(v) != it);
}


void Graph::add_vertex(int v)
{
    if(list.find(v) == list.end())
        list.insert({v,vertex_set{}});
}

int Graph::get_degree(int v)
{
    return list[v].size();
}


void Graph::remove_edge(int u, int v)
{
    list[u].erase(v);
    list[v].erase(u);
}