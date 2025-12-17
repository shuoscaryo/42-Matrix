#include <iostream>
#include <stdexcept>

#include "Matrix.tpp"
#include "Vector.tpp"
#include "Test.tpp"


void vectorBasicTests()
{
    Test::header("Vector Basic Tests");
    Test::add("Normal and Inline prints",
        []() -> void {
            Vector<float> A{1,2,3};
            std::cout << "A{1,2,3}" << "\n";
            std::cout << "inline print (wrapper):\n" << ivp(A) << "\n";
            std::cout << "normal print \"std::cout << A\":\n" << A << "\n";
        }
    );
    Test::add("Constructors",
        []() -> void {
            std::cout << "Vector<int>(): " << ivp(Vector<int>()) << "\n";
            std::cout << "Vector<int>(0): " << ivp(Vector<int>(0)) << "\n";
            std::cout << "Vector<int>(3): " << ivp(Vector<int>(3)) << "\n";
            std::cout << "Vector<float>(5): " << ivp(Vector<float>(5)) << "\n";
            std::cout << "Vector<char>(5): " << ivp(Vector<char>(5)) << "\n";
            std::cout << "Vector<int>{1,2,3}: " << ivp(Vector<int>{1,2,3}) << "\n";
            std::cout << "Vector<float>(Vector<float>{1,2,3}): " <<
                ivp(Vector<float>(Vector<float>{1,2,3})) << "\n";
        }
    );
    Test::add("Copy Constructor",
        []() -> void {
            Vector<float> A{1,2,3};
            Vector<float> B{4,5,6};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "B: " << ivp(B) << "\n";
            std::cout << "A = B\n";
            A = B;
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "B: " << ivp(B) << "\n";
            std::cout << "A[2] = 12, B[1] = 9\n";
            A[2] = 12;
            B[1] = 9;
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "B: " << ivp(B) << "\n";
        }
    );
    Test::add("Element Access",
        []() -> void {
            Vector<float> A{1,2,3,4,5,6};
            std::cout << "A:\n" << ivp(A) << "\n";
            std::cout << "A[0]: " << A[0] << "\n";
            std::cout << "A[1]: " << A[1] << "\n";
            std::cout << "A[2]: " << A[2] << "\n";
            std::cout << "A[3]: " << A[3] << "\n";
            std::cout << "A[4]: " << A[4] << "\n";
            std::cout << "A[5]: " << A[5] << "\n";
        }
    );
    Test::add("Index out of bounds",
        []() -> void {
            Vector<float> A{1,2,3,4,5,6};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A[6]: " << A[6] << "\n";
        }
    );
    Test::add("Index out of bounds",
        []() -> void {
            Vector<float> A{1,2,3,4,5,6};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A[-1]: " << A[-1] << "\n";
        }
    );
    Test::add("size",
        []() -> void {
            Vector<float> A{1,2,3};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A.size(): " << A.size() << "\n";
            Vector<float> B{};
            std::cout << "B: " << ivp(B) << "\n";
            std::cout << "B.size(): " << B.size() << "\n";
        }
    );
    Test::add("toMatrix ok",
        []() -> void {
            Vector<float> A{1,2,3,4};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A.toMatrix(2,2):\n" << A.toMatrix(2,2) << "\n";
            std::cout << "A.toMatrix(4,1):\n" << A.toMatrix(4,1) << "\n";
            std::cout << "A.toMatrix(1,4):\n" << A.toMatrix(1,4) << "\n";
        }
    );
    Test::add("toMatrix not ok",
        []() -> void {
            Vector<float> A{1,2,3,4};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A.toMatrix(1,5):\n" << A.toMatrix(1,5) << "\n";
        }
    );
    Test::add("toMatrix not ok",
        []() -> void {
            Vector<float> A{1,2,3,4};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A.toMatrix(2,3):\n" << A.toMatrix(2,3) << "\n";
        }
    );
    Test::add("toMatrix not ok",
        []() -> void {
            Vector<float> A{1,2,3,4};
            std::cout << "A: " << ivp(A) << "\n";
            std::cout << "A.toMatrix(0,4):\n" << A.toMatrix(0,4) << "\n";
        }
    );
}


