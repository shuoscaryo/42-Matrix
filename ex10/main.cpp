#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.row_echelon():\n" << A.row_echelon() << "\n";
}

void myTests()
{
}

void subjectTests()
{
	Test::header("subject tests");
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 2},
			{3, 4}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 2},
			{2, 4}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{8, 5, -2, 4, 28},
			{4, 2.5, 20, 4, -4},
			{8, 5, 1, 4, 17}
		}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
