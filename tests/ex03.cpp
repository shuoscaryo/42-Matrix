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

void myTests()
{
	Test::header("my tests");
	Test::add("1D dot product",
		dotHelper<float>,
		Vector<float>{5},
		Vector<float>{-2}
	);
	Test::add("orthogonal vectors",
		dotHelper<float>,
		Vector<float>{1,0,0},
		Vector<float>{0,1,0}
	);
	Test::add("invalid dimension",
		dotHelper<float>,
		Vector<float>{1,2},
		Vector<float>{1,2,3}
	);
}

void subjectTests()
{
	Test::header("subject tests");
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
	myTests();
	return 0;
}
