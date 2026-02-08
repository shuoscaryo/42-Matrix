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

void myTests()
{
	Test::header("my tests");
	Test::add("single value",
		normHelper<float>,
		Vector<float>{-5}
	);
	Test::add("mix signs 3D",
		normHelper<float>,
		Vector<float>{-1, 2, -3}
	);
	Test::add("inf norm tie",
		normHelper<float>,
		Vector<float>{-7, 7, 0}
	);
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
	myTests();
	return 0;
}
