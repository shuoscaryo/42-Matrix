#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>
#include <utility>
#include "Vector.tpp"

template <typename T> class Matrix;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &obj);

template <typename T>
class Matrix
{
	public:
	// Constructors and destructor

		Matrix();
		Matrix(const Matrix<T> & rhs);
		Matrix(size_t rows, size_t cols);
		Matrix(std::pair<size_t, size_t> shape);
		Matrix(const std::initializer_list<std::initializer_list<T>> & rhs);
		~Matrix();

	// Operator overloads

		Matrix<T> & operator=(const Matrix<T> & rhs);
		Vector<T> & operator[](size_t i);
		const Vector<T> & operator[](size_t i) const;
		Matrix<T> operator+(const Matrix<T> & rhs);
		Matrix<T> operator-(const Matrix<T> & rhs);
		Matrix<T> operator*(const T & rhs);

	// Setters and getters
		

	// Member functions

		std::pair<size_t, size_t> shape() const;
		bool isSquare() const;
		Vector<T> toVector() const;
		static Matrix<T> identity(size_t size);

		Matrix<T> & add(const Matrix<T> & rhs);
		Matrix<T> & sub(const Matrix<T> & rhs);
		Matrix<T> & scl(const T & rhs);

		Vector<T> mul_vec(const Vector<T> & vec) const;
		Matrix<T> mul_mat(const Matrix<T> & mat) const;

		T trace() const;

		Matrix<T> transpose() const;

		Matrix<T> row_echelon() const;

		T determinant() const;

		Matrix<T> inverse() const;

		size_t rank() const;


	protected:
	private:
	// Atributes

		std::unique_ptr<Vector<T>[]> _elements; // Malloc of _cols length containing vectors of _rows length
		size_t _rows;
		size_t _cols;

	// Private member functions


	// Friends <3

		friend std::ostream &operator<< <T>(std::ostream &os, const Matrix<T> &obj);
		// also a print for std::pair<size_t,size_t> for shape print
};

// CONSTRUCTORS

template <typename T>
Matrix<T>::Matrix():
	_elements(nullptr),
	_rows(0),
	_cols(0)
{}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs)
{
	*this = rhs;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
	if (cols == 0 or rows == 0)
	{
		_cols = _rows = 0;
		return;
	}
	_rows = rows;
	_cols = cols;
	_elements = std::make_unique<Vector<T>[]>(cols);
	for (size_t i = 0; i < cols; ++i)
		_elements[i] = Vector<T>(rows);
}

template <typename T>
Matrix<T>::Matrix(std::pair<size_t, size_t> shape):
	Matrix(shape.first, shape.second)
{}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> & rhs)
{
	// Get sizes
	_rows = rhs.size();
	if (_rows == 0)
		return;
	_cols = rhs.begin()->size();
	if (_cols == 0)
	{
		_rows = 0;
		return;
	}
	// Allocate memory
	_elements = std::make_unique<Vector<T>[]>(_cols);
	for (size_t i = 0; i < _cols; ++i)
		_elements[i] = Vector<T>(_rows);
	// Fill values
	size_t j = 0;
	for (auto & row: rhs)
	{
		if (row.size() != _cols)
			throw std::invalid_argument("Matrix constructor initializer_list: rows of different size");
		size_t i = 0;
		for (auto & col: row)
			_elements[i++][j] = col;
		j++;
	}
}

template <typename T>
Matrix<T>::~Matrix()
{}

// OPERATORS

template <typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs)
{
	_rows = rhs._rows;
	_cols = rhs._cols;
	_elements = std::make_unique<Vector<T>[]>(_cols);
	for (size_t i = 0; i < _cols; ++i)
		_elements[i] = rhs[i];
	return *this;
}

template <typename T>
Vector<T> & Matrix<T>::operator[](size_t i)
{
	if (i >= _cols)
		throw std::out_of_range("Matrix::[] out of range");
	return _elements[i];
}

