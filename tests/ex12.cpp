#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.inverse():\n" << A.inverse() << "\n";
}

void myTests()
{
	Test::header("my tests");
	Test::add("Should Crash singular matrix",
		helper<float>,
		Matrix<float>{
			{1, 1},
			{1, 1}
		}
	);
	Test::add("1x1 matrix value 1",
		helper<float>,
		Matrix<float>{
			{1},
		}
	);
	Test::add("1x1 matrix value 2",
		helper<float>,
		Matrix<float>{
			{2},
		}
	);
	Test::add("Simetry matrix inverse",
		helper<float>,
		Matrix<float>{
			{0, 0, 1},
			{0, 1, 0},
			{1, 0, 0}
		}
	);
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
		Matrix<float>::identity(3).scl(2)
	);
	Test::add("",
		helper<float>,
		Matrix<float>::identity(3).scl(0.5)
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{8, 5, -2},
			{4, 7, 20},
			{7, 6, 1}
		}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