void matrixBasicTests()
{
    Test::header("Matrix Basic Tests");
    Test::add("Constructors",
        []() -> void {
            std::cout << "Matrix<int>():\n" << Matrix<int>() << "\n";
            std::cout << "Matrix<int>(0,0):\n" << Matrix<int>(0,0) << "\n";
            std::cout << "Matrix<int>(3,2):\n" << Matrix<int>(3,2) << "\n";
            std::cout << "Matrix<float>(Matrix<float>(3,2).shape()):\n" <<
                Matrix<float>(Matrix<float>(3,2).shape()) << "\n";
            std::cout << "Matrix<int>{{1,2},{3,5}}:\n" <<
                Matrix<int>{{1,2},{3,5}} << "\n";
            std::cout << "Matrix<float>(Matrix<float>{{1,2},{3,5}}):\n" <<
                Matrix<float>(Matrix<float>{{1,2},{3,5}}) << "\n";
        }
    );
    Test::add("Copy Constructor",
        []() -> void {
            Matrix<float> A{{1,2,3},{4,5,6}};
            Matrix<float> B{{7,8,9}};
            std::cout << "A:\n" << A << "\n";
            std::cout << "B: " << B << "\n";
            std::cout << "A = B\n";
            A = B;
            std::cout << "A: " << A << "\n";
            std::cout << "B: " << B << "\n";
            std::cout << "A[2][0] = 12, B[2][0] = 15\n";
            A[2][0] = 12;
            B[2][0] = 15;
            std::cout << "A: " << A << "\n";
            std::cout << "B: " << B << "\n";
        }
    );
    Test::add("Not rectangular input shape",
        []() -> void {
            std::cout << "Matrix<float> A{{1,2,3},{4,5}}: "<< Matrix<float>{{1,2,3},{4,5}} << "\n";
        }
    );
    Test::add("Element Access",
        []() -> void {
            Matrix<float> A{{1,2},{3,4},{5,6}};
            std::cout << "A:\n" << A << "\n";
            std::cout << "A[0]:\n" << A[0] << "\n";
            std::cout << "A[1]:\n" << A[1] << "\n";
            std::cout << "A[0][0]: " << A[0][0] << "\n";
            std::cout << "A[0][1]: " << A[0][1] << "\n";
            std::cout << "A[0][2]: " << A[0][2] << "\n";
        }
    );
    Test::add("Index out of bounds",
        []() -> void {
            Matrix<float> A{{1,2,3}};
            std::cout << "A: " << A << "\n";
            std::cout << "A[2]: " << A[2] << "\n";
            std::cout << "A[3]: " << A[3] << "\n";
        }
    );
    Test::add("Index out of bounds",
        []() -> void {
            Matrix<float> A{{1,2,3}};
            std::cout << "A: " << A << "\n";
            std::cout << "A[2][0]: " << A[2][0] << "\n";
            std::cout << "A[2][1]: " << A[2][1] << "\n";
        }
    );
    Test::add("shape",
        []() -> void {
            Matrix<float> A{{1,2,3}};
            std::cout << "A: Matrix<float> A{{1,2,3}}\n" << A << "\nA.shape(): "
                << A.shape() << "\n";
            Matrix<float> B(0,5);
            std::cout << "B: Matrix<float> B(0,5)\n" << B << "\nB.shape(): "
                << B.shape() << "\n";
            Matrix<float> C{{}};
            std::cout << "C: Matrix<float> C{{}}:\n" << C << "\nC.shape(): "
                << C.shape() << "\n";
            Matrix<float> D{{1,2},{3,4},{5,6}};
            std::cout << "D: Matrix<float> D{{1,2},{3,4},{5,6}}:\n" << D
                << "\nD.shape(): " << D.shape() << "\n";
            Matrix<float> E(3,2);
            std::cout << "E: Matrix<float> E(3,2):\n" << E << "\nE.shape(): "
                << E.shape() << "\n";
        }
    );
    Test::add("toVector ok",
        []() -> void {
            Matrix<float> A{{1,2},{3,4},{5,6}};
            std::cout << "A:\n" << A << "\n";
            std::cout << "A.toVector(): " << ivp(A.toVector()) << "\n";
            Matrix<float> B{};
            std::cout << "B:\n" << B << "\n";
            std::cout << "B.toVector(): " << ivp(B.toVector()) << "\n";
        }
    );
    Test::add("toVector and back!",
        []() -> void {
            Matrix<float> A{{1,2},{3,4},{5,6}};
            std::cout << "A:\n" << A << "\n";
            Vector<float> B = A.toVector();
            std::cout << "B = A.toVector(): " << ivp(B) << "\n";
            std::cout << "B.toMatrix(3,2):\n" << B.toMatrix(3,2) << "\n";
        }
    );
}


int main()
{
    vectorBasicTests();
    matrixBasicTests();

    return 0;
}
