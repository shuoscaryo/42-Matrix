#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"


void helper(float fov, float ratio, float near, float far)
{
	Matrix<float> A = projection(fov, ratio, near, far);
	std::cout << "fov: " << fov * 180/M_PI << "º ,ratio: " << ratio << " ,near: "
		<< near << " ,far: " << far << "\n";
	std::cout << "projection matrix:\n"
		<< A << "\n";
	for (size_t row = 0; row < A.shape().first; ++row)
	{
		for (size_t col = 0; col < A.shape().second; ++col)
		{
			std::cout << A[col][row];
			if (col + 1 != A.shape().first)
				std::cout << ", ";
		}
		if (row + 1 != A.shape().second)
			std::cout << "\n";
	}	
}

void myTests()
{
	Test::header("my tests");
	Test::add("",
		helper,
		M_PI/2,
		1,
		1,
		2
	);
}

void subjectTests()
{
	Test::header("subject tests");
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
