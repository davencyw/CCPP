/*
 *
 *	CCPP_BENCHmark class for easy CCPP_BENCHmarking and profiling
 *  cpp codes.
 *  ___________________________________________________________
 *
 *  Part of:
 *  Common CPP Library 
 *  Common c++ library for everyday use. Always in development.
 *
 *  author: david schmidig [david@davencyw.net] 
 *          DAVENCYW CODE [davencyw.net]
 *          Msc CSE ETH Zurich
 *
 *
 */

#ifndef __BENCH__
#define __BENCH__

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "timer.hpp"

using namespace std;


class BENCH
{
	public:

	#ifdef CCPP_BENCH
		enum Timeres
		{
			MICROSECONDS = Timer::MICROSECONDS,
			MILLISECONDS = Timer::MILLISECONDS,
			SECONDS = Timer::SECONDS
		};
	#endif

	static void inline settitle(string title){
		#ifdef CCPP_BENCH
			_title = title;
		#endif
	}

	static void inline setresolution(Timeres res){
		_res = res;

		//get time resolution unit to string
		switch(_res){

			case MICROSECONDS : _resname = "μs";
				break;
			case MILLISECONDS : _resname = "ms";
				break;
			case SECONDS 	 : _resname = "s";
				break;
			default      : _resname = "TIMEERROR";
				break;
		}

	}

	static void inline reg(string name){
		#ifdef CCPP_BENCH
			transform(name.begin(), name.end(),name.begin(), ::toupper);
			_names.emplace_back(name);
			_timers.emplace_back(Timer());
			_times.emplace_back(0);
			++_n;
			_father.push_back(-1); //no father
		#endif
	}

	static void inline regchild(string name, int father){
		#ifdef CCPP_BENCH
			transform(name.begin(), name.end(),name.begin(), ::toupper);
			_names.emplace_back(name);
			_timers.emplace_back(Timer());
			_times.emplace_back(0);
			++_n;
			_father.push_back(father);
		#endif
	}

	static void inline start(const int i){
		#ifdef CCPP_BENCH
			_timers[i].start();

		#endif
	}

	static void inline stop(const int i){
		#ifdef CCPP_BENCH
			_timers[i].stop();
			_times[i] += _timers[i].elapsed(_res);
			_timers[i].reset();
		#endif
	}

	static void inline summarize(){
		#ifdef CCPP_BENCH
			double totale(0);

			//TODO sort output according to relations!
			//TODO maybe colored?

			//get total times of all father sections
			for (int i = 0; i < _n; ++i)
			{	
				if(_father[i] == -1)
					totale += _times[i];
			}

			if(!_title.empty())
				_title.append("\n");


			cout<<"P R O F I L I N G\n"
				<<_title
				<<"_________________\n\n\n";

			for (int i = 0; i <= _n; ++i)
			{	
				bool hasfather(_father[i]!=-1);
				double t(0);
				if(totale)
					t = (100.0 * _times[i] / totale);

				if(!hasfather){
					cout<< _names[i] << endl
						<< "runtime " << _resname << "\t\t" << _times[i] << endl
						<< "percentage of runtime \t" << t << "%" << endl << endl;
				}
				else{
					int father = _father[i];
					double t(0);
					if(_times[father])
						t = ((double)_times[i]/_times[father])*100.0;

					cout<<"╚═════  "
						<< _names[i] << endl
						<< "\truntime " << _resname << "\t\t" << _times[i] << endl
						<< "\tpercentage of runtime \t" << t << "%"<< endl << endl;

				}
			}
		#endif
	}


	static void summarytocsv(string filename){
		#ifdef CCPP_BENCH

			if(_title.empty())
				_title = "NO TITLE";
			if(_info.empty())
				_info = "NO INFO";

			//open file
			ofstream fileout;
			fileout.open(filename);

			//write summary
			fileout << _title << endl
					<< _info << endl
					<< "resolution: " << _resname << endl;

			//write csv description
			fileout << "id;name;time[" << _resname << "];fatherid"<<endl;

			//write data
			for (int i = 0; i <= _n; ++i)
			{
				fileout << i << ";" << _names[i] << ";"
						<< _times[i] << ";" << _father[i] << endl;
			}

			
			//close filestream	
			fileout.close();
		
		#endif

	}

	private:

	#ifdef CCPP_BENCH

		//bench title - optional
		static string _title;

		//info of program for summary - optional
		static string _info;

		//number of profiled sections
		static int _n;
		//name of profiled section
		static vector<string> _names;
		//relations pair(father, child)
		static vector<int> _father;
		//time of profiled section [ms]
		static vector<long int> _times;
		//timer for every section
		static vector<Timer> _timers;
		//resolution of timer
		static int _res;
		static string _resname;
	#endif
};

//bench.hpp
#endif 