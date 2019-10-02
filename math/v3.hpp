#pragma once
#include "math.h"
#include <fstream>

class Vector;
class Point;

template <class T>
class V3 {
public:
	T x;
	T y;
	T z;
	T w;
	V3(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
	V3() : x(0), y(0), z(0), w(0) {}

	// addition
	template <class T2>
	auto operator+(const V3<T2>& v) -> V3<decltype(v.x + x)>
	{
		return V3(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	template <class T2>
	V3<T>& operator+=(const V3<T2>& v)
	{
		return *this + v;
	}
	
	// subtraction
	template <class T2>
	auto operator-(const V3<T2>& v) -> V3<decltype(v.x - x)>
	{
		return V3(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	template <class T2>
	V3<T>& operator-=(const V3<T2>& v)
	{
		return *this - v;
	}

	// multiplication
	template <class T2>
	friend V3<T> operator*(const V3<T>& v, const T2& scalar) 
	{
		return V3<T>((T)scalar * v.x, (T)scalar * v.y, (T)scalar * v.z, (T)scalar * v.w);
	}

	template <class T2>
	friend V3<T> operator*(const T2& scalar, const V3<T>& v) 
	{
		return V3<T>((T)scalar * v.x, (T)scalar * v.y, (T)scalar * v.z, (T)scalar * v.w);
	}

	// division
	template <class T2>
	V3<T> operator/(const T2& scalar) 
	{
		return *this * (double)(1/(double)scalar);
	}

	// initialization (copy)
	template <class T2>
	V3(const V3<T2>& v) : x((T)v.x), y((T)v.y), z((T)v.z), w((T)v.w) {}

	// dot product
	template <class T2>
	auto dot(const V3<T2>& v) -> decltype(x * v.x) 
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	// equality
	template <class T2>
	bool operator==(V3<T2> v) const
	{
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}

	// magnitude
	double magnitude() const 
	{
		return sqrt(x * x + y * y + z * z);
	}

	V3<T> normalize()
	{
		double m = this->magnitude();
		return V3<T>(x / m, y / m, z / m, w);
	}

	// quick casts to points and vectors to set w
	friend class Vector;
	friend class Point;
	operator Vector() const;
	operator Point() const;
};

template <class T1, class T2>
auto dot(const V3<T1>& v1, const V3<T2>& v2) -> decltype(v1.dot(v2))
{
	return v1.dot(v2);
}

template <class T1, class T2>
auto cross(const V3<T1>& v1, const V3<T2>& v2) -> V3<decltype(v1.y * v2.z - v1.z * v2.y)>
{
	return V3<decltype(v1.y * v2.z - v1.z * v2.y)>(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
		0.0 // vector
	);
}

template <class T>
std::ostream& operator <<( std::ostream& os, V3<T> const& v ) {
    os << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.z << "}";
    return os;
}

typedef V3<double> Tuple;
typedef Vector Color;
