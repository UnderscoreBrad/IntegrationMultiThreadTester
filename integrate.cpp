#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <pthread.h>
#include <chrono>

struct integration_args {
    long double a;
    long double b;
    long n;
    long double rtnVal;
};

void *integrate_runner(void* arg){
    struct integration_args *struct_ptr = (struct integration_args*) arg;
    std::uniform_real_distribution<double> unif(struct_ptr->a, struct_ptr->b);      //https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    std::default_random_engine random;                                              //random doubles are faster than long doubles w/o difference in accuracy
    //random.seed(std::chrono::system_clock::now().time_since_epoch().count());       //faster than std::random_device
    random.seed(pthread_self());
    for(long i = 0; i < struct_ptr->n; i++){
        long double point = unif(random);                            //Generate new random point
        long double height = sin(point)/point;                       //Get height at random point
        struct_ptr->rtnVal += height;                           //Add height to running sum
    }                                                           //area = ([summation f(x)]/(num points))*(upper bound - lower bound)
    //struct_ptr->rtnVal = (struct_ptr->rtnVal/struct_ptr->n) * (struct_ptr->b-struct_ptr->a);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    if(argc < 5){
        std::cerr << "ERROR:\tInvalid number of terminal arguments.\nUSAGE:\t./integrate a b n n_threads" << std::endl;
        exit(EXIT_FAILURE);
    }
    long double a = std::stold(argv[1]);
    long double b = std::stold(argv[2]);
    long n = std::stol(argv[3]);
    long n_threads = std::stol(argv[4]);

    if(n_threads > 10 || n_threads < 1) n_threads = 8;   //default to 8 if invalid count
    long n_per_thread = n/n_threads;
    long remainder = n%n_threads;
    //long double partition = (b-a)/n_threads;

    struct integration_args iArgs[10];  //scales to a max of 10 threads
    pthread_t tids[10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    iArgs[0].a = a;
    iArgs[0].b = b;//a + partition;
    iArgs[0].n = n_per_thread + remainder;  //deals with remainder while avoiding extra branch
    iArgs[0].rtnVal = 0;
    pthread_create(&tids[0], &attr, integrate_runner, &iArgs[0]);

    for(long i = 1; i < 10 && i < n_threads; i++){
        iArgs[i].a = a;// + (partition * (long double)i);
        iArgs[i].b = b;// + (partition * (long double)(i+1));
        iArgs[i].n = n_per_thread; 
        iArgs[i].rtnVal = 0;
        pthread_create(&tids[i], &attr, integrate_runner, &iArgs[i]);
    }

    long double area = 0.0;
    for(long i = 0; i < n_threads; i++){
        pthread_join(tids[i], NULL);
        area += iArgs[i].rtnVal;
    }
    printf("%.17Lf\n", (area/n)*(b-a));
    return EXIT_SUCCESS;
}