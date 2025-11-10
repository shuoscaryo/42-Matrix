#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void dotHelper(Vector<T> u, const Vector<T> &v)
{
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "v: " << ivp(v) << "\n";
	std::cout << "u.dot(v): " << u.dot(v) << "\n";
}

void subjectTests()
{
	Test::header("dot product subject tests");
	Test::add("",
		dotHelper<float>,
		Vector<float>{0,0},
		Vector<float>{1,1}
	);
	Test::add("",
		dotHelper<float>,
		Vector<float>{1,1},
		Vector<float>{1,1}
	);
	Test::add("",
		dotHelper<float>,
		Vector<float>{-1,6},
		Vector<float>{3,2}
	);
}

int main()
{
	subjectTests();
	return 0;
}
