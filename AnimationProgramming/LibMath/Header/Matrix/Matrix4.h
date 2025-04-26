#ifndef __LIBMATH__MATRIX__MATRIX4_H__
#define __LIBMATH__MATRIX__MATRIX4_H__

#pragma region Header

#include "Matrix/Matrix3.h"

/// Vector librairies
#include "Vector/Vector.h"

#pragma endregion

namespace LibMath
{
	class Vector4;

	class Matrix4
	{
	public:

#pragma region Constructor

		/// Constructor

								/// Initialize 4x4 identity matrix with diagonal of 1
								Matrix4(void);
								/// Initialize 4x4 identity matrix multiplied by a scalar
		explicit				Matrix4(float);
								/// Constructor which takes a list of values
								Matrix4(float _array[4][4]);
#pragma endregion

#pragma region Other functions

		/// Other functions

					/// Return the determinant of a 4x4 matrix
					float		Determinant(const Matrix4&) const;
					/// Return an identity matrix multiplied by a scalar (1 if left empty)
		static		Matrix4		Identity(float _scalar = 1.0f);
					/// Invert matrix rows and columns
					Matrix4		Transpose(const Matrix4&);
					/// Return the matrix of the result of every submatrix for every elements
					Matrix4		Minor(const Matrix4&);
					/// Function to find the good cofactor of the submatrix between 1 and -1
					Matrix4		Cofactor(const Matrix4&);
					/// Function to change the order between row and column of the matrix
					Matrix4		Adjugate(Matrix4&);
					/// Return matrix to the power of -1
					Matrix4		GetInverse() const;
#pragma endregion

#pragma region Transformation

		/// Transformation

					/// Return a rotation matrix for the x axis
		static		Matrix4     XRotation(float, bool _isRowMajor = false);
					/// Return a rotation matrix for the y axis
		static		Matrix4     YRotation(float, bool _isRowMajor = false);
					/// Return a rotation matrix for the z axis
		static		Matrix4     ZRotation(float, bool _isRowMajor = false);
					/// Calcul the translate matrix
		static		Matrix4		Translate(const Vector3&, bool _isRowMajor = false);
					/// Calcul the scale matrix
		static		Matrix4		Scale(const Vector3&);
					/// Function to do the perspective projection matrix
		static		Matrix4		PerspectiveProjection(float, float, float, float);
					/// Function to do the orthographic matrix
		static		Matrix4		Orthographique(Vector3, Vector3);
#pragma endregion

#pragma region In class operator

		/// In class operator

					/// To access to a value by the index associate into the matrix
					float*		operator[](int);
					/// To access to a value by the index associate into the matrix
					const float* operator[](int) const;
					/// Set a matrix equal to another
					Matrix4&	operator=(const Matrix4&);
					/// Add 2 matrices together & return the result
					Matrix4		operator+(const Matrix4&) const;
					/// Subtract one matrix from another & return the result
					Matrix4		operator-(const Matrix4&) const;
					/// Multiply two matrices together & return the result
					Matrix4		operator*(const Matrix4&) const;
					/// Multiply a matrix with a scalar & return the result
					Matrix4		operator*(const float&) const;
					/// Add 2 matrices together & set the first matrix equal to the result
					Matrix4&	operator+=(const Matrix4);
					/// Subtract 1 matrix from another & set the first matrix equal to the result
					Matrix4&	operator-=(const Matrix4);
					/// Multiply 2 matrices & set the first matrix equal to the result
					Matrix4&	operator*=(const Matrix4);
					/// Multiply a matrix by a scalar & modify the matrix values with the result
					Matrix4&	operator*=(const float&);
					/// Compare 2 matrices return true if they are equal to one another
					bool		operator==(const Matrix4) const;
					/// Compare 2 matrices return true if they are not equal to one another
					bool		operator!=(const Matrix4) const;
#pragma endregion

#pragma region Destructor

		/// Destructor

								/// Default destructor
								~Matrix4() = default;
#pragma endregion

		/// Variables
		float m_matrix[4][4];

	}; // !Class Matrix4

#pragma region Out class operator

	/// Operator to multiply a vector 4 and a matrix 4
	Vector4 operator*(const Vector4&, const Matrix4&);

#pragma endregion

} // !Namespace LibMath

#endif // __LIBMATH__MATRIX_H__