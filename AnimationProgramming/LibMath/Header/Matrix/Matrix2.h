#ifndef __LIBMATH__MATRIX__MATRIX2_H__
#define __LIBMATH__MATRIX__MATRIX2_H__

#pragma region Header

/// Standard librairies
#include <iostream>

/// Matrix librairies
#include "Matrix3.h"

#pragma endregion

namespace LibMath
{
	class Matrix3;

	class Matrix2
	{
	public:

#pragma region Constructor

		///Constructor

									/// Constructor without parameter to set to identity with diagonal of 1
									Matrix2();
									/// Constructor with one parameter to set to identity with diagonal of the float value
		explicit					Matrix2(float);
									/// Constructor with four parameters to set all the value with float value
									Matrix2(float, float, float, float);
#pragma endregion

#pragma region Other functions

		///Other functions

					/// Return the determinant of a 2x2 matrix
					float			Determinant(const Matrix2&) const;
					/// Set the identity matrix 1.f by default
					Matrix2			Identity(float _scalar = 1.f);
					/// Swap rows & columns, then return this new matrix
					Matrix2			Transpose(const Matrix2&);
					/// Return the matrix of every submatrix for every elements in the matrix
					Matrix2			Minor(const Matrix2&);
					/// Function to change the order between row and column of the matrix
					Matrix2&		Adjugate(const Matrix2&);
					/// Reverse the matrix between row major to column major or column major to row major
					Matrix2			Inverse(const Matrix2&) const;
					/// Return the determinant of a 2x2 matrix
					Matrix2&		GetMatrix2(const Matrix3&, int, int);
#pragma endregion

#pragma region In class operator

		///In class operator

					/// To access to a value by the index associate into the matrix
					float*			operator[](int);
					/// To access to a value by the index associate into the matrix
					const float*	operator[](int) const;

					/// Set the value of 1 matrix equal to another
					Matrix2			operator=(const Matrix2&);
					/// Add to matrices together
					Matrix2			operator+(const Matrix2&) const;
					/// Subtract to matrices
					Matrix2			operator-(const Matrix2&) const;
					/// Multiply 2 matrices together
					Matrix2			operator*(const Matrix2&) const;
					/// Multiply the matrix by a float
					Matrix2			operator*(float);

					/// Check the equality between two matrix
					bool			operator==(const Matrix2) const;
					/// Check the inequality between two matrix
					bool			operator!=(const Matrix2) const;
					/// Add 2 matrices together & set the first matrix equal to the result
					Matrix2&		operator+=(const Matrix2&);
					/// Subtract 1 matrix from another & set the first matrix equal to the result
					Matrix2&		operator-=(const Matrix2&);
					/// Multiply 2 matrices & set the first matrix equal to the result
					Matrix2&		operator*=(const Matrix2&);
#pragma endregion
	
#pragma region Destructor

		///Destructor

									/// Default destructor
									~Matrix2() = default;
#pragma endregion

		///Variables
		float	m_matrix[2][2];

	}; // !Class Matrix

} // !Namespace LibMath

#endif // !__LIBMATH__MATRIX__MATRIX2_H__