/*
 *
 *	Benchmark class for easy benchmarking and profiling
 *  cpp codes.
 *  ___________________________________________________________
 *
 *	Part of:
 *	Common CPP Library 
 *	Common c++ library for everyday use. Always in development.
 *
 *	author: david schmidig [david@davencyw.net]
 *			Msc CSE ETH Zurich
 *
 *
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "timer.hpp"

using namespace std;


class BENCH
{
	public:

	BENCH():_n(-1){};

	void reg(){
		#ifdef BENCH
			_names.emplace_back("a");
			++_n;
		#endif
	}

	void start(int i){
		#ifdef BENCH
			if(i>_n)
				//not available
				return
			if(_running[i])
				//already running
				return

			_running[i] = true;
			_timers[i].start();

		#endif
	}

	void stop(int i){
		#ifdef BENCH
			if(i>_n)
				//not available
				return
			if(!_running[i])
				//not running
				return

			_running[i] = false;
			_times[i] += _timers[i].elapsed();
			_timers[i].reset();
		#endif
	}

	void summarize(){
		#ifdef BENCH
			double totale(accumulate(_times.begin(),_times.end(),0));


			cout<<"P R O F I L I N G\n"
				<<"_________________\n\n\n";

			for (int i = 0; i <= _n; ++i)
			{
				cout<< _names[i] << endl
					<< "runtime [ms]\t\t" << _times[i]
					<< "percentage of runtime \t" << totale\_times[i] << endl << endl;
			}
		#endif
	}


	private:

	#ifdef BENCH
		//number of profiled sections
		int _n;
		//name of profiled section
		vector<string> _names;
		//time of prifiled section
		vector<double> _times;
		//timer for every section
		vector<Timer> _timers;
		//indicates running timers
		vector<bool> _running;
	#endif
};