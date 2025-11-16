#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.transpose():\n" << A.transpose() << "\n";
}

void myTests()
{
	Test::header("my tests");
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1,2,3},
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1},
			{2},
			{3},
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 2, 3},
			{4, 5, 6},
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		}
	);
}

void subjectTests()
{
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