template <typename T>
const Vector<T> & Matrix<T>::operator[](size_t i) const
{
	if (i >= _cols)
		throw std::out_of_range("Matrix::[] out of range");
	return _elements[i];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs)
{
	Matrix<T> output = *this;
	output.add(rhs);
	return output;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & rhs)
{
	Matrix<T> output = *this;
	output.sub(rhs);
	return output;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T & rhs)
{
	Matrix<T> output = *this;
	output.scl(rhs);
	return output;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &obj)
{
	if (obj._cols == 0 or obj._rows == 0)
	{
		os << "[]";
		return os;
	}
	for (size_t row = 0; row < obj._rows; ++row)
	{
		os << "[";
		for (size_t col = 0; col < obj._cols; ++col)
		{
			os << obj[col][row];
			if (col != obj._cols - 1)
				os << " ";
		}
		os << "]";
		if (row != obj._rows - 1)
			os << std::endl;
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::pair<size_t, size_t> &obj)
{
	os << "(" << obj.first << ", " << obj.second << ")";
	return os;
}

// MEMBER FUNCTIONS

template <typename T>
std::pair<size_t, size_t> Matrix<T>::shape() const
{
    return {_rows, _cols};
}

template <typename T>
bool Matrix<T>::isSquare() const
{
    return _rows == _cols;
}

template <typename T>
Vector<T> Matrix<T>::toVector() const
{
	Vector<T> output(_rows * _cols);
	size_t i = 0;
	for (size_t row = 0; row < _rows; ++row)
		for (size_t col = 0; col < _cols; ++col)
			output[i++] = _elements[col][row];
	return output;
}

template <typename T>
Matrix<T> Matrix<T>::identity(size_t size)
{
	// Creates an identity matrix with specified size
	Matrix<T> output(size,size);
	for (size_t i = 0; i < size; ++i)
		output[i][i] = 1;
	return output;
}

// EX00

template <typename T>
Matrix<T> & Matrix<T>::add(const Matrix<T> & rhs)
{
	if (this->shape() != rhs.shape())
		throw std::invalid_argument("Matrix ::add: shape mismatch");
	for (size_t col = 0; col < _cols; ++col)
		_elements[col].add(rhs[col]);

	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::sub(const Matrix<T> & rhs)
{
	if (this->shape() != rhs.shape())
		throw std::invalid_argument("Matrix::sub shape mismatch");
	for (size_t col = 0; col < _cols; ++col)
		_elements[col].sub(rhs[col]);

	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::scl(const T & rhs)
{
	for (size_t col = 0; col < _cols; ++col)
		_elements[col].scl(rhs);

	return *this;
}

// EX01

template <typename T>
Matrix<T> linear_combination(
	std::initializer_list<Matrix<T>> u,
	std::initializer_list<T> coefs
)
{
	if (u.size() == 0)
		return Matrix<T>();
	if (u.size() != coefs.size())
		throw std::runtime_error("linear_combination different \"u\" and \"coefs\" sizes.");
	Matrix<T> output(u.begin()->shape());
	auto uIt = u.begin();
	auto coefsIt = coefs.begin();
	do
	{
		Matrix<T> vScaled(*uIt);
		vScaled.scl(*coefsIt);
		output.add(vScaled);
		++uIt;
		++coefsIt;
	} while(uIt != u.end());
	return output;	
}

// EX07

template <typename T>
Vector<T> Matrix<T>::mul_vec(const Vector<T> & vec) const
{
	if (this->_cols != vec.size())
		throw std::runtime_error("Matrix::mul_vec Matrix columns must be same as vec size");
	Vector<T> output(this->_rows);
	for (size_t row = 0; row < this->_rows; ++row)
	{
		T sum = (*this)[0][row] * vec[0];
		for (size_t col = 1; col < this->_cols; ++col)
			sum += (*this)[col][row] * vec[col];
		output[row] = sum;
	}
	return output;
}

template <typename T>
Matrix<T> Matrix<T>::mul_mat(const Matrix<T> & mat) const
{
	if (this->_cols != mat._rows or this->_cols != mat._cols)
		throw std::runtime_error("Matrix::mul_mat Invalid shapes to multiply");
	Matrix<T> output(this->_rows, mat._cols);
	// A*B multiplication
	// for each A row
	for (size_t row = 0; row < this->_rows; ++row)
	{
		// for each B column
		for (size_t col = 0; col < mat._cols; ++col)
		{
			// multiply elements
			T sum = (*this)[0][row] * mat[col][0];
			for (size_t i = 1; i < this->_cols; ++i)
				sum += (*this)[i][row] * mat[col][i];
			output[col][row] = sum;
		}
	}
	return output;
}

// EX08

template <typename T>
T Matrix<T>::trace() const
{
	if (!isSquare())
		throw std::runtime_error("Matrix::trace trace only available for square matrices");
	if (_cols == 0)
		return T{};
	T output = (*this)[0][0];
	for (size_t i = 1; i < _cols; ++i)
		output += (*this)[i][i];
	return output;
}

// EX09

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
	Matrix<T> output(_cols, _rows);
	for (size_t row = 0; row < _rows; ++row)
	{
		for (size_t col = 0; col < _cols; ++col)
			output[row][col] = (*this)[col][row];
	}
	return output;
}

// EX10

template <typename T>
static int _findNonZeroRow(const Matrix<T> & A, size_t from, size_t col)
{
	// returns the first row whose [col] position is not 0.
	const size_t rowLen = A.shape().first;
	for (size_t row = from; row < rowLen; ++row)
		if (A[col][row] != 0)
			return row;
	return -1;
}

template <typename T>
static void _swapRows(Matrix<T> &A, size_t row1, size_t row2)
{
	const size_t colLen = A.shape().second;
	for (size_t col = 0; col < colLen; ++col)
		std::swap(A[col][row1], A[col][row2]);
}

template <typename T>
static void _scaleRow(
	Matrix<T> &A,
	size_t row,
	const T & multiplier,
	size_t startFrom = 0
)
{
	const size_t colLen = A.shape().second;
	// Divide the whole row by the first element, so the first one becomes 1
	for (size_t i = startFrom; i < colLen; ++i)
		A[i][row] *= multiplier;
}

template <typename T>
static void _substractRow(
	Matrix<T> &A,
	size_t refRow,
	size_t row,
	const T & multiplier, 
	size_t startFrom = 0
)
{
	// row - refRow * multiplier
	const size_t colLen = A.shape().second;
	// substract the refRow multiplied to the target row
	for (size_t i = startFrom; i < colLen; ++i)
		A[i][row] -= A[i][refRow] * multiplier;
}

template <typename T>
Matrix<T> Matrix<T>::row_echelon() const
{
	// It's reduced row echelon not normal one!
	// Subject examples normalize left most pivot of each row to 1 and clears
	// all other rows with the current one, leaving the simplest vectors for
	// the space
	Matrix<T> output((*this));
	// workRow is the first row from where perform operations 
	size_t workRow = 0;
	// Iterate columns to remove every element but the pivot
	for (size_t col = 0; col < _cols; ++col)
	{
		// Find first row that has a value different than 0 to use as pivot
		const int pivotRow = _findNonZeroRow(output, workRow, col);
		if (pivotRow == -1)
			continue;
		// If the row used as pivot is not the first, make it first
		if (pivotRow != int(workRow))
			_swapRows(output, pivotRow, workRow);
		// Scale the row so it starts with 1 and start from the curr col
		_scaleRow(output, workRow, 1 / output[col][workRow], col);
		// simplify rest of rows in same column
		for (size_t row = 0; row < _rows; ++row)
			if (row != workRow)
				_substractRow(output, workRow, row,
					output[col][row] / output[col][workRow], col);
		// update the work row so the current pivot is not used more
		++workRow;
	}
	return output;
}

// EX11

template <typename T>
T Matrix<T>::determinant() const
{
	// Diagonalize Matrix and determinant is only the diagonal part :O
	// (not used) Operation of scaling a row scales determinant the same amount
	// eg.     |1 2|             |1*2 2*2| 
	//     det |3 4| = -2 -> det | 3   4 | = -2 * 2
	// Operation of swaping rows changes the sign of determinant
	// eg.     |1 2|             |3 4| 
	//     det |3 4| = -2 -> det |1 2| = 2
	// Operation of substracting a row to another doesn't change derminant
	// eg.     |1 2|             | 1   2 | 
	//     det |3 4| = -2 -> det |3-1 4-2| = -2
	if (!isSquare())
		throw std::runtime_error("Matrix::determinant non square matrix");
	if (_rows == 0)
		throw std::runtime_error("Matrix::determinant shape (0,0)");
	Matrix<T> output((*this));
	// workRow is the first row from where perform operations
	size_t workRow = 0;
	// flag false = -1, flag true = +1
	bool flag = true;
	// Iterate columns to remove every element but the pivot
	for (size_t col = 0; col < _cols - 1; ++col)
	{
		// Find first row that has a value different than 0 to use as pivot
		const int pivotRow = _findNonZeroRow(output, workRow, col);
		if (pivotRow == -1)
			continue;
		// If the row used as pivot is not the first, make it first
		if (pivotRow != int(workRow))
		{
			flag = !flag;
			_swapRows(output, pivotRow, workRow);
		}
		for (size_t row = workRow + 1; row < _rows; ++row)
			_substractRow(output, workRow, row,
				output[col][row] / output[col][workRow], col);
		// update the work row so the current pivot is not used more
		++workRow;
	}
	// Calculate the multiplication of the diagonal. Only non zero term in
	// determinant
	T sum = output[0][0];
	for (size_t i = 1; i < _rows; ++i)
		sum *= output[i][i];
	return flag == true ? sum: -sum;
}

// EX12

template <typename T>
Matrix<T> Matrix<T>::inverse() const
{
	// To calculate inverse we start from defining what should the inverse do
	// A * A^-1 = I
	// If we apply consecutive multiplications to both sides we can change A
	// so it becomes I
	// (E1 * E2 * ...) * A * A^-1 = (E1 * E2 * ...) * I
	// (E1 * E2 * ...) * A = I
	// The Ei operations are swap, scale and add one row to another.
	// Every operation is done for "output" and "A" equally.
	if (!isSquare())
		throw std::runtime_error("Matrix::inverse non square matrix");
	if (_rows == 0)
		throw std::runtime_error("Matrix::inverse shape (0,0)");
	Matrix<T> output = Matrix<T>::identity(_cols);
	Matrix<T> A(*this);
	// workRow is the first row from where perform operations
	size_t workRow = 0;
	// Iterate columns to remove every element but the pivot
	for (size_t col = 0; col < _cols; ++col)
	{
		// Find first row that has a value different than 0 to use as pivot
		const int pivotRow = _findNonZeroRow(A, workRow, col);
		if (pivotRow == -1)
			throw std::runtime_error("Matrix::inverse singular matrix");
		// If the row used as pivot is not the first, make it first
		if (pivotRow != int(workRow))
		{
			_swapRows(output, pivotRow, workRow);
			_swapRows(A, pivotRow, workRow);
		}
		// Scale A so it starts with one, apply same factor to output
		T sclFactor = 1 / A[col][workRow];
		_scaleRow(A, workRow, sclFactor, col);
		_scaleRow(output, workRow, sclFactor);
		// simplify rest of rows in same column
		for (size_t row = 0; row < _rows; ++row)
			if (row != workRow)
			{
				T subFactor = A[col][row] / A[col][workRow];
				_substractRow(A, workRow, row, subFactor, col);
				_substractRow(output, workRow, row, subFactor);
			}
		// update the work row so the current pivot is not used more
		++workRow;
	}
	return output;
}

// EX13

template <typename T>
size_t Matrix<T>::rank() const
{
	// Rank is how many pivot points we have
	Matrix<T> A(*this);
	// workRow is the first row from where perform operations
	size_t workRow = 0;
	size_t rank = 0;
	// Iterate columns to remove every element but the pivot
	for (size_t col = 0; col < _cols; ++col)
	{
		// Find first row that has a value different than 0 to use as pivot
		const int pivotRow = _findNonZeroRow(A, workRow, col);
		if (pivotRow == -1)
			continue;
		++rank;
		// If the row used as pivot is not the first, make it first
		if (pivotRow != int(workRow))
			_swapRows(A, pivotRow, workRow);
		// Scale A so it starts with one, apply same factor to output
		T sclFactor = 1 / A[col][workRow];
		_scaleRow(A, workRow, sclFactor, col);
		// simplify rest of rows in same column
		for (size_t row = 0; row < _rows; ++row)
			if (row != workRow)
			{
				T subFactor = A[col][row] / A[col][workRow];
				_substractRow(A, workRow, row, subFactor, col);
			}
		// update the work row so the current pivot is not used more
		++workRow;
	}
	return rank;
}

// EX14