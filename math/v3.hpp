#pragma once

template <class T>
class V3 {
public:
	T x;
	T y;
	T z;
	T w;
	V3(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}

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

	// initialization (copy)
	template <class T2>
	V3(const V3<T2>& v) : x((T)v.x), y((T)v.y), z((T)v.z), w((T)v.w) {}

	// dot product
	template <class T2>
	auto dot(const V3<T2>& v) -> decltype(x * v.x) 
	{
		return (x * v.x + y * v.x + z * v.z);
	}

	// equality
	template <class T2>
	bool operator==(V3<T2> v) const
	{
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}
};

template <class T1, class T2>
auto dot(const V3<T1>& v1, const V3<T2>& v2) -> decltype(v1.dot(v2))
{
	return v1.dot(v2);
}