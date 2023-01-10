#include "Validator.h"

bool Validator::validate(int& result)
{
    bool status = true;
    m_Graph = m_Parser.parse_file();
    
    int shortest_cycle = INT_MAX;
    for(int u = 0; u < m_Graph.size(); u++)
    {
        for(auto v: m_Graph.get_neighbors(u))
        {
            shortest_cycle = std::min(m_Graph.shortest_cycle(u,v),shortest_cycle);
        }
    }
    result = shortest_cycle;
    if (shortest_cycle < m_MinCycleLength)
    {
        cout << "bad graph, shortest cycle in the graph: " << shortest_cycle << "\n";
        return false;
    }
    return status;
}


bool validator_main(const vector<string>& args)
{
    bool status = true;
    Parser p;
    status = Parser::get_parser(args,p);
    if(!status)
    {
        cerr <<"Error: encountered error when trying to initialize a parser\n";
        return status;
    }
    auto args_iter = find(args.begin(), args.end(), "--mincycle");
    if(args_iter == args.end())
    {
        cerr << "--mincycle is a required argument for valifation\n";
        return false;
    }
    string sMinCycleLength = *(++args_iter);
    int g,shortest_cycle;
    sscanf(sMinCycleLength.c_str(),"%d",&g);
    Validator v(p,g);
    status = v.validate(shortest_cycle);
    if(status)
    {
        cout << "SUCCESS, Graph has no cycles shorter than "<< g << "\n";
        cout << "shortest cycle length in the graph is: " << shortest_cycle << "\n";
    }
    return status;
}