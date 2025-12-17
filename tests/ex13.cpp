#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.rank(): " << A.rank() << "\n";
}

void myTests()
{
	Test::header("my tests");
}

void subjectTests()
{
	Test::header("subject tests");
	Test::add("",
		helper<float>,
		Matrix<float>::identity(3)
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 2, 0, 0},
			{2, 4, 0, 0},
			{-1, 2, 1, 1},
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{8, 5, -2},
			{4, 7, 20},
			{7, 6, 1},
			{21, 18, 7}
		}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
