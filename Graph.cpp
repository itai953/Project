#include "Graph.h"

Graph::Graph():_g(4) 
{
    for(int i=0; i < 4; i++)
    {
        insert_edge(i,(i+1)%4);
    }
    insert_edge(1,3);
}

const vector<int>& Graph::get_neighbors(int v) const
{
    return _g[v];
}

bool Graph::insert_edge(int u, int v)
{
    if(u == v) return false;
    if(is_neighbor(u,v)) return false;
    if(_g[u].size() >= MAX_DEGREE || _g[v].size() >= MAX_DEGREE) return false;
    _g[u].push_back(v);
    _g[v].push_back(u);
}


bool Graph::is_neighbor(int u, int v)
{
    if(u == v)
        return false;
    for(int N : _g[u])
    {
        if (N == v)
        {
            return true;
        }
    }
}


int Graph::add_vertex()
{
    _g.emplace_back(vector<int>());
    return _g.size() - 1;
}


int Graph::get_degree(int v)
{
    return _g[v].size();
}


void Graph::remove_edge(int u, int v)
{
   if(!is_neighbor(u,v)) return;
   auto it_v = std::find(_g[u].begin(), _g[v].end(),v);
   _g[u].erase(it_v);
   auto it_u = std::find(_g[v].begin(), _g[v].end(), u);
   _g[v].erase(it_u);
}

void Graph::distance_from(int v, int *dist) const {
    const int n = _g.size();
    for(int i=0; i<n; i++) dist[i] = -1;
    dist[v] = 0;
    int q[n], q_write = 0, q_read = 0;
    q[q_write++] = v;
    while (q_read < q_write) {
        int u = q[q_read++];
        for(int w: get_neighbors(u)) {
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q[q_write++] = w;
            }
        }
    }
}


int Graph::shortest_cycle(int u, int v) {
    int n = _g.size();
    remove_edge(u,v);
    int dist_v[n];
    distance_from(v, dist_v);
    insert_edge(u,v);
    return dist_v[u]+1;
}