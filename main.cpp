#include "Algorithms.h"
#include "Validator.h"

#include <sstream>
#include <iterator>


int generate_check_point(double mean,int seed){
    // create a random number engine
    std::mt19937 rng(seed);

    // create a normal distribution with the desired mean and standard deviation 1
    std::normal_distribution<double> normal_dist(mean, mean/10);

    // generate and print 10 random numbers from the normal distribution
    // for (int i = 0; i < 10; i++) {
    //     double rand_num = normal_dist(rng);
    //     rand_num = std::round(rand_num / 4.0) * 4.0;  // round to the nearest multiple of 4
    //     std::cout << rand_num << " ";
    // }
    //std::cout << std::endl;
    double rand_num = normal_dist(rng);
    rand_num = std::round(rand_num / 4.0) * 4.0;
    return (int) rand_num;
}

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
    int g, max_n,num_iterations,checkpoint;
    sscanf(argv[1],"%d",&g);
    sscanf(argv[2],"%d",&max_n);
    sscanf(argv[3],"%d",&num_iterations);
    sscanf(argv[4],"%d",&checkpoint);
    string PATH = string(argv[5]);
    srand(0); // add seed 0
    ofstream log_file(PATH+ "_0.log");
    // ofstream log_from_checkpoint(PATH+"_check_0.log");
    bool status = true;
    checkpoint = generate_check_point(checkpoint,0); //new
    status = GF(max_n, g, result,log_file,checkpoint);
    log_file.close();
    //start looping
    for(int i = 1; i < num_iterations; i++ )
    {
        srand(i); //add seed
        stringstream ss;
        ss <<"_" << i << ".log";
        ofstream log_file(PATH + ss.str());
        ofstream log_from_checkpoint(PATH+"_check" + ss.str());
        checkpoint = generate_check_point(checkpoint,i); //new
        status = GF(max_n, g, temp,log_file,checkpoint);
        if (temp.size() < result.size())
        {
            result = temp;
        }
        log_file.close();
    }
    if(status)
    {
        ofstream output(PATH + "_result.txt");
        // output << "result graph:\n";
        output << result;
        output.close();
    }
    return 0;
}