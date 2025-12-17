#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"
#include "Complex.hpp"

void TestsEx00()
{
	Test::header("Tests Ex00");
    Vector<Complex> u = {
        Complex(1,1),
        Complex(0,1),
        Complex(-6,-4)
    };
    Vector<Complex> v = {
        Complex(0,0),
        Complex(1,0),
        Complex(3,-2)
    };
    Test::add("Vector addition",
		[&v,&u]() -> void
        {
            std::cout << "u: " << ivp(u, ", ") << "\n";
            std::cout << "v: " << ivp(v, ", ") << "\n";
            std::cout << "u+v: " << ivp(u+v, ", ") << "\n";
            std::cout << "v+u: " << ivp(v+u, ", ") << "\n";
        }
	);
    Test::add("Vector substraction",
		[&v,&u]() -> void
        {
            std::cout << "u: " << ivp(u, ", ") << "\n";
            std::cout << "v: " << ivp(v, ", ") << "\n";
            std::cout << "u-v: " << ivp(u-v, ", ") << "\n";
            std::cout << "v-u: " << ivp(v-u, ", ") << "\n";
        }
	);
    Test::add("Vector scale",
		[&u]() -> void
        {
            Complex scale(3,2);
            std::cout << "u: " << ivp(u, ", ") << "\n";
            std::cout << "scale: " << scale << "\n";
            std::cout << "u*scale: " << ivp(u*scale, ", ") << "\n";
        }
	);
}

template <typename T>
void linearCombTest(
	std::initializer_list<Vector<T>> u,
	std::initializer_list<T> coefs
){
	size_t i = 0;
	auto uIt = u.begin();
	auto coefsIt = coefs.begin();
	do
	{
		std::cout << "[" << i++ << "] coef: ";
		if (coefsIt == coefs.end())
			std::cout << "None";
		else
			std::cout << *coefsIt;
		std::cout << " | ";
		std::cout << "u: ";
		if (uIt == u.end())
			std::cout << "None";
		else
			std::cout << ivp(*uIt, ", ");
		std::cout << "\n";
		if (uIt != u.end())
			++uIt;
		if (coefsIt != coefs.end())
			++coefsIt;
	} while (uIt != u.end() or coefsIt != coefs.end());
	Vector<T> v = linear_combination(u, coefs);
	std::cout << "linear combination: " << ivp(v, ", ") << "\n";
}

void TestsEx01()
{
	Test::header("Tests Ex01");
	Test::add("",
        linearCombTest<Complex>,
        std::initializer_list<Vector<Complex>>{
            Vector<Complex>{
                Complex(4,3),
                Complex(3,2),
                Complex(10,1)
            },
            Vector<Complex>{
                Complex(14,1),
                Complex(6,3),
                Complex(0,0)
            }
        },
        std::initializer_list<Complex>{
            Complex(0.5,0),
            Complex(0,0.5)
        }
    );
}

template <typename V>
void lerpHelper(const V &u, const V &v, float t)
{
	std::cout << "u:\n" << u << "\n";
	std::cout << "v:\n" << v << "\n";
	std::cout << "t: " << t << "\n";
	V output = lerp(u,v,t);
	std::cout << "lerp:\n" << output << "\n";
}

void TestsEx02()
{
    Test::header("Tests Ex02");
    Test::add("",
        []() -> void {
            Vector<Complex> u{
                Complex(2,1),
                Complex(1,4)
            };
            Vector<Complex> v{
                Complex(4,-1),
                Complex(2,-3)
            };
            float t = 0.3;
            std::cout << "u: " << ivp(u, ", ") << "\n";
            std::cout << "v: " << ivp(v, ", ") << "\n";
            std::cout << "t: " << t << "\n";
            Vector<Complex> output = lerp(u,v,t);
            std::cout << "lerp: " << ivp(output, ", ") << "\n";
        }
	);
	Test::add("",
        []() -> void {
            Matrix<Complex> u{
                {Complex(2,1), Complex(1,4)},
                {Complex(20,10), Complex(10,40)}
            };
            Matrix<Complex> v{
                {Complex(5,6), Complex(1,4)},
                {Complex(23,15), Complex(0,0)}
            };
            float t = 0.5;
            std::cout << "u:\n" << u << "\n";
            std::cout << "v:\n" << v << "\n";
            std::cout << "t: " << t << "\n";
            Matrix<Complex> output = lerp(u,v,t);
            std::cout << "lerp:\n" << output << "\n";
        }
	);
}

template <typename T>
void dotHelper(Vector<T> u, const Vector<T> &v)
{
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "v: " << ivp(v) << "\n";
	std::cout << "u.dot(v): " << u.dot(v) << "\n";
}

void TestsEx03()
{
    Test::header("Tests Ex03");
	Test::add("",
		dotHelper<Complex>,
		Vector<float>{0,0},
		Vector<float>{1,1}
	);
}

int main()
{
	TestsEx00();
	TestsEx01();
	TestsEx02();
	TestsEx03();
	return 0;
}
