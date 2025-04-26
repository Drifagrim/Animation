///Header
#include "Matrix/Matrix3.h"

namespace LibMath
{
#pragma region Constructor

	/// Constructor to create a 3x3 identity matrix
	Matrix3::Matrix3(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->m_matrix[i][j] = (i == j ? 1.f : 0.f);
			}
		}
	}
	/// Constructor to create a 3x3 identity matrix multiplied by a scalar
	Matrix3::Matrix3(float _scalar)
	{
		// Initialize as identity matrix multiplied by a scalar
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->m_matrix[i][j] = (i == j ? _scalar : 0.0f);
			}
		}
	}
	/// Constructor with array of float to set the different value of a matrix
	Matrix3::Matrix3(float _array[3][3])
	{
		for (int i = 0; i < 9; ++i)
		{
			this->m_matrix[i / 3][i % 3] = _array[i / 3][i % 3];
		}
	}

#pragma endregion

#pragma region Other function

	/// Change the i and j value in regard to the diagonal
	Matrix3		Matrix3::Transpose(const Matrix3& _other)
	{
		Matrix3 matrix3 = _other;

		// Transpose matrix
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->m_matrix[j][i] = matrix3.m_matrix[i][j];
			}
		}

		return *this;
	}
	/// Set the matrix to the identity by setting the scalar at value of the diagonal
	Matrix3		Matrix3::Identity(float _scalar)
	{
		// Create an identity matrix and multiply by scalar
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->m_matrix[i][j] = (i == j ? _scalar : 0.0f);
			}
		}

		return *this;
	}
	/// Create a submatrix since the matrix and return the result
	Matrix3		Matrix3::Minor(const Matrix3& _other)
	{
		Matrix2 matrix2;
		Matrix3 matrixCopy(_other);
		Matrix3 resultMatrix;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix2.GetMatrix2(matrixCopy, i, j);
				float det = matrix2.Determinant(matrix2);
				resultMatrix.m_matrix[i][j] = det;
			}
		}

		return resultMatrix;
	}
	/// Function to find the good cofactor of the submatrix between 1 and -1
	Matrix3		Matrix3::Cofactor(const Matrix3& _other)
	{
		Matrix3 resultMatrix;
		resultMatrix = resultMatrix.Minor(_other);

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				resultMatrix.m_matrix[i][j] *= ((i + j) % 2 == 0 ? 1.0f : -1.0f);
			}
		}

		return resultMatrix;
	}
	/// Function to change the order between row and column of the matrix
	Matrix3&	Matrix3::Adjugate(const Matrix3 _other)
	{
		Matrix2 matrix2;

		// Row 1
		this->m_matrix[0][0] = +matrix2.Determinant({ _other.m_matrix[1][1], _other.m_matrix[1][2], _other.m_matrix[2][1], _other.m_matrix[2][2] });
		this->m_matrix[0][1] = -matrix2.Determinant({ _other.m_matrix[0][1], _other.m_matrix[0][2], _other.m_matrix[2][1], _other.m_matrix[2][2] });
		this->m_matrix[0][2] = +matrix2.Determinant({ _other.m_matrix[0][1], _other.m_matrix[0][2], _other.m_matrix[1][1], _other.m_matrix[1][2] });

		// Row 2
		this->m_matrix[1][0] = -matrix2.Determinant({ _other.m_matrix[1][0], _other.m_matrix[1][2], _other.m_matrix[2][0], _other.m_matrix[2][2] });
		this->m_matrix[1][1] = +matrix2.Determinant({ _other.m_matrix[0][0], _other.m_matrix[0][2], _other.m_matrix[2][0], _other.m_matrix[2][2] });
		this->m_matrix[1][2] = -matrix2.Determinant({ _other.m_matrix[0][0], _other.m_matrix[0][2], _other.m_matrix[1][0], _other.m_matrix[1][2] });

		// Row 3
		this->m_matrix[2][0] = +matrix2.Determinant({ _other.m_matrix[1][0], _other.m_matrix[1][1], _other.m_matrix[2][0], _other.m_matrix[2][1] });
		this->m_matrix[2][1] = -matrix2.Determinant({ _other.m_matrix[0][0], _other.m_matrix[0][1], _other.m_matrix[2][0], _other.m_matrix[2][1] });
		this->m_matrix[2][2] = +matrix2.Determinant({ _other.m_matrix[0][0], _other.m_matrix[0][1], _other.m_matrix[1][0], _other.m_matrix[1][1] });

		return *this;
	}
	/// Reverse the matrix between row major to column major or column major to row major
	Matrix3		Matrix3::Inverse(const Matrix3& _other) const
	{
		// Check if inverse exists
		Matrix3 matrixCopy = _other;
		Matrix3 resultMatrix;

		float det = resultMatrix.Determinant(matrixCopy);

		// Check determinant is not zero
		if (det == 0.0f)
			return resultMatrix;

		resultMatrix = matrixCopy.Adjugate(matrixCopy) * (1.0f / det);

		return resultMatrix;
	}
	/// The determinant of a matrix is a summary value and is calculated using the cofactors 
	/// of elements of the matrix
	float		Matrix3::Determinant(const Matrix3& _other) const
	{
		/*
			Split 3x3 matrix into 3 2x2 matrix and multiply by the coefficient

			Equation:
			|a b c|
			|d e f|
			|g h i|

			Determinant = a(ei - fh) - b(di - gf) + c(dh - eg)
		*/
		float a = _other.m_matrix[0][0] * ((_other.m_matrix[1][1] * _other.m_matrix[2][2]) - (_other.m_matrix[1][2] * _other.m_matrix[2][1]));
		float b = _other.m_matrix[0][1] * ((_other.m_matrix[1][0] * _other.m_matrix[2][2]) - (_other.m_matrix[1][2] * _other.m_matrix[2][0]));
		float c = _other.m_matrix[0][2] * ((_other.m_matrix[1][0] * _other.m_matrix[2][1]) - (_other.m_matrix[1][1] * _other.m_matrix[2][0]));

		return a - b + c;
	}
	/// Get the minor of the matrix 4
	Matrix3& Matrix3::GetMatrix3(const Matrix4& _other, int _row, int _col)
	{
		int iOffset = 0;
		int jOffset = 0;

		for (int i = 0; i < 4; ++i)
		{
			if (i == _row)
			{
				jOffset = -1;
				continue;
			}

			iOffset = 0;
			for (int j = 0; j < 4; ++j)
			{
				if (j == _col)
				{
					iOffset = -1;
					continue;
				}

				m_matrix[i + jOffset][j + iOffset] = _other.m_matrix[i][j];
			}
		}

		return *this;
	}

