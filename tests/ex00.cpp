#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"


template <typename T>
void addVector(Vector<T> A,const Vector<T>& B, bool isInline)
{
    if (isInline)
    {
        std::cout << "A: " << ivp(A) << "\n";
        std::cout << "B: " << ivp(B) << "\n";
        A.add(B);
        std::cout << "A + B: " << ivp(A) << "\n";
    } else
    {
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        A.add(B);
        std::cout << "A + B:\n" << A << "\n";
    }
}

template <typename T>
void subVector(Vector<T> A,const Vector<T>& B, bool isInline)
{
    if (isInline)
    {
        std::cout << "A: " << ivp(A) << "\n";
        std::cout << "B: " << ivp(B) << "\n";
        A.sub(B);
        std::cout << "A - B: " << ivp(A) << "\n";
    } else
    {
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        A.sub(B);
        std::cout << "A - B:\n" << A << "\n";
    }
}

template <typename T>
void sclVector(Vector<T> A,const T& x, bool isInline)
{
    if (isInline)
    {
        std::cout << "A: " << ivp(A) << "\n";
        std::cout << "x: " << x << "\n";
        A.scl(x);
        std::cout << "A * x: " << ivp(A) << "\n";
    } else
    {
        std::cout << "A:\n" << A << "\n";
        std::cout << "x: " << x << "\n";
        A.scl(x);
        std::cout << "A * x:\n" << A << "\n";
    }
}

template <typename T>
void addMatrix(Matrix<T> A,const Matrix<T>& B)
{
    std::cout << "A:\n" << A << "\n";
    std::cout << "B:\n" << B << "\n";
    A.add(B);
    std::cout << "A + B:\n" << A << "\n";
}

template <typename T>
void subMatrix(Matrix<T> A,const Matrix<T>& B)
{
    std::cout << "A:\n" << A << "\n";
    std::cout << "B:\n" << B << "\n";
    A.sub(B);
    std::cout << "A - B:\n" << A << "\n";
}

template <typename T>
void sclMatrix(Matrix<T> A,const T& x)
{
    std::cout << "A:\n" << A << "\n";
    std::cout << "x: " << x << "\n";
    A.scl(x);
    std::cout << "A * x:\n" << A << "\n";
}

void subjectTests()
{
    Test::header("Subject Tests");
    Test::add("Vector add",
        addVector<float>,
        Vector<float>{2, 3},
        Vector<float>{5, 7},
        false
    );
    Test::add("Vector sub",
        subVector<float>,
        Vector<float>{2, 3},
        Vector<float>{5, 7},
        false
    );
    Test::add("Vector scl",
        sclVector<float>,
        Vector<float>{2, 3},
        float(2),
        false
    );
    Test::add("Matrix add",
        addMatrix<float>,
        Matrix<float>{{1, 2}, {3, 4}},
        Matrix<float>{{7, 4}, {-2, 2}}
    );
    Test::add("Matrix sub",
        subMatrix<float>,
        Matrix<float>{{1, 2}, {3, 4}},
        Matrix<float>{{7, 4}, {-2, 2}}
    );
    Test::add("Matrix scl",
        sclMatrix<float>,
        Matrix<float>{{1, 2}, {3, 4}},
        float(2)
    );

}

void vectorEx00Tests()
{
    Test::header("Vector add sub scl tests");
    Test::add("int addition",
        addVector<int>,
        Vector<int>{1,2,3,4,5,6},
        Vector<int>{1,-1,1,-1,1,-1},
        true
    );
    Test::add("int addition size 0",
        addVector<int>,
        Vector<int>{},
        Vector<int>{},
        true
    );
    Test::add("float addition",
        addVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        Vector<float>{1.1, -1.1, 1.1, -1.1, 1.1, -1.1},
        true
    );
    Test::add("float addition different size",
        addVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        Vector<float>{1.1, -1.1, 1.1, -1.1, 1.1},
        true
    );
    Test::add("int substraction",
        subVector<int>,
        Vector<int>{1,2,3,4,5,6},
        Vector<int>{1,-1,1,-1,1,-1},
        true
    );
    Test::add("int substraction size 0",
        subVector<int>,
        Vector<int>{},
        Vector<int>{},
        true
    );
    Test::add("float substraction",
        subVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        Vector<float>{1.1, -1.1, 1.1, -1.1, 1.1, -1.1},
        true
    );
    Test::add("float substraction different size",
        subVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        Vector<float>{1.1, -1.1, 1.1, -1.1, 1.1},
        true
    );
    Test::add("int scalar multiplication",
        sclVector<int>,
        Vector<int>{1,2,3,4,5,6},
        int(3),
        true
    );
    Test::add("int scalar multiplication",
        sclVector<int>,
        Vector<int>{1,2,3,4,5,6},
        int(0),
        true
    );
    Test::add("float scalar multiplication",
        sclVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        float(1.1),
        true
    );
    Test::add("float scalar multiplication",
        sclVector<float>,
        Vector<float>{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6},
        float(0),
        true
    );
}

void matrixEx00Tests()
{
    Test::header("Matrix add sub scl tests");
    Test::add("int addition",
        addMatrix<int>,
        Matrix<int>{{1,2},{3,4}},
        Matrix<int>{{1,1},{1,1}}
    );
    Test::add("int addition shape (1, 1)",
        addMatrix<int>,
        Matrix<int>{{1}},
        Matrix<int>{{1}}
    );
    Test::add("int addition shape (0, 0)",
        addMatrix<int>,
        Matrix<int>{{}},
        Matrix<int>{{}}
    );
    Test::add("float addition",
        addMatrix<float>,
        Matrix<float>{{1.1, 2.2, 3.3}, {4.4 ,5.5 ,6.6}},
        Matrix<float>{{1.1, -1.1, 1.1}, {-1.1, 1.1, -1.1}}
    );
    Test::add("float addition different size",
        addMatrix<float>,
        Matrix<float>{{1.1, 2.2, 3.3} ,{4.4 ,5.5 ,6.6}},
        Matrix<float>{{1.1, -1.1}, {1.1, 1.1}}
    );
    Test::add("int substraction",
        subMatrix<int>,
        Matrix<int>{{1,2},{3,4}},
        Matrix<int>{{1,1},{1,1}}
    );
    Test::add("int substraction shape (1, 1)",
        subMatrix<int>,
        Matrix<int>{{1}},
        Matrix<int>{{1}}
    );
    Test::add("int substraction shape (0, 0)",
        subMatrix<int>,
        Matrix<int>{{}},
        Matrix<int>{{}}
    );
    Test::add("float substraction",
        subMatrix<float>,
        Matrix<float>{{1.1, 2.2, 3.3}, {4.4 ,5.5 ,6.6}},
        Matrix<float>{{1.1, -1.1, 1.1}, {-1.1, 1.1, -1.1}}
    );
    Test::add("int scalar multiplication",
        sclMatrix<int>,
        Matrix<int>{{1,2,3,4,5,6}},
        int(3)
    );
    Test::add("int scalar multiplication",
        sclMatrix<int>,
        Matrix<int>{{1,2},{3,4},{5,6}},
        int(3)
    );
    Test::add("float scalar multiplication",
        sclMatrix<float>,
        Matrix<float>{{1.1, 2.2, 3.3} ,{4.4 ,5.5 ,6.6}},
        float(1.1)
    );
    Test::add("float scalar multiplication",
        sclMatrix<float>,
        Matrix<float>{{1.1, 2.2, 3.3 ,4.4 ,5.5 ,6.6}},
        float(2.2)
    );
}

int main() {

    subjectTests();
    vectorEx00Tests();
    matrixEx00Tests();

    return 0;
}
