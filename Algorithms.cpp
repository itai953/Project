#include "Algorithms.h"
#include <cmath>
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

inline int walks_compare(const int tot_walks[], const int best_tot_walks[], int g)
{
  for (int l = 1; l < g; l++)
    if (tot_walks[l] != best_tot_walks[l])
      return tot_walks[l] - best_tot_walks[l];
  return 0;
}


vector<Edge> find_max_walks_edges(const Graph &G, int max_walks[], int g, vector<vector<int>>& walks_vec)
{
    vector<Edge> max_walks_edges;
    int n = G.size();
    max_walks[1] = -1;
    for(int v_even = 0; v_even < n ; v_even+=2)
    {
        for(const int& v_odd: G.get_neighbors(v_even))
        {
            int walks[g];
            G.num_closed_nb_walks(v_odd, v_even, g - 1, walks);
            walks_vec.push_back(vector<int>(walks, walks+g));
            int cmp = walks_compare(walks, max_walks, g);
            if (cmp >= 0)
            {
                if (cmp > 0)
                {
                    for (int l = 1; l < g; l++)
                        max_walks[l] = walks[l];
                    max_walks_edges.clear();
                }
                max_walks_edges.push_back(make_pair(v_even, v_odd));
            }
        }
    }

    return max_walks_edges;
}

int shortest_walk(const int tot_walks[], int g)
{
  for (int l = 1; l < g; l++)
    if (tot_walks[l])
      return l;
  return g;
}

vector<Edge> find_edges_with_max_walks(const Graph &G, int max_walks[], int g,
                                       const vector<Edge> &candidate_edges)
{
    int u,v;
    vector<Edge> max_walks_edges;
    max_walks[1] = -1;
    for (auto e : candidate_edges)
    {
        u = e.first;
        v = e.second;
        int walks[g];
        G.num_closed_nb_walks(u, v, g - 1, walks);
        int cmp = walks_compare(walks, max_walks, g);
        if (cmp >= 0)
        {
            if (cmp > 0)
            {
                for (int l = 1; l < g; l++)
                    max_walks[l] = walks[l];
                max_walks_edges.clear();
            }
            max_walks_edges.push_back(make_pair(u, v));
        }
    }
  return max_walks_edges;
}
int GrowF_find_f_cadidates(const Graph &G, const Edge &e, int g,
                           vector<Edge> &f_candidates)
{
    int n = G.size();
    int dist_from_v2[n];
    G.distance_from(e.first, dist_from_v2);
    int max_dist = -1;
    f_candidates.clear();
    for (int u2 = 0; u2 < n; u2 += 2)
    {
        int dist = min(dist_from_v2[u2] + 3, g);
        if (dist < max_dist)
            continue;
        if (dist > max_dist)
        {
            f_candidates.clear();
            max_dist = dist;
        }
        for (int u3 : G.get_neighbors(u2))
            f_candidates.push_back(make_pair(u2, u3));
    }
    return max_dist;
}

