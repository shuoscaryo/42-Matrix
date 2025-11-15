#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>
#include <cmath> // used in allowed functions

template<typename T> class Matrix;
template <typename T> class Vector;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &obj);

template <typename T>
class Vector
{
	public:
	// Constructors and destructor

		Vector();
		Vector(const Vector<T> & rhs);
		Vector(size_t size);
		Vector(std::initializer_list<T> rhs);
		~Vector();

	// Operator overloads

		Vector<T> & operator=(const Vector<T> & rhs);
		T & operator[](size_t i);
		const T & operator[](size_t i) const;
		Vector<T> operator+(const Vector<T> & rhs);
		Vector<T> operator-(const Vector<T> & rhs);
		Vector<T> operator*(const T & rhs);

	// Setters and getters	


	// Member functions

		size_t size() const;
		Matrix<T> toMatrix(size_t cols, size_t rows) const;

		Vector<T> & add(const Vector<T> & rhs);
		Vector<T> & sub(const Vector<T> & rhs);
		Vector<T> & scl(const T & rhs);

		T dot(const Vector<T> & rhs) const;

		float norm_1() const;
		float norm() const;
		float norm_inf() const;

	protected:
	private:
	// Atributes

		std::unique_ptr<T[]> _elements;
		size_t _size;

	// Private member functions


	// Friends <3

		friend std::ostream &operator<< <T>(std::ostream &os, const Vector<T> &obj);
};

// wrapper for printing inline
template<class T>
struct inlineVectorPrint
{
	const Vector<T>& v;
};

// Helper so it's shorter
template<class T>
inlineVectorPrint<T> ivp(const Vector<T>& v)
{
	return inlineVectorPrint<T>{v};
}

// CONSTRUCTORS

template <typename T>
Vector<T>::Vector():
	_elements(nullptr),
	_size(0)
{}

template <typename T>
Vector<T>::Vector(const Vector<T> & rhs)
{
	*this = rhs;
}

template <typename T>
Vector<T>::Vector(size_t size):
	_elements(std::make_unique<T[]>(size)),
	_size(size)
{}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> rhs):
	_elements(std::make_unique<T[]>(rhs.size())),
	_size(rhs.size())
{
	size_t i = 0;
	for (auto &j: rhs)
		_elements[i++] = j;
}

template <typename T>
Vector<T>::~Vector()
{}

// OPERATORS

template <typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> & rhs)
{
	if (this == &rhs)
		return *this;
	_size = rhs.size();
	_elements = std::make_unique<T[]>(_size);
	for (size_t i = 0; i < _size; ++i)
		_elements[i] = rhs[i];
	return *this;
}

template <typename T>
T & Vector<T>::operator[](size_t i)
{
	if (i >= _size)
		throw std::out_of_range("Vector::[] out of range");
	return _elements[i];
}

template <typename T>
const T & Vector<T>::operator[](size_t i) const
{
	if (i >= _size)
		throw std::out_of_range("Vector::[] out of range");
	return _elements[i];
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> & rhs)
{
	Vector<T> output = *this;
	output.add(rhs);
	return output;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> & rhs)
{
	Vector<T> output = *this;
	output.sub(rhs);
	return output;
}

template <typename T>
Vector<T> Vector<T>::operator*(const T & rhs)
{
	Vector<T> output = *this;
	output.scl(rhs);
	return output;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &obj)
{
	if (obj.size() == 0)
	{
		os << "[]";
		return os;
	}

	for (size_t i = 0; i < obj.size(); ++i)
	{
		os << "[" << obj[i] << "]";
		if (i != obj.size() - 1)
		os << "\n";
	}
		
	return os;
}

template <typename T>
std::ostream &operator<<(
	std::ostream &os,
	const inlineVectorPrint<T> &obj
){
	const Vector<T>& v = obj.v;
	if (v.size() == 0)
	{
		os << "[]";
		return os;
	}

	os << "[";
	for (size_t i = 0; i < v.size() - 1; ++i)
		os << v[i] << " ";
	os << v[v.size() - 1] << "]";
		
	return os;
}

// MEMBER FUNCTIONS

template <typename T>
size_t Vector<T>::size() const
{
	return _size;
}

