#include "Parser.h"


Graph Parser::parse_file()
{
    Graph result;
    for(int i=0; i < 4; i++)
    {
        result.remove_edge(i,(i+1)%4);
    }
    result.remove_edge(1,3);
    int num_vertices = count_lines();
    int u,v;
    while (result.size() < num_vertices)
    {
        result.add_vertex();
    }
    string line;
    while (!input_file.eof())
    {
        std::getline(input_file,line);
        if( line == "" )
            break;
        stringstream ss(line);
        ss >> u;
        ss.ignore();
        int deg = (u%2)?3:2;
        for(int i=0; i < deg; i++)
        {
            ss >> v;
            if(ss.fail())
            {
                cerr << "ERROR: wrong degree for vertex " << u << "\n";
                exit(1);
            }
            result.insert_edge(u,v);
        }
        ss >> v;
        if(!ss.fail())
        {
            cerr <<"ERROR: while reading neighbors of vertex  " << u << "\n";
        }
    }
    return result;
}

int Parser::count_lines()
{
    ifstream inFile(file_path); 
    return std::count(std::istreambuf_iterator<char>(inFile), 
                      std::istreambuf_iterator<char>(), '\n');
}

bool Parser::get_parser(const vector<string>& args,Parser& result)
{
    auto args_iter = find(args.begin(), args.end(), "--fpath");
    if(args_iter == args.end())
    {
        cerr << "ERROR: --parse flag must have --fpath\n";
        return false;
    }
    string fpath = *(++args_iter);
    ifstream input(fpath);
    if (!input.is_open())
    {
        cerr << "ERROR: unable to open file at path" << fpath << "\n";
        return false;
    }
    result.input_file = ifstream(fpath);
    result.file_path = fpath;
    return true;
}