#ifndef PARSER_H
#define PARSER_H
#include "Graph.h"
#include "algorithm"
#include <sstream>

class Parser
{
    ifstream input_file;
    string file_path;
    int count_lines();
public:
    Parser(){ }
    Parser(const string& f_path):input_file(f_path),file_path(f_path){ }
    Graph parse_file();
    static bool get_parser(const vector<string>& args,Parser& result);

    const string& get_file_path() const {return file_path;}
};




#endif