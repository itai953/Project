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
    return true;
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
    return false;
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
   auto it_v = std::find(_g[u].begin(), _g[u].end(),v);
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

void Graph::print(ostream& out) const
{
    for(int i=0; i < size(); i++ )
    {
        out << i << ": ";
        for(int v : _g[i])
        {
            out << v << " ";
        }
        out << "\n";
    }
}


ostream& operator<<(ostream& out, const Graph& G)
{
    G.print(out);
    return out;
}


void Graph::reserve_and_reset_counters(int num, int counter_size) const
{
  if ((int)_counters.size() < num) _counters.resize(num);
  for(int i=0; i<num; i++)
    _counters[i].resize(counter_size);
}


int Graph::edge_index(int u, int v) const
{
    const vector<int>& N = _g[u];
    for(int i=0; i < N.size(); i++)
    {
        if(N[i] == v)
            return i;
    }
    return -1;
}



void Graph::num_nb_paths_step(const SparseCounter& cur,
			      SparseCounter& next) const {
    int n = size();
    next.clear();
     for(const auto [edge,count] : cur) {
        int x = edge / MAX_DEGREE;
        int y = get_neighbors(x)[edge % MAX_DEGREE];
        for(int z : get_neighbors(x))
            if (y!=z)
                next.inc(z*MAX_DEGREE+edge_index(z,x), count);
     }
}




void Graph::num_nb_paths_back_step(const SparseCounter& cur,
			      SparseCounter& next) const {
    int n = size();
    next.clear();
    for(const auto [edge,count] : cur) {
        int x = edge / MAX_DEGREE;
        int y = get_neighbors(x)[edge % MAX_DEGREE];
        for(int z : get_neighbors(y))
            if (x!=z)
                next.inc(y*MAX_DEGREE+edge_index(y,z), count);
    }
}

int nb_paths_dot(const SparseCounter& c1, SparseCounter& c2)
{
    int acc = 0;
    for(const auto [edge,count] : c1)
        acc += count * c2[edge];
    return acc;
}

void Graph::num_closed_nb_walks(int u, int v, int l, int total[]) const
{
    const int n = size();
    reserve_and_reset_counters(3, MAX_DEGREE*n);
    int l_forward = l/2;
    int l_backward = l - l_forward;
    SparseCounter& last_forward = _counters[2];
    const int uv = u*MAX_DEGREE+edge_index(u,v);
    _counters[0].inc(uv);
    total[0] = 1;
    for(int i=0; i<l_forward; i++) {
        SparseCounter& cur = _counters[i%2];
        SparseCounter& next = _counters[(i+1)%2];
        num_nb_paths_step(cur, next);
        total[i+1] = next[uv];
    }
    std::swap(_counters[l_forward%2], last_forward);
    _counters[0].clear();
    _counters[0].inc(uv);
    for(int i=0; i<l_backward; i++) {
        SparseCounter& cur = _counters[i%2];
        SparseCounter& next = _counters[(i+1)%2];
        num_nb_paths_back_step(cur, next);
        total[l_forward+i+1] = nb_paths_dot(next, last_forward);
    }
}