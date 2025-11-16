#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void cosHelper(Vector<T> u, Vector<T> v)
{
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "v: " << ivp(v) << "\n";
	std::cout << "cos(u,v): " << angle_cos(u,v) << "\n";
}

void myTests()
{
	Test::header("dot product my tests");
	Test::add("",
		cosHelper<float>,
		Vector<float>{1,1,1},
		Vector<float>{1,1,-2}
	);
}

void subjectTests()
{
	Test::header("dot product subject tests");
	Test::add("",
		cosHelper<float>,
		Vector<float>{1,0},
		Vector<float>{1,0}
	);
	Test::add("",
		cosHelper<float>,
		Vector<float>{1,0},
		Vector<float>{0,1}
	);
	Test::add("",
		cosHelper<float>,
		Vector<float>{2,1},
		Vector<float>{4,2}
	);
	Test::add("",
		cosHelper<float>,
		Vector<float>{1,2,3},
		Vector<float>{4,5,6}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
