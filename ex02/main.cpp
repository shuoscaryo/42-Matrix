#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename V>
void lerpHelper(const V &u, const V &v, float t)
{
	std::cout << "u:\n" << u << "\n";
	std::cout << "v:\n" << v << "\n";
	std::cout << "t: " << t << "\n";
	V output = lerp(u,v,t);
	std::cout << "lerp:\n" << output << "\n";
}

void subjectTests()
{
	Test::header("Subject Tests");
	Test::add("",
		lerpHelper<float>,
		0,
		1,
		0
	);
	Test::add("",
		lerpHelper<float>,
		0,
		1,
		1
	);
	Test::add("",
		lerpHelper<float>,
		0,
		1,
		0.5
	);
	Test::add("",
		lerpHelper<float>,
		21,
		42,
		0.3
	);
	Test::add("",
		lerpHelper<Vector<float>>,
		Vector<float>{2,1},
		Vector<float>{4,2},
		0.3
	);
	Test::add("",
		lerpHelper<Matrix<float>>,
		Matrix<float>{{2,1},{3,4}},
		Matrix<float>{{20,10},{30,40}},
		0.5
	);
}

int main()
{
	subjectTests();
	return 0;
}
