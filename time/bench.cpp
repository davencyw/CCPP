#include "bench.hpp"

#ifdef CCPP_BENCH

using namespace std;

	//bench title - optional
	string BENCH::_title = "";
	string BENCH::_info = "";

	//number of profiled sections
	int BENCH::_n = -1;
	//name of profiled section
	vector<string> BENCH::_names;
	//realtions
	vector<int> BENCH::_father;
	//time of profiled section [ms]
	vector<long int> BENCH::_times;
	//timer for every section
	vector<Timer> BENCH::_timers;
	//resolution of timer - milliseconds default
	int BENCH::_res = BENCH::MILLISECONDS;
	string BENCH::_resname = "ms";

#endif