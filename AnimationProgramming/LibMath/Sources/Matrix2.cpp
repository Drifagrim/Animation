///Header
#include "Matrix/Matrix2.h"

namespace LibMath
{
#pragma region Constructor
	
	/// Initialize with 2x2 identity matrix
	Matrix2::Matrix2()
	{
		
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				i == j ? this->m_matrix[i][j] = 1.0f : this->m_matrix[i][j] = 0.0f;
			}
		}
	}
	/// Construct the matrix 2x2 by setting the identity to the scalar
	Matrix2::Matrix2(float _scalar)
	{
		
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				i == j ? this->m_matrix[i][j] = _scalar : this->m_matrix[i][j] = 0.0f;		// Initialize with 2x2 identity matrix
			}
		}
	}
	/// Construct the matrix 2x2 by setting all values
	Matrix2::Matrix2(float _x, float _y, float _z, float _w)
	{
		this->m_matrix[0][0] = _x;
		this->m_matrix[0][1] = _y;
		this->m_matrix[1][0] = _z;
		this->m_matrix[1][1] = _w;
	}

#pragma endregion

#pragma region Other functions

	/// Calcul the determinant of a matrix 2x2
	float			Matrix2::Determinant(const Matrix2& _other) const
	{
		float a = _other.m_matrix[0][0] * _other.m_matrix[1][1];
		float b = _other.m_matrix[0][1] * _other.m_matrix[1][0];

		return a - b;
	}
	/// Set the matrix identity to the value of the scalar
	Matrix2			Matrix2::Identity(float _scalar)
	{
		this->m_matrix[0][0] = 1.0f;
		this->m_matrix[0][1] = 0.0f;
		this->m_matrix[1][0] = 0.0f;
		this->m_matrix[1][1] = 1.0f;

		return *this * _scalar;
	}
	/// Change the colum and the row in regard to the diagonal
	Matrix2			Matrix2::Transpose(const Matrix2& _other)
	{
		/**********************************************************\
		*														   *
		* matrix {							transpose = {		   *
		*			1, 3, 5,								1, 2,  *
		*			2, 4, 6 }		=>						3, 4,  *
		*													5, 6 } *
		*														   *
		\**********************************************************/
		Matrix2 tmpMatrix = Matrix2(
			_other.m_matrix[0][0],
			_other.m_matrix[0][1],
			_other.m_matrix[1][0],
			_other.m_matrix[1][1]
		);

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				this->m_matrix[j][i] = tmpMatrix.m_matrix[i][j];							// Transpose matrix
			}
		}

		return *this;
	}
	/// Calcul the determinant of the submatrix
	Matrix2			Matrix2::Minor(const Matrix2& _other)
	{
		*this = _other;

		this->m_matrix[0][0] = std::powf(-1.0f, 2) * this->m_matrix[0][0];
		this->m_matrix[0][1] = std::powf(-1.0f, 3) * this->m_matrix[0][1];
		this->m_matrix[1][0] = std::powf(-1.0f, 3) * this->m_matrix[1][0];
		this->m_matrix[1][1] = std::powf(-1.0f, 4) * this->m_matrix[1][1];

		return *this;
	}
	/// Set the matrix adjugate
	Matrix2&		Matrix2::Adjugate(const Matrix2& _other)
	{
		this->m_matrix[0][0] = _other.m_matrix[1][1];
		this->m_matrix[1][0] = -_other.m_matrix[1][0];
		this->m_matrix[0][1] = -_other.m_matrix[0][1];
		this->m_matrix[1][1] = _other.m_matrix[1][1];

		return *this;
	}
	/// Calcul the inverse of the matrix
	Matrix2			Matrix2::Inverse(const Matrix2& _other) const
	{
		Matrix2 matrixCopy = _other;
		Matrix2 resultMatrix;

		float determinant = Determinant(_other);													// Get determinant of matrix

		if (determinant == 0.0f)																	// Check determinanterminant is not zero or return an identity matrix
			return Matrix2();																		// TODO: check might cause potential issues

		resultMatrix = matrixCopy.Adjugate(_other) * (1 / determinant);

		return resultMatrix;
	}
	/// Get the minor of the matrix 3
	Matrix2& Matrix2::GetMatrix2(const Matrix3& _matrix3, int _row, int _column)
	{
		int iOffset = 0;
		int jOffset = 0;

		for (int i = 0; i < 3; ++i)
		{
			if (i == _row)
			{
				jOffset = -1;
				continue;
			}

			iOffset = 0;
			for (int j = 0; j < 3; ++j)
			{
				if (j == _column)
				{
					iOffset = -1;
					continue;
				}

				m_matrix[i + jOffset][j + iOffset] = _matrix3.m_matrix[i][j];
			}
		}

		return *this;
	}

#pragma endregion