template <typename T>
Matrix<T> Vector<T>::toMatrix(size_t cols, size_t rows) const
{
	if (_size != cols * rows)
		throw std::runtime_error("Vector::toMatrix Invalid matrix shape");
	Matrix<T> output(cols, rows);
	size_t k = 0;
	for (size_t j = 0; j < rows; ++j)
		for (size_t i = 0; i < cols; ++i)
			output[i][j] = _elements[k++];
	return output;
}

// EX00

template <typename T>
Vector<T> & Vector<T>::add(const Vector<T> & rhs)
{
	if (_size != rhs._size)
		throw std::invalid_argument("Vector::add size mismatch");
	for (size_t i = 0; i < _size; ++i)
		_elements[i] += rhs[i];

	return *this;
}

template <typename T>
Vector<T> & Vector<T>::sub(const Vector<T> & rhs)
{
	if (_size != rhs._size)
		throw std::invalid_argument("Vector::sub size mismatch");
	for (size_t i = 0; i < _size; ++i)
		_elements[i] -= rhs[i];

	return *this;
}

template <typename T>
Vector<T> & Vector<T>::scl(const T & rhs)
{
	for (size_t i = 0; i < _size; ++i)
		_elements[i] *= rhs;

	return *this;
}

// EX01

template <typename T>
Vector<T> linear_combination(
	std::initializer_list<Vector<T>> u,
	std::initializer_list<T> coefs
)
{
	if (u.size() == 0)
		return Vector<T>();
	if (u.size() != coefs.size())
		throw std::runtime_error("Vector::linear_combination different \"u\" and \"coefs\" sizes.");
	Vector<T> output(u.begin()->size());
	auto uIt = u.begin();
	auto coefsIt = coefs.begin();
	do
	{
		Vector<T> vScaled(*uIt);
		vScaled.scl(*coefsIt);
		output.add(vScaled);
		++uIt;
		++coefsIt;
	} while(uIt != u.end());
	return output;	
}

// EX02

template <typename V>
V lerp(V u, V v, float t)
{
	return u + (v - u) * t;
}

// EX03

template <typename T>
T Vector<T>::dot(const Vector<T> & rhs) const
{
	if (this->size() != rhs.size())
        throw std::invalid_argument("Vector::dot vectors must have same size");
	if (this->size() == 0)
		return T{};
	T output = _elements[0] * rhs[0];
	for (size_t i = 1; i < this->size(); ++i)
		output += _elements[i] * rhs[i];
	return output;
}

// EX04

template <typename T>
float Vector<T>::norm_1() const
{
	// Defined as:
	//     norm_1 = Σ |v[i]|
	// First you gotta move one axis, then next, then next...
	// like a taxi in NY moving in the grid, can't cross the buildings
	// Distance if parallel axis movement is completely restricted
	float output = 0;
	for (size_t i = 0; i < size(); ++i)
	{
		float val = (_elements[i] > 0 ? _elements[i] : - _elements[i]);
		output += val;
	}
	return output;
}

template <typename T>
float Vector<T>::norm() const
{
	// Defined as:
	//     norm = sqrt(Σ |v[i]|^2)
	// Usual distance calculation, can go on all axis at once but each axis
	// speed is limited relative to movement speed
	// Distance if parallel axis movement is allowed but the energy is capped
	// at the same value on all directions
	float output = 0;
	for (size_t i = 0; i < size(); ++i)
	{
		float val = (_elements[i] > 0 ? _elements[i] : - _elements[i]);
		output += val * val;
	}
	// Math lib used here (subject)
	output = pow(output, 0.5);
	return output;
}

template <typename T>
float Vector<T>::norm_inf() const
{
	// Defined as:
	//     norm = max(|v|)
	// You can move on all axis independently, like a 3D printer that a
	// movement takes as much as the furthest point in an axis
	// Distance if parallel axis movement is allowed and no inter axix
	// restrictions
	float output = 0;
	for (size_t i = 0; i < size(); ++i)
	{
		float val = (_elements[i] > 0 ? _elements[i] : - _elements[i]);
		output = (val > output ? val : output);
	}
	return output;
}