#pragma endregion

#pragma region Transformation

	/// Calcul the rotation around x axis
	Matrix3		Matrix3::XRotation(float _angle, bool _isRowMajor)
	{
		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);

		if (_isRowMajor)
		{
			float matrix[3][3] =
			{
				1.0f, 0.0f, 0.0f,
				0.0f, cosAngle, -sinAngle,
				0.0f, sinAngle, cosAngle
			};

			return Matrix3(matrix);
		}
		else
		{
			float matrix[3][3] =
			{
				1.0f, 0.0f, 0.0f,
				0.0f, cosAngle, sinAngle,
				0.0f, -sinAngle, cosAngle
			};

			return Matrix3(matrix);

		}

	}
	/// Calcul the rotation around y axis
	Matrix3		Matrix3::YRotation(float _angle, bool isRowMajor)
	{
		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);

		if (isRowMajor)
		{
			float matrix[3][3] =
			{
				cosAngle, 0.0f, sinAngle,
				0.0f, 1.0f, 0.0f,
				-sinAngle, 0.0f, cosAngle
			};

			return Matrix3(matrix);
		}
		else
		{
			float matrix[3][3] =
			{
				cosAngle, 0.0f, -sinAngle,
				0.0f, 1.0f, 0.0f,
				sinAngle, 0.0f, cosAngle
			};

			return Matrix3(matrix);
		}
	}
	/// Calcul the rotation around z axis
	Matrix3		Matrix3::ZRotation(float _angle, bool _isRowMajor)
	{
		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);

		if (_isRowMajor)
		{
			float matrix[3][3] =
			{
				cosAngle, -sinAngle, 0.0f,
				sinAngle, cosAngle, 0.0f,
				0.0f, 0.0f, 1.0f
			};

			return Matrix3(matrix);
		}
		else
		{
			float matrix[3][3] =
			{
				cosAngle, sinAngle, 0.0f,
				-sinAngle, cosAngle, 0.0f,
				0.0f, 0.0f, 1.0f
			};

			return Matrix3(matrix);
		}
	}
	/// Calcul the translation in regard to the vector 2
	Matrix3		Matrix3::Translate(const Vector2& _vector, bool _isRowMajor)
	{
		if (_isRowMajor)
		{
			float matrix[3][3] =
			{
				1.f, 0.f, _vector.m_x,
				0.f, 1.f, _vector.m_y,
				0.f, 0.f, 1.f

			};

			return Matrix3(matrix);
		}
		else
		{
			float matrix[3][3] =
			{
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				_vector.m_x, _vector.m_y, 1.f

			};

			return Matrix3(matrix);
		}
	}
	/// Calcul the scale in regard to the vector 2
	Matrix3		Matrix3::Scale(const Vector2& _vector)
	{
		float matrix[3][3] =
		{
			_vector.m_x, 0.f, 0.f,
			0.f, _vector.m_y, 0.f,
			0.f, 0.f, 1.f
		};

		return Matrix3(matrix);
	}

