#include "Algorithms.h"
#include "Validator.h"

#include <sstream>
#include <iterator>



int main(int argc, char** argv)
{
    
    vector<string> args(argv, argv+argc);
    auto arg_iter = find(args.begin(), args.end(), "--validate");
    if (arg_iter != args.end())
    {
        bool status = true;
        status = validator_main(args);
        if(!status)
        {
            exit(1);
        }
        return 0;
    }
    Graph result,temp;
    int g, max_n,num_iterations;
    sscanf(argv[1],"%d",&g);
    sscanf(argv[2],"%d",&max_n);
    sscanf(argv[3],"%d",&num_iterations);
    string PATH = string(argv[4]);
    
    ofstream log_file(PATH+ "_0.log");
    GF(max_n, g, result,log_file);
    log_file.close();

    //start looping
    for(int i = 1; i < num_iterations; i++ )
    {
        stringstream ss;
        ss <<"_" << i << ".log";
        ofstream log_file(PATH + ss.str());
        GF(max_n, g, temp,log_file);
        if (temp.size() < result.size())
        {
            result = temp;
        }
        log_file.close();
    }
    ofstream output(PATH + "_result.txt");
    // output << "result graph:\n";
    output << result;
    output.close();
    return 0;
}