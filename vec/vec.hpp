/*
 *	DLP friendly vector class for aligned memory and SOA memory layouts
 *
 */

#if defined(__INTEL_COMPILER)
#include <malloc.h>
#else
#include <mm_malloc.h>
#endif


template <class T>
class Vec2{

	Vec2(){T* data = (T*)_mm_malloc(2*sizeof(T), 64);}

	T x(){return data[0];};
	T y(){return data[1];};

	private:

		T* data;
	
};


template <class T>
class Vec3{

	Vec3(){T* data = (T*)_mm_malloc(3*sizeof(T), 64);}

	T x(){return data[0];};
	T y(){return data[1];};
	T z(){return data[2];};

	private:

		T* data;
	
};


template <class T>
class Vec4{

	Vec4(){T* data = (T*)_mm_malloc(4*sizeof(T), 64);}

	T w(){return data[0];};
	T x(){return data[1];};
	T y(){return data[2];};
	T z(){return data[3];};
		

	private:

		T* data;
	
};


//TYPEDEFS

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;


typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;


typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;