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

		//first two bits indicates data type [T]
 			//00 - double
 			//01 - float
 			//10 - int
 			//11 - unsigned int
 		//next 62 bits represents an unsigned integer [N] containing the number of following data
 			//max 16tb files
 		//next N * sizeof(T) bytes contain data

namespace ccpp{

	
	//templated on the data type which is stored
	template <class T>
	class MatrixIO
	{
		public:

		static T* read(std::string filename){

			//TODO buffer input with chunks
			//TODO filename check and append if - .cbm

			//first 64 bits
			int64_t first;

			filename.append(".cbm");
			FILE* file = fopen(filename.c_str(), "r");

			fread(&first, sizeof(int64_t), 1, file);

			//data type
			int64_t t(first & 0b11);
			//number of data
			int64_t n(first >> 2);

			//sanity check
			assert(t >= 0);
			assert(t == typehelper<T>::value);
			assert(n < std::pow(2,62));

			T* data = (T*)_mm_malloc(n*sizeof(T), 64);

			fread(data, sizeof(T), n, file);

			fclose(file);

			return data;

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

			
	};

	//convenient typedefs
	typedef MatrixIO<double> MatIOd;
	typedef MatrixIO<float> MatIOf;
	typedef MatrixIO<int> MatIOi;
	typedef MatrixIO<unsigned int> MatIOu;

}

//end iomatrix.hpp
#endif
