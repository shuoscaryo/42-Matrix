#pragma once
#include <iostream>

class Complex
{
	public:
	// Constructors and destructor

		Complex(void);
		Complex(float real, float imaginary = 0);
		Complex(const Complex & src);
		~Complex();

	// Setters and getters
		
	// Member functions

	// Operator overloads

		Complex & operator=(const Complex & rhs);
		Complex operator+(const Complex& rhs) const;
		Complex operator-(const Complex& rhs) const;
		Complex operator*(const Complex& rhs) const;

	protected:
	private:
	// Atributes

		float _r;
		float _i;

	// Private member functions

	// Friends <3
		friend std::ostream &operator<<(std::ostream &os, const Complex &obj);
};

std::ostream &operator<<(std::ostream &os, const Complex &obj);
