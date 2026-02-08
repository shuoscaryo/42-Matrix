#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void crossHelper(Vector<T> u, Vector<T> v)
{
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "v: " << ivp(v) << "\n";
	std::cout << "cross_product(u,v): " << ivp(cross_product(u,v)) << "\n";
}

void myTests()
{
	Test::header("my tests");
	Test::add("orthogonal x y",
		crossHelper<float>,
		Vector<float>{1,0,0},
		Vector<float>{0,1,0}
	);
	Test::add("orthogonal y z",
		crossHelper<float>,
		Vector<float>{0,1,0},
		Vector<float>{0,0,1}
	);
	Test::add("parallel vectors",
		crossHelper<float>,
		Vector<float>{1,2,3},
		Vector<float>{2,4,6}
	);
	Test::add("opposite vectors",
		crossHelper<float>,
		Vector<float>{1,0,0},
		Vector<float>{-1,0,0}
	);
	Test::add("invalid dimension",
		crossHelper<float>,
		Vector<float>{1,0},
		Vector<float>{0,1}
	);
}

void subjectTests()
{
	Test::header("subject tests");
	Test::add("",
		crossHelper<float>,
		Vector<float>{0,0,1},
		Vector<float>{1,0,0}
	);
	Test::add("",
		crossHelper<float>,
		Vector<float>{1,2,3},
		Vector<float>{4,5,6}
	);
	Test::add("",
		crossHelper<float>,
		Vector<float>{4,2,-3},
		Vector<float>{-2,-5,16}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
