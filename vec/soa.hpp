/*
 *
 * SOA class for DLP friendly use. 
 * Uses intel SIMD intrinsics for SOA and SOA - SOA operations.
 *  ___________________________________________________________
 *
 *  Part of:
 *  Common CPP Library 
 *  Common c++ library for everyday use. Always in development.
 *
 *  author: david schmidig [david@davencyw.net]
 *          Msc CSE ETH Zurich
 *
 *
 */

#ifndef __CCPP_SOA__
#define __CCPP_SOA__


#if defined(__INTEL_COMPILER)
#include <malloc.h>
#else
#include <mm_malloc.h>
#endif

#include <immintrin.h>


template <class T>
class Soa{

	public:
		Soa(unsigned int n){

			_data = (T*)_mm_malloc(n*sizeof(T), 64);
			_n = n;

		}

		void vadd(Soa<T>* sa, Soa<T>* sc){

			auto a = sa->data();
			auto c = sc->data();

			//compiler auto vectorization
			//no intrinsics needed
			for (int i = 0; i < _n; ++i)
			{
				c[i] = _data[i] + a[i];
			}
		}

		void vadd(Soa<T>* sa){

			auto a = sa->data();

			//compiler auto vectorization
			//no intrinsics needed
			for (int i = 0; i < _n; i++)
			{	
				_data[i] = _data[i] + a[i];
				
			}

		}

		void vmult(Soa<T>* sa, Soa<T>* sc){

			auto a = sa->data();
			auto c = sc->data();

			//compiler auto vectorization
			//no intrinsics needed
			for (int i = 0; i < _n; ++i)
			{
				c[i] = _data[i] * a[i];
			}
		}

		void vmult(Soa<T>* sa){

			auto a = sa->data();

			//compiler auto vectorization
			//no intrinsics needed
			for (int i = 0; i < _n; i++)
			{	
				_data[i] = _data[i] * a[i];
				
			}

		}

		void set(T s){

			for (int i = 0; i < _n; ++i)
			{
				_data[i] = s;
			}
		}

		T* data(){
			return _data;
		}

		~Soa(){

			_mm_free(_data);
		}
		
	private:

		T* _data;
		unsigned int _n;


}; 

//end soa.hpp
#endif 
