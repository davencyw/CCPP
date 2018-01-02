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
/*
 *
 *  Type traits converting type to 2 bit number for double(00),
 *  float(01), int(10) and unsigned int(11)
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

#ifndef __CCPP_TYPETRAITS__
#define __CCPP_TYPETRAITS__

//type traits - get data type
	template <class T>
	class typehelper
	{
		public:
		static const int value = -1;		
	};

	template <>
	class typehelper <double>
	{
		public:
		static const int value = 0;		
	};

	template <>
	class typehelper <float>
	{
		public:
		static const int value = 1;		
	};

	template <>
	class typehelper <int>
	{
		public:
		static const int value = 2;		
	};


	template <>
	class typehelper <unsigned int>
	{
		public:
		static const int value = 3;		
	};
//end typetraits.hpp
#endif
