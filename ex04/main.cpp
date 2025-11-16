#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void normHelper(Vector<T> u)
{
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "u.norm_1(): " << u.norm_1() << "\n";
	std::cout << "u.norm(): " << u.norm() << "\n";
	std::cout << "u.norm_inf(): " << u.norm_inf() << "\n";
}

void subjectTests()
{
	Test::header("subject tests");
	Test::add("",
		normHelper<float>,
		Vector<float>{0,0,0}
	);
	Test::add("",
		normHelper<float>,
		Vector<float>{1,2,3}
	);
	Test::add("",
		normHelper<float>,
		Vector<float>{-1,-2}
	);
}

int main()
{
	subjectTests();
	return 0;
}
