#ifndef __LIBMATH__MATRIX__MATRIX3_H__
#define __LIBMATH__MATRIX__MATRIX3_H__

#pragma region Header

/// Matrix librairies
#include "Matrix/Matrix.h"

/// Vector librairies
#include "Vector/Vector.h"

/// Ariithmetic librairies
#include "Arithmetic.h"

#pragma endregion

namespace LibMath
{
	class Matrix4;

	class Matrix3
	{
	public:

#pragma region Constructor

		/// Constructor

								/// Default constructor initializes as identity matrix
								Matrix3(void);
								/// Constructor which multiplies an identity matrix by the given scalar
		explicit				Matrix3(float);
								/// Constructor which takes a list of values
								Matrix3(float _array[3][3]);
#pragma endregion

#pragma region Other functions

		/// Other functions

					/// Change row col with col row (in regard to the diagonal
					Matrix3		Transpose(const Matrix3&);
					/// Return an identity matrix multiplied by a scalar (scalar set to 1 if left empty)
					Matrix3		Identity(float _scalar = 1.0f);
					/// Return the matrix of the result of every submatrix for every elements
					Matrix3		Minor(const Matrix3&);
					/// Function to find the good cofactor of the submatrix between 1 and -1
					Matrix3		Cofactor(const Matrix3&);
					/// Function to change the order between row and column of the matrix
					Matrix3&	Adjugate(const Matrix3);
					/// Reverse the matrix between row major to column major or column major to row major
					Matrix3		Inverse(const Matrix3&) const;
					/// Return the determinant of a 3x3 matrix
					float		Determinant(const Matrix3&) const;
					/// Get a matrix 3 since a matrix 4
					Matrix3&	GetMatrix3(const Matrix4&, int, int);

#pragma endregion

#pragma region Transformation

		/// Transormation

					/// Get X rotation matrix
		static		Matrix3		XRotation(float, bool _isRowMajor = false);
					/// Get Y rotation matrix
		static		Matrix3		YRotation(float, bool _isRowMajor = false);
					/// Get Z rotation matrix
		static		Matrix3		ZRotation(float, bool _isRowMajor = false);
					/// Calcul the translate matrix
		static		Matrix3		Translate(const Vector2&, bool _isRowMajor = false);
					/// Calcul the scale matrix
		static		Matrix3		Scale(const Vector2&);
					
#pragma endregion

#pragma region In class operator

		/// In class operator

					/// To access to a value by the index associate into the matrix
					float* operator[](int);
					/// To access to a value by the index associate into the matrix
					const float* operator[](int) const;
					/// Set a matrix equal to another
					Matrix3&	operator=(const Matrix3&);
					/// Add 2 matrices together & return the result
					Matrix3		operator+(const Matrix3) const;
					/// Subtract one matrix from another & return the result
					Matrix3		operator-(const Matrix3) const;
					/// Multiply two matrices together & return the result
					Matrix3		operator*(const Matrix3) const;
					/// Multiply a matrix with a scalar & return the result
					Matrix3		operator*(const float) const;
					/// Add 2 matrices together & set the first matrix equal to the result
					Matrix3&	operator+=(const Matrix3);
					/// Subtract 1 matrix from another & set the first matrix equal to the result
					Matrix3&	operator-=(const Matrix3);
					/// Multiply 2 matrices & set the first matrix equal to the result
					Matrix3&	operator*=(const Matrix3);
					/// Multiply a matrix by a scalar & modify the matrix values with the result
					Matrix3&	operator*=(const float&);
					/// Compare 2 matrices return true if they are equal to one another
					bool		operator==(const Matrix3) const;
					/// Compare 2 matrices return true if they are not equal to one another
					bool		operator!=(const Matrix3) const;
#pragma endregion

#pragma region Destructor

		/// Destructor

								/// Default destructor
								~Matrix3() = default;
#pragma endregion

		/// Variables
		float m_matrix[3][3];

	}; // !Class Matrix3

} // !Namespace LibMath

#endif // !__LIBMATH__MATRIX__MATRIX3_H__
