#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void helper(const Matrix<T> & A)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "A.determinant(): " << A.determinant() << "\n";
}

void myTests()
{
	Test::header("my tests");
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 0, 0},
			{0, 1, 0},
			{1, 2, 3},
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},
			{2, 3, 1}
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
}

void subjectTests()
{
	Test::header("subject tests");
	Test::add("",
		helper<float>,
		Matrix<float>{
			{1, -1},
			{-1, 1}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{2, 0, 0},
			{0, 2, 0},
			{0, 0, 2}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{8, 5, -2},
			{4, 7, 20},
			{7, 6, 1}
		}
	);
	Test::add("",
		helper<float>,
		Matrix<float>{
			{8, 5, -2, 4},
			{4, 2.5, 20, 4},
			{8, 5, 1, 4},
			{28, -4, 17, 1},
		}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
