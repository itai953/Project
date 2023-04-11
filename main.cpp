#include "Algorithms.h"
#include "Validator.h"

#include <sstream>
#include <iterator>
#include <chrono>

using namespace chrono;


int generate_check_point(double mean,int seed){
    // create a random number engine
    std::mt19937 rng(seed);

    // create a normal distribution with the desired mean and standard deviation 1
    std::normal_distribution<double> normal_dist(mean, 12);

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
    bool status = true;
    checkpoint = generate_check_point(checkpoint,0); //new
    auto start = high_resolution_clock::now();
    status = GF(0xFFFFFFFF, g, result,log_file,checkpoint);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    log_file << "duration: " << duration.count();
    log_file.close();
    int best_iter = 0;
    bool success = false;
    //start looping
    for(int i = 1; i < num_iterations; i++ )
    {
        srand(i); //add seed
        stringstream ss;
        ss <<"_" << i << ".log";
        ofstream log_file(PATH + ss.str());
        checkpoint = generate_check_point(checkpoint,i); //new
        start = high_resolution_clock::now();
        status = GF(max_n, g, temp,log_file,checkpoint);
        stop = high_resolution_clock::now();
        duration = duration_cast<seconds>(stop - start);
        log_file << "duration: " << duration.count();
        if (status && (temp.size() < result.size()))
        {
            result = temp;
            best_iter = i;
            success = true;
        }
        log_file.close();
    }
    if(status)
    {
        ofstream output(PATH + "_result.txt");
        // output << "result graph:\n";
        output << result;
        output << "\niteration: " << best_iter << endl;
        output.close();
    }
    return 0;
}