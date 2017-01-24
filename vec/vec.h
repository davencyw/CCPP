

template <class T>
class vec2{

	vec2(){}

	private:

		T* data;
	
};


template <class T>
class vec3{

	vec3(){}

	private:

		T* data;
	
};


template <class T>
class vec4{

	vec4(){}

	T w(){return data[0];};
	T x(){return data[1];};
	T y(){return data[2];};
	T z(){return data[3];};
		

	private:

		T* data;
	
};


//TYPEDEFS

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;


typedef vec3<int> vec3i;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;


typedef vec4<int> vec4i;
typedef vec4<float> vec4f;
typedef vec4<double> vec4d;