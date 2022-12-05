#include "Algorithms.h"

using std::min;

typedef std::pair<int, int> Edge;

void rand_perm(vector<Edge> &v)
{
    for (int i = v.size() - 1; i > 0; i--)
        std::swap(v[i], v[rand() % (i + 1)]);
}

int add_two_mid(Graph& G, Edge& e)
{
    G.remove_edge(e.first, e.second);
    int v_mid_even = G.add_vertex();
    int v_mid_odd = G.add_vertex();
    G.insert_edge(e.first,v_mid_odd);
    G.insert_edge(v_mid_odd,v_mid_even);
    G.insert_edge(v_mid_even,e.second);
    return v_mid_odd;
}

Edge random_furthest_edge(const Graph &G, int v, const vector<Edge> &candidate_edges)
{
    int n = G.size();
    int dist_v[n];
    G.distance_from(v, dist_v);
    int max_dist = -1;
    vector<Edge> f_edges_candidates;
    for (const auto &e : candidate_edges)
        if (min(dist_v[e.first], dist_v[e.second]) >= max_dist)
        {
            if (min(dist_v[e.first], dist_v[e.second]) > max_dist)
                f_edges_candidates.clear();
            max_dist = min(dist_v[e.first], dist_v[e.second]);
            f_edges_candidates.push_back(std::make_pair(e.first,e.second));
        }
    return f_edges_candidates[rand() % f_edges_candidates.size()];
}

bool GD(int g, int max_n, Graph &res)
{
    Graph G; //default c'tor builds k4m
    vector<Edge> edges;
    while (G.size() < max_n)
    {
        edges.clear();
        for (int v_even = 0; v_even < G.size(); v_even += 2)
        {
            int v_odd = G.get_neighbors(v_even)[rand() % 2];
            edges.push_back(std::make_pair(v_even, v_odd));
        }

        rand_perm(edges); //randomize edges order in vector

        Edge e{-1, -1};

        //iterate on all edges in vector, if any are in a cycle of length < g, add vertices
        for (const auto &E : edges)
        {
            if (G.shortest_cycle(E.first, E.second) < g)
            {
                e = std::make_pair(E.first, E.second);
                break;
            }
        }

        //no edges are part of cycle of length < g, success
        if (e.first < 0)
        {
            res = G;
            return true; //return the built graph
        }

        int mid_e = add_two_mid(G, e);
        Edge f = random_furthest_edge(G, mid_e, edges);
        int mid_f = add_two_mid(G,f);
        G.insert_edge(mid_e,mid_f);
    }
    return false;
}
