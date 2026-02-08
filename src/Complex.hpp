#pragma once
#include <iostream>

class Complex
{
	public:
	// Constructors and destructor

		Complex(void);
		Complex(double real, double imaginary = 0);
		Complex(const Complex & src);
		~Complex();

	// Setters and getters

		double real() const;
		double imag() const;
		
	// Member functions

	// Operator overloads

		Complex & operator=(const Complex & rhs);
		Complex operator+(const Complex& rhs) const;
		Complex operator-(const Complex& rhs) const;
		Complex operator*(const Complex& rhs) const;

	protected:
	private:
	// Atributes

		double _r;
		double _i;

	// Private member functions

	// Friends <3
		friend std::ostream &operator<<(std::ostream &os, const Complex &obj);
};

std::ostream &operator<<(std::ostream &os, const Complex &obj);
