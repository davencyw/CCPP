##DESCRIPTION
The __BENCH__ benchmarking class is designed to be a simple and clean but precise benchmarking tool for c++ applications. It relies on preprocessor macros to remove all benchmarking code for non benchmark runs such that all BENCH functions have no effect and can be optimized away with `-O3` if not used, such that you do not have to mess around with `#ifdef` macros in your own code. It is written as a static class, such that you can access it from everywhere in your project. The only thing you have to include then is your own `Benchdec.hpp` which specifies the sections you want to benchmark (see usage). You have to include `Benchdec.hpp` in every file, where you want to benchmark your code! __BENCH__ uses `Timer.hpp` from __CCPP__ implementation as timer.

##USAGE
###Benchdec.hpp
```c++
 #include <CCPP/time/bench.hpp>

//name of sections benchmarked
 enum
{
    B_TASKA = 0,
    B_TASKB,
    B_SUBTASKB
};
```
###Main.cpp
```c++
...
#include "Benchdec.hpp"

int main(){
    //setup info for better readability of summaries
    BENCH::setttitle("example")
    BENCH::setinfo("Loopcount: 100.")

    //Milliseconds is also default if no resolution is set
    BENCH::setresolution(BENCH::MILLISECONDS)

    //register your sections (enum in your benchdec.hpp)
    BENCH::reg("taskA");            //id = 0;
    BENCH::reg("taskB");            //id = 1;
    //child task of task B  
    BENCH::regchild("subtaskB", 1);  //id = 2;

    //start compuation

    BENCH::start(B_TASKA);
        /*
         * Your code to benchmark
         */
    BENCH::stop(B_TASKA);

    BENCH::start(B_TASKB);
        for(auto i(0); i<100; ++i){
            BENCH::start(B_SUBTASKB)
                /*
                 * Your code to benchmark
                 */
            BENCH::stop(B_SUBTASKB)
        }

    BENCH::stop(B_TASKB);

    //to get the benchmarking results either
    BENCH::summarize();
    //or
    BENCH::summarytocsv("yourfile");

}
```