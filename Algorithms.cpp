#include "Graph.h"
#include <random>

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

bool GD(int g, int max_n, Graph &res)
{
    Graph G;
    vector<Edge> edges;
    while (G.size() < max_n)
    {

        for (int v_even = 0; v_even < G.size(); v_even += 2)
        {
            int v_odd = G.get_neighbors(v_even)[rand() % 2];
            edges.push_back(std::make_pair(v_even, v_odd));
        }

        rand_perm(edges);

        Edge e{-1, -1};

        for (const auto &E : edges)
        {
            if (G.shortest_cycle(E.first, E.second) < g)
            {
                e = std::make_pair(E.first, E.second);
                break;
            }
        }

        if (e.first < 0)
        {
            res = G;
            return true;
        }

        

    }
}
