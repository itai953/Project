#include "Algorithms.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    Graph result;
    int g, max_n;
    sscanf(argv[1],"%d",&g);
    sscanf(argv[2],"%d",&max_n);
    // cout << g << " " << max_n;
    GD(g, max_n, result);
    cout << result;
    return 0;
}