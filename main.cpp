#include "Algorithms.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    Graph result,temp;
    int g, max_n,num_iterations;
    sscanf(argv[1],"%d",&g);
    sscanf(argv[2],"%d",&max_n);
    sscanf(argv[3],"%d",&num_iterations);
    GD(g, max_n, result);

    for(int i = 0; i < num_iterations; i++ )
    {
        GD(g, max_n, temp);
        if (temp.size() < result.size())
        {
            result = temp;
        }
    }
    cout << result;
    return 0;
}