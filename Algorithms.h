#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "Graph.h"
#include <random>
#include <algorithm>

using std::min;
typedef std::pair<int, int> Edge;

void rand_perm(vector<Edge> &v);
int add_two_mid(Graph& G, Edge& e);
Edge random_furthest_edge(const Graph &G, int v, const vector<Edge> &candidate_edges);
bool GD(int g, int max_n, Graph &res);

#endif