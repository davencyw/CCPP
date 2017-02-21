/*
 *
 *  Simple and small matrix writer and reader for efficient 
 *  store and load of large matrices in binary. Only supports
 *  double, float, int and unsigned int as data type.
 *  Has its own storage format. Format is *.cbm (CcppBinaryMatrix)
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

#ifndef __CCPP_IOMATRIX__
#define __CCPP_IOMATRIX__

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cassert>

#include "typetraits.hpp"

 //representation:

//	|	//first two bits indicates data type [T]
// 	|		//00 - double
// 	TN	//01 - float
// 	|		//10 - int
// 	|		//11 - unsigned int
// 	|	//next 62 bits represents an unsigned integer [N] containing the number of following data
// 	|		//max 16tb files
 		//next N * sizeof(T) bytes contain data

namespace ccpp{

	//metadata about binary representation
	template <class T>
	struct Tn
	{	
		//number of elements in data
		unsigned int n;
		//data type
		int t;
		//filename
		std::string filename;

		//data
		T* data;
	};

	//templated on the data type which is stored
	template <class T>
	class MatrixIO
	{
		public:

		static T* read(std::string filename){


			Tn<T> tn = getTnFromFile(filename);

			//allocate memory
			tn.data = (T*)_mm_malloc(tn.n*sizeof(T), 64);
			read(tn);

			return tn.data;

		}

		static void read(std::string filename, T* data, unsigned int N){

			Tn<T> tn = getTnFromFile(filename);
			tn.data = data;
			//sanity check
			assert(tn.n == N);
			read(tn);			

		}

		static void read(Tn<T> tn){

			//TODO buffer input with chunks
			//TODO filename check and append if - .cbm
			//TODO better exception handling than asserts
			//	   to tell the user what is wrong
			//TODO add file descriptor to Tn struct (only
			//     opening the file once..)

			//sanity check
			assert(tn.t >= 0);
			assert(tn.t == typehelper<T>::value);
			assert(tn.n < std::pow(2,62));

			FILE* file = fopen(tn.filename.c_str(), "r");
			//discard first entry
			int64_t disc;
			fread(&disc,sizeof(int64_t),1,file);
			fread(tn.data, sizeof(T), tn.n, file);
			fclose(file);

		}


		static void write(std::string filename, T* data, unsigned int N){

			//TODO buffer output with chunks
			//TODO filename check and append if - .cbm

			//first 64 bits
			int64_t first;

			//data type
			int64_t t(typehelper<T>::value);
			//number of data
			int64_t n(N);

			//sanity check
			assert(n < std::pow(2,62));
			assert(t < 4);
			assert(t >= 0);

			first = (n << 2) | t;

			filename.append(".cbm");

			FILE* file = fopen(filename.c_str(), "w");

			fwrite(&first, sizeof(int64_t), 1, file);
			fwrite(data, sizeof(T), n, file);
			fclose(file);

		}


		private:

		static std::string getProperFilename(std::string filename){

			std::string ext(".cbm");

			return filename.append(ext);
		}

		static Tn<T> getTnFromFile(std::string filename){

			Tn<T> tn;
			tn.filename = getProperFilename(filename);			

			//first 64 bits
			int64_t f;

			FILE* file = fopen(tn.filename.c_str(), "r");
			fread(&f, sizeof(int64_t), 1, file);
			fclose(file);
			
			//data type
			tn.t = (f & 0b11);
			//number of data
			tn.n = (f >> 2);

			std::cout<<tn.n<<"N"<<std::endl;

			return tn;
		}


			
	};

	//convenient typedefs
	typedef MatrixIO<double> MatIOd;
	typedef MatrixIO<float> MatIOf;
	typedef MatrixIO<int> MatIOi;
	typedef MatrixIO<unsigned int> MatIOu;

}

//end iomatrix.hpp
#endif
