#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"


void helper(float fov, float ratio, float near, float far)
{
	float fovRad = fov / 180.0 * M_PI;
	Matrix<float> A = projection(fovRad, ratio, near, far);
	std::cout << "fov: " << fov << "º, ratio: " << ratio << ", near: "
		<< near << ", far: " << far << "\n";
	std::cout << "projection matrix:\n";
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
		90.0f,
		1,
		1,
		2
	);
	Test::add("",
		helper,
		45,
		3,
		1,
		2
	);
}

int main()
{
	myTests();
	return 0;
}
