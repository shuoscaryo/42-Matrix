#include "Vector.tpp"

template <typename T>
float angle_cos(const Vector<T> & u, const Vector<T> & v)
{
	// dot(U,V) = mod(U) * mod(V) * cos(O)
	// cos = dot(U,V) / (mod(U) * mod(V))
	return u.dot(v) / (u.norm() * v.norm());
}
