/*
 *
 *  DESCRIPTION
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
#ifndef __CCPP_TERMINALIO__
#define __CCPP_TERMINALIO__

#include <cassert>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace CCPP{
	namespace term{

		//const border elements
		constexpr char horiz[]		= ("\u2550");
		constexpr char vertic[] 	= ("\u2551");
		constexpr char lucorner[]	= ("\u2554");
		constexpr char llcorner[]	= ("\u255A");
		constexpr char rucorner[]	= ("\u2557");
		constexpr char rlcorner[]	= ("\u255D");
		//const color elements
		constexpr char precolor[] 	= ("\033[1;31m");
		constexpr char pascolor[] 	= ("\033[0m");


		void clearterm(){
			std::cout<<"\033[2J\033[1;1H";
		}

		std::pair<unsigned int, unsigned int> gettermsize(){
			struct winsize w;
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			return std::make_pair(w.ws_row,w.ws_col);
			
		}

		unsigned int gettermwidth(){
			auto size(gettermsize());
			return size.second;
		}



		void writebox(unsigned int width, unsigned int height, std::string text){

			std::string firstlastline("");
			std::string boxtext("");

			//generating first and last border line
			for (int i = 0; i < width-2; ++i){
				firstlastline += horiz;
			}

			//generating boxtext
			std::vector<std::string> lines;
			boost::split(lines, text, boost::is_any_of("\n"));
			
			unsigned int numlinesintext(lines.size());
			const unsigned int firsttextlineat(height/2 - numlinesintext/2);
			const unsigned int emptytoplines((height-2)/2 - numlinesintext/2);
			const unsigned int emptybottomlines(height-emptytoplines-numlinesintext);

			assert(numlinesintext + emptytoplines + emptybottomlines == height);
			for (int i = 0; i < emptytoplines; ++i)
			{
				boxtext.append(vertic);
				boxtext.append(width-2,' ');
				boxtext.append(vertic);
				boxtext.append("\n");
			}

			for (int i = 0; i < numlinesintext; ++i)
			{
				int leftwidth((width-2-lines[i].length())/2);
				int rightwidth(width-2-lines[i].length()-leftwidth);

				leftwidth < 0 ? leftwidth = 0 : leftwidth = leftwidth;
				rightwidth < 0 ? rightwidth = 0 : rightwidth = rightwidth;

				boxtext.append(vertic);
				boxtext.append(leftwidth,' ');
				boxtext.append(precolor + lines[i] + pascolor);
				boxtext.append(rightwidth,' ');
				boxtext.append(vertic);
				boxtext.append("\n");
			}

			for (int i = 0; i < emptybottomlines; ++i)
			{
				boxtext.append(vertic);
				boxtext.append(width-2,' ');
				boxtext.append(vertic);
				boxtext.append("\n");
			}


			std::cout << lucorner << firstlastline << rucorner << "\n";
			std::cout << boxtext;
			std::cout << llcorner << firstlastline << rlcorner << "\n";


		}

	}
}
//end terminal.hpp
#endif
