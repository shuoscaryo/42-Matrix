#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void mul_vecHelper(const Matrix<T> & A, const Vector<T> & u)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "u: " << ivp(u) << "\n";
	std::cout << "A.mul_vec(u): " << ivp(A.mul_vec(u)) << "\n";
}

template <typename T>
void mul_matHelper(Matrix<T> A, Matrix<T> B)
{
	std::cout << "A:\n" << A << "\n";
	std::cout << "B:\n" << B << "\n";
	std::cout << "A.mul_mat(B):\n" << A.mul_mat(B) << "\n";
}

void myTests()
{
}

void subjectTests()
{
	Test::header("subject tests");
	// vectors
	Test::add("",
		mul_vecHelper<float>,
		Matrix<float>{{1,0},{0,1}},
		Vector<float>{4,2}
	);
	Test::add("",
		mul_vecHelper<float>,
		Matrix<float>{{2,0},{0,2}},
		Vector<float>{4,2}
	);
	Test::add("",
		mul_vecHelper<float>,
		Matrix<float>{{2,-2},{-2,2}},
		Vector<float>{4,2}
	);
	// matrices
	Test::add("",
		mul_matHelper<float>,
		Matrix<float>{{1,0},{0,1}},
		Matrix<float>{{1,0},{0,1}}
	);
	Test::add("",
		mul_matHelper<float>,
		Matrix<float>{{1,0},{0,1}},
		Matrix<float>{{2,1},{4,2}}
	);
	Test::add("",
		mul_matHelper<float>,
		Matrix<float>{{3,-5},{6,8}},
		Matrix<float>{{2,1},{4,2}}
	);
}

int main()
{
	subjectTests();
	myTests();
	return 0;
}