bool GF_from_checkpoint(int max_n, int g, Graph& result, ofstream& log)
{
    Graph G = result;
    int n = G.size();
    
    while(n <= max_n)
    {
        vector<vector<int>> walks_vec;
        int max_walks[g];
        vector<Edge> max_walks_edges = find_max_walks_edges(G, max_walks, g,walks_vec);
        int s = shortest_walk(max_walks, g);
        if (s == g)
        {
            result = G;
            log << "GF FROM CHECK POINT SUCCESS, n =" << n << "\n";
            return true;
        }
        writeData(walks_vec,walks_vec.size(),g,log,n);
        Edge e = max_walks_edges[rand() % max_walks_edges.size()];
        vector<Edge> f_candidates;
        int max_D = GrowF_find_f_cadidates(G, e, g, f_candidates);
        int max_walks2[g];
        f_candidates = find_edges_with_max_walks(G, max_walks2, g, f_candidates);
        auto f = f_candidates[rand() % f_candidates.size()];
        int mid_e = add_two_mid(G, e);
        int mid_f = add_two_mid(G, f);
        G.insert_edge(mid_e, mid_f);
        n = G.size();
    }
    log << "GF FROM CHECK POINT FAILED\n";
    return false;
}
vector<int> calc_max_c_vect(int g,Graph& G){
    vector<vector<int>> walks_vec;
    int max_walks[g];
    vector<Edge> max_walks_edges = find_max_walks_edges(G, max_walks, g,walks_vec);
    double func_res = 0;
    vector<int>& maxWalk = walks_vec[0];
    for (int i = 1; i < walks_vec.size(); ++i) {
        if (std::lexicographical_compare(begin(maxWalk), end(maxWalk), begin(walks_vec[i]), end(walks_vec[i]))) {
            maxWalk = walks_vec[i];
        }
    }
    
    return maxWalk;
}
bool climb_G_from_checkpoint(int max_n,int g,Graph& G,ofstream& log_check){
    int n = G.size();
    while (n <= max_n)
    {
        vector<vector<int>> walks_vec;
        int max_walks[g];
        vector<Edge> max_walks_edges = find_max_walks_edges(G, max_walks, g,walks_vec);
        double func_res = 0;
        vector<int>& maxWalk = walks_vec[0];
        for (int i = 1; i < walks_vec.size(); ++i) 
        {
            if (std::lexicographical_compare(begin(maxWalk), end(maxWalk), begin(walks_vec[i]), end(walks_vec[i]))) 
            {
                maxWalk = walks_vec[i];
            }
        }
        Edge e;
        vector<Edge> f_candidates;
        writeData(walks_vec, walks_vec.size(), g, log_check, n);
        int s = shortest_walk(max_walks, g);
        if (s == g)
        {
            log_check << "GF SUCCESS, n =" << n << "\n"; 
            return true;
        }
        vector<pair<Edge,Edge> > e_f_candidates(10);
        for (int i = 0; i < 10; i++)
        {
            Edge e = max_walks_edges[rand() % max_walks_edges.size()];
            int max_D = GrowF_find_f_cadidates(G, e, g, f_candidates);
            int max_walks2[g];
            f_candidates = find_edges_with_max_walks(G, max_walks2, g, f_candidates);
            auto f = f_candidates[rand() % f_candidates.size()];
            e_f_candidates[i] = pair<Edge,Edge>(e,f);
        }
        auto G_min = G;
        vector<int> min_vect(g,1000);
        pair<Edge,Edge> min_e_f;
        for(auto& cand: e_f_candidates){
            auto G_copy = G;
            int mid_e = add_two_mid(G_copy, cand.first);
            int mid_f = add_two_mid(G_copy, cand.second);
            G_copy.insert_edge(mid_e, mid_f);
            n = G_copy.size();
            vector<int> tmp_vect = calc_max_c_vect(g,G_copy);
            //cout << tmp_res << " above\n";
            if (std::lexicographical_compare(begin(tmp_vect), end(tmp_vect), begin(min_vect), end(min_vect))) 
            {
                min_vect = tmp_vect;
                min_e_f = cand;
                G_min = G_copy;
                if(std::lexicographical_compare(begin(tmp_vect), end(tmp_vect), begin(maxWalk), end(maxWalk)))
                {
                    break;
                }
            }
        }
        G = G_min;
        
    }
    return false;  
}

bool GF(int max_n, int g, Graph& result, ofstream& log, int checkpoint)
{
    Graph G; //construct k4m;
    int n = G.size();
    int log_interval = 24;
    bool status = true;
    while(n <= max_n)
    {
        if(n == checkpoint)
        {
            status = climb_G_from_checkpoint(max_n,g,G,log);
            if (status)
                result = G;
            break;
        }
        vector<vector<int>> walks_vec;
        int max_walks[g];
        vector<Edge> max_walks_edges = find_max_walks_edges(G, max_walks, g,walks_vec);
        log_interval = (n/log_interval >= 10) ? log_interval*2 : log_interval;
        if((n % log_interval) == 4)
        {
            writeData(walks_vec, walks_vec.size(), g, log, n);
        }
        int s = shortest_walk(max_walks, g);
        if (s == g)
        {
            result = G;
            log << "GF SUCCESS, n =" << n << "\n"; 
            return true;
        }
        Edge e = max_walks_edges[rand() % max_walks_edges.size()];
        vector<Edge> f_candidates;
        int max_D = GrowF_find_f_cadidates(G, e, g, f_candidates);
        int max_walks2[g];
        f_candidates = find_edges_with_max_walks(G, max_walks2, g, f_candidates);
        auto f = f_candidates[rand() % f_candidates.size()];
        int mid_e = add_two_mid(G, e);
        int mid_f = add_two_mid(G, f);
        G.insert_edge(mid_e, mid_f);
        n = G.size();
    }

    if(!status) log << "GF FAILED\n";
    return status;
}

