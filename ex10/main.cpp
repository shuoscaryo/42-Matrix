#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.row_echelon(): " << A.row_echelon() << "\n";
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
			{1,0},
			{0,1}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{2, -5, 0},
			{4, 3, 7},
			{-2, 3, 4}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{-2, -8, 4},
			{1, -23, 4},
			{0, 6, 4}
		}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