#pragma endregion

#pragma region In class operator

	float* Matrix3::operator[](int _index)
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (_index < 0 || _index > 3)
			throw std::logic_error("Index must be in range [0, 3[");

		return this->m_matrix[_index];
	}

	const float* Matrix3::operator[](int _index) const
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (_index < 0 || _index > 3)
			throw std::logic_error("Index must be in range [0, 3[");

		return this->m_matrix[_index];
	}

	/// Set the value of the matrix in regard to the other matrix
	Matrix3&	Matrix3::operator=(const Matrix3& _other)
	{
		// Copy all matrix values
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				this->m_matrix[i][j] = _other.m_matrix[i][j];
			}
		}

		return *this;
	}
	/// Addition between two matrix
	Matrix3		Matrix3::operator+(const Matrix3 _other) const
	{
		Matrix3 tmp;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp.m_matrix[i][j] = this->m_matrix[i][j] + _other.m_matrix[i][j];
			}
		}

		return tmp;
	}
	/// Substract to matrix
	Matrix3		Matrix3::operator-(const Matrix3 _other) const
	{
		Matrix3 tmp = Matrix3();

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				tmp.m_matrix[i][j] = this->m_matrix[i][j] - _other.m_matrix[i][j];
			}
		}

		return tmp;
	}
	/// Multiplicaiton between two matrix
	Matrix3		Matrix3::operator*(const Matrix3 _other) const
	{

		// Create empty 3x3 matrix
		float initValues[3][3] = {
			0.f, 0.f, 0.f, 
			0.f, 0.f, 0.f, 
			0.f, 0.f, 0.f };
		Matrix3 result(initValues);

		// Iterate through matrix to set the result matrix equal to the result of the 2 matrices multiplied
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					// Add the value obtained from multiplying the 2 matrices row * column
					result.m_matrix[i][j] += this->m_matrix[i][k] * _other.m_matrix[k][j];
				}
			}
		}

		return result;
	}
	/// Multiplicaiton between this matrix and a scalar
	Matrix3		Matrix3::operator*(const float _scalar) const
	{
		Matrix3 tmp;

		for (int i = 0; i < 9; ++i)
		{
			tmp.m_matrix[i / 3][i % 3] = m_matrix[i / 3][i % 3] * _scalar;
		}

		return tmp;
	}
	/// Addition of two matrix
	Matrix3&	Matrix3::operator+=(const Matrix3 _other)
	{
		return *this = *this + _other;
	}
	/// Substraction of two matrix
	Matrix3&	Matrix3::operator-=(const Matrix3 _other)
	{
		return *this = *this - _other;
	}
	/// Multiplication between two matrix
	Matrix3&	Matrix3::operator*=(const Matrix3 _other)
	{
		return *this = *this * _other;
	}
	/// Multiplication between this matrix and a scalar
	Matrix3&	Matrix3::operator*=(const float& _scalar)
	{
		return *this = *this * _scalar;
	}
	/// Check the equality between two matrix
	bool		Matrix3::operator==(const Matrix3 _other) const
	{
		// Check equality via epsilon test
		float difference = 0.0f;

		for (int i = 0; i < 9; ++i)
		{
			float num1 = absolute(m_matrix[i / 3][i % 3]);
			float num2 = absolute(_other.m_matrix[i / 3][i % 3]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference > scaledEpsilon)
				return false;
		}

		return true;
	}
	/// Check the inequality between two matrix
	bool		Matrix3::operator!=(const Matrix3 _other) const
	{
		// Check equality via epsilon test
		float difference = 0.0f;

		for (int i = 0; i < 9; ++i)
		{
			float num1 = absolute(m_matrix[i / 3][i % 3]);
			float num2 = absolute(_other.m_matrix[i / 3][i % 3]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference <= scaledEpsilon)
				return false;
		}

		return true;
	}

#pragma endregion

} // !Namespace LibMath