# IntegrationMultiThreadTester
A simple C++ Monte Carlo integration program designed to scale well on multi-threaded machines.

This simple test can be used to indicate both processor speed and multi-thread scaling.

The tester works by generating a set of random points in the interval (a,b) and testing their heights in the sin(x)/x function.
Heights are added to a running sum, to approximate the area under the curve sin(x)/x. 
The workload is split thread-wise. 
A different set of random points is used for every run and every thread.

# USAGE: ./integrate lower_bound upper_bound point_count thread_count

speedup.sh tests a fixed number of points with a variable number of threads.
Thread count starts at 1 and increases linearly to the specified max thread count.
# USAGE: ./speedup.sh max_thread_count point_count

efficiency.sh tests a variable number of points with a variable number of threads.
Thread count starts at 1 and increases linearly to the specified max thread count.
Point count starts at 100,000,000 and increases linearly by 100,000,000 per iteration.
# USAGE: ./efficiency.sh max_thread_count

Find an explanation of Monte Carlo Integration here: https://en.wikipedia.org/wiki/Monte_Carlo_integration