#pragma region In class operator
	
	/// To access to a value by the index associate into the matrix
	float*			Matrix2::operator[](int index)
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (index < 0 || index > 2)
			throw std::logic_error("Index must be in range [0, 2[");

		return this->m_matrix[index];
	}
	/// To access to a value by the index associate into the matrix
	const float*	Matrix2::operator[](int index) const
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (index < 0 || index > 2)
			throw std::logic_error("Index must be in range [0, 2[");

		return this->m_matrix[index];
	}
	/// Set the value of 1 matrix equal to another
	Matrix2			Matrix2::operator=(const Matrix2& _other)
	{
		this->m_matrix[0][0] = _other.m_matrix[0][0];
		this->m_matrix[0][1] = _other.m_matrix[0][1];
		this->m_matrix[1][0] = _other.m_matrix[1][0];
		this->m_matrix[1][1] = _other.m_matrix[1][1];

		return *this;
	}
	/// Add to matrices together
	Matrix2			Matrix2::operator+(const Matrix2& _other) const
	{
		Matrix2 tmp = Matrix2();

		tmp.m_matrix[0][0] = this->m_matrix[0][0] + _other.m_matrix[0][0];
		tmp.m_matrix[0][1] = this->m_matrix[0][1] + _other.m_matrix[0][1];
		tmp.m_matrix[1][0] = this->m_matrix[1][0] + _other.m_matrix[1][0];
		tmp.m_matrix[1][1] = this->m_matrix[1][1] + _other.m_matrix[1][1];

		return tmp;
	}
	/// Subtract to matrices
	Matrix2			Matrix2::operator-(const Matrix2& _other) const
	{
		Matrix2 tmp = Matrix2();

		tmp.m_matrix[0][0] = this->m_matrix[0][0] - _other.m_matrix[0][0];
		tmp.m_matrix[0][1] = this->m_matrix[0][1] - _other.m_matrix[0][1];
		tmp.m_matrix[1][0] = this->m_matrix[1][0] - _other.m_matrix[1][0];
		tmp.m_matrix[1][1] = this->m_matrix[1][1] - _other.m_matrix[1][1];

		return tmp;
	}
	/// Multiply 2 matrices together
	Matrix2			Matrix2::operator*(const Matrix2& _other) const
	{
		Matrix2 tmp = Matrix2
		(
			(this->m_matrix[0][0] * _other.m_matrix[0][0]) + (this->m_matrix[0][1] * _other.m_matrix[1][0]),
			(this->m_matrix[0][0] * _other.m_matrix[0][1]) + (this->m_matrix[0][1] * _other.m_matrix[1][1]),
			(this->m_matrix[1][0] * _other.m_matrix[0][0]) + (this->m_matrix[1][1] * _other.m_matrix[1][0]),
			(this->m_matrix[1][0] * _other.m_matrix[0][1]) + (this->m_matrix[1][1] * _other.m_matrix[1][1])
		);

		return tmp;
	}
	/// Multiply the matrix by a float
	Matrix2			Matrix2::operator*(float scalar)
	{
		/************************\
		* Operator * to multiply *
		*  a matrix to a scalar  *
		* and return the matrix  *
		*		  result		 *
		\************************/
		Matrix2 matrix = { 0.0f, 0.0f, 
						   0.0f, 0.0f };

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				matrix[i][j] = this->m_matrix[i][j] * scalar;
			}
		}

		return Matrix2(matrix);
	}
	/// Check the equality between two matrix
	bool			Matrix2::operator==(const Matrix2 _other) const
	{
		/************************\
		* Check if the matrix is *
		*	 equal to another	 * 
		*		  matrix		 *
		\************************/
		float difference = 0.0f;

		for (int i = 0; i < 4; ++i)
		{
			float num1 = absolute(m_matrix[i / 2][i % 2]);
			float num2 = absolute(_other.m_matrix[i / 2][i % 2]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference > scaledEpsilon)
				return false;
		}

		return true;
	}
	/// Check the inequality between two matrix
	bool			Matrix2::operator!=(const Matrix2 _other) const
	{
		/************************\
		* Check if the matrix is *
		*	inequal to another	 *
		*		  matrix		 *
		\************************/
		float difference = 0.0f;

		for (int i = 0; i < 4; ++i)
		{
			float num1 = absolute(m_matrix[i / 2][i % 2]);
			float num2 = absolute(_other.m_matrix[i / 2][i % 2]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference <= scaledEpsilon)
				return false;
		}

		return true;
	}
	/// Add 2 matrices together & set the first matrix equal to the result
	Matrix2&		Matrix2::operator+=(const Matrix2& _other)
	{
		*this = *this + _other;

		return *this;
	}
	/// Subtract 1 matrix from another & set the first matrix equal to the result
	Matrix2&		Matrix2::operator-=(const Matrix2& _other)
	{
		*this = *this - _other;

		return *this;
	}
	/// Multiply 2 matrices & set the first matrix equal to the result
	Matrix2&		Matrix2::operator*=(const Matrix2& _other)
	{
		*this = *this * _other;

		return *this;
	}

#pragma endregion

} // !Namespace LibMath