#include "Complex.hpp"
#include <stdexcept>

Complex::Complex(void):
	_r(0), _i(0)
{}

Complex::Complex(float real, float imaginary):
	_r(real), _i(imaginary)
{}

Complex::Complex(const Complex & src)
{
	*this = src;
}

Complex::~Complex()
{}

Complex &Complex::operator=(const Complex &rhs)
{
	_r = rhs._r;
	_i = rhs._i;
	return (*this);
}

Complex Complex::operator+(const Complex& rhs) const {
	return Complex(_r + rhs._r, _i + rhs._i);
}

Complex Complex::operator-(const Complex& rhs) const {
	return Complex(_r - rhs._r, _i - rhs._i);
}

Complex Complex::operator*(const Complex& rhs) const {
	return Complex(_r * rhs._r - _i * rhs._i, _r * rhs._i + _i * rhs._r);
}

std::ostream &operator<<(std::ostream &os, const Complex &obj)
{
	os << obj._r << " + " << obj._i << "i";
	return (os);
}
