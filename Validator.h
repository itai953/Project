#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "Parser.h"
#include "Algorithms.h"
#include <stdio.h>

class Validator
{
    Graph m_Graph;
    Parser m_Parser;
    int m_MinCycleLength; //g
public:
    Validator(Parser& parser,int g):m_Graph(),m_Parser(parser.get_file_path()),m_MinCycleLength(g){ }
    bool validate(int& result);
    
};


bool validator_main(const vector<string>& args);

#endif