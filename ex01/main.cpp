#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"

template <typename T>
void linearCombTest(
	std::initializer_list<Vector<T>> u,
	std::initializer_list<T> coefs
){
	size_t i = 0;
	auto uIt = u.begin();
	auto coefsIt = coefs.begin();
	do
	{
		std::cout << "[" << i++ << "] coef: ";
		if (coefsIt == coefs.end())
			std::cout << "None";
		else
			std::cout << *coefsIt;
		std::cout << " | ";
		std::cout << "u: ";
		if (uIt == u.end())
			std::cout << "None";
		else
			std::cout << ivp(*uIt);
		std::cout << "\n";
		if (uIt != u.end())
			++uIt;
		if (coefsIt != coefs.end())
			++coefsIt;
	} while (uIt != u.end() or coefsIt != coefs.end());
	Vector<T> v = linear_combination(u, coefs);
	std::cout << "linear combination: " << ivp(v) << "\n";
}

template <typename T>
void matrixLinearCombTest(
	std::initializer_list<Matrix<T>> u,
	std::initializer_list<T> coefs
){
	size_t i = 0;
	auto uIt = u.begin();
	auto coefsIt = coefs.begin();
	do
	{
		std::cout << "[" << i++ << "] coef: ";
		if (coefsIt == coefs.end())
			std::cout << "None";
		else
			std::cout << *coefsIt;
		std::cout << " | ";
		std::cout << "u:\n";
		if (uIt == u.end())
			std::cout << "None";
		else
			std::cout << *uIt;
		std::cout << "\n";
		if (uIt != u.end())
			++uIt;
		if (coefsIt != coefs.end())
			++coefsIt;
	} while (uIt != u.end() or coefsIt != coefs.end());
	Matrix<T> A = linear_combination(u, coefs);
	std::cout << "linear combination:\n" << A << "\n";
}

void subjectTests()
{
	Test::header("Subject Tests");
	Test::add("",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,0,0},
			Vector<float>{0,1,0},
			Vector<float>{0,0,1}
		},
		std::initializer_list<float>{10, -2, 0.5}
	);
	Test::add("",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,2,3},
			Vector<float>{0,10,-100}
		},
		std::initializer_list<float>{10, -2}
	);
}

void myTests()
{
	Test::header("my Tests");
	Test::add("Empty",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{},
		std::initializer_list<float>{}
	);
	Test::add("1 vector, coef 1",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,2,3}
		},
		std::initializer_list<float>{1}
	);
	Test::add("1 vector, coef 0.5",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,2,3}
		},
		std::initializer_list<float>{0.5}
	);
	Test::add("Missing vector",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,2,3}
		},
		std::initializer_list<float>{0.5, 2}
	);
	Test::add("Missing coefs",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{1,2,3},
			Vector<float>{1,2,3}
		},
		std::initializer_list<float>{0.5}
	);
	Test::add("50\% 50\%",
		linearCombTest<float>,
		std::initializer_list<Vector<float>>{
			Vector<float>{4,3,10},
			Vector<float>{14,6,0}
		},
		std::initializer_list<float>{0.5, 0.5}
	);
}

void matrixExtraTests()
{
	Test::header("Linear Combination matrix extra Tests");
	Test::add("Empty",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{},
		std::initializer_list<float>{}
	);
	Test::add("1 Matrix, coef 1",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{
			Matrix<float>{{1, 2}, {3, 4}}
		},
		std::initializer_list<float>{1}
	);
	Test::add("1 Matrix, coef 0.5",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{
			Matrix<float>{{1, 2}, {3, 4}}
		},
		std::initializer_list<float>{0.5}
	);
	Test::add("Missing Matrix",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{
			Matrix<float>{{1, 2}, {3, 4}}
		},
		std::initializer_list<float>{0.5, 2}
	);
	Test::add("Missing coefs",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{
			Matrix<float>{{1, 2}, {3, 4}},
			Matrix<float>{{1, 2}, {3, 4}}
		},
		std::initializer_list<float>{0.5}
	);
	Test::add("50\% 50\%",
		matrixLinearCombTest<float>,
		std::initializer_list<Matrix<float>>{
			Matrix<float>{{2, 4}, {6, 8}},
			Matrix<float>{{4, 8}, {12, 16}}
		},
		std::initializer_list<float>{0.5, 0.5}
	);
}

int main()
{
	subjectTests();
	myTests();
	matrixExtraTests();
	return 0;
}
