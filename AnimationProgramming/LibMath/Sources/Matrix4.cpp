///Header
#include "Matrix/Matrix4.h"

namespace LibMath
{
#pragma region Constructor
	
	/// Constructor to create 4x4 a identity matrix 
	Matrix4::Matrix4(void)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->m_matrix[i][j] = (i == j ? 1.f : 0.f);
			}
		}
	}
	/// Constructor to create a 4x4 identity matrix multiplied by a scalar
	Matrix4::Matrix4(float _scalar)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->m_matrix[i][j] = (i == j ? _scalar : 0.0f);
			}
		}
	}
	/// Constructor to create a 4x4 matrix by setting all the values
	Matrix4::Matrix4(float _array[4][4])
	{
		for (int i = 0; i < 16; ++i)
		{
			this->m_matrix[i / 4][i % 4] = _array[i / 4][i % 4];
		}
	}

#pragma endregion

#pragma region Other function
	 
	/// Return the determinant of a 4x4 matrix
	float		Matrix4::Determinant(const Matrix4& _other) const
	{
		float determinant = 0.0f;

		for (int i = 0; i < 4; ++i)
		{
			// Create 3x3 matrix
			Matrix3 minor;

			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					minor.m_matrix[j][k] = (k < i) ? _other.m_matrix[j + 1][k] : _other.m_matrix[j + 1][k + 1];
				}
			}

			float minorDeterminant = minor.Determinant(minor);
			determinant += (i % 2 == 0) ? _other.m_matrix[0][i] * minorDeterminant : -_other.m_matrix[0][i] * minorDeterminant;
		}

		return determinant;
	}
	/// Set the identity matrix, by default set to 1
	Matrix4		Matrix4::Identity(float _scalar)
	{
		Matrix4 matrix;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				matrix.m_matrix[i][j] = (i == j ? _scalar : 0.0f);
			}
		}

		return matrix;
	}
	/// Invert matrix rows and columns
	Matrix4		Matrix4::Transpose(const Matrix4& _other)
	{
		Matrix4 matrix4 = _other;

		// Transpose matrix
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m_matrix[j][i] = matrix4.m_matrix[i][j];
			}
		}

		return *this;
	}
	/// Return the matrix of the result of every submatrix for every elements
	Matrix4		Matrix4::Minor(const Matrix4& _other)
	{
		Matrix3 matrix3;
		Matrix4 matrixCopy(_other);
		Matrix4 resultMatrix;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				matrix3.GetMatrix3(matrixCopy, i, j);
				float det = matrix3.Determinant(matrix3);
				resultMatrix.m_matrix[i][j] = det;
			}
		}

		return resultMatrix;
	}
	/// Function to find the good cofactor of the submatrix between 1 and -1
	Matrix4		Matrix4::Cofactor(const Matrix4& _other)
	{
		Matrix4 resultMatrix;
		resultMatrix = resultMatrix.Minor(_other);

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				resultMatrix.m_matrix[i][j] *= ((i + j) % 2 == 0 ? 1.0f : -1.0f);
			}
		}

		return resultMatrix;
	}
	/// Function to change the order between row and column of the matrix
	Matrix4		Matrix4::Adjugate(Matrix4& _other)
	{
		Matrix4 matrix4;

		_other = _other.Cofactor(_other);
		_other = matrix4.Transpose(_other);

		return _other;
	}
	/// Return matrix to the power of -1
	Matrix4		Matrix4::GetInverse() const
	{
		// Check if inverse exists
		Matrix4 matrixCopy = *this;
		Matrix4 resultMatrix;

		float det = resultMatrix.Determinant(matrixCopy);

		// Check determinant is not zero
		if (det == 0.0f)
			return resultMatrix;

		resultMatrix = matrixCopy.Adjugate(matrixCopy) * (1.0f / det);

		return resultMatrix;
	}

#pragma endregion

#pragma region Transformation

	/// Return a rotation matrix for the x axis
	Matrix4		Matrix4::XRotation(float _angle, bool _isRowMajor)
	{
		Matrix4 matrix4;

		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);


		matrix4.m_matrix[0][0] = 1.0f;
		matrix4.m_matrix[3][3] = 1.0f;

		if (_isRowMajor)
		{

			matrix4.m_matrix[1][1] = cosAngle;
			matrix4.m_matrix[1][2] = -sinAngle;
			matrix4.m_matrix[2][1] = sinAngle;
			matrix4.m_matrix[2][2] = cosAngle;
		}
		else
		{
			matrix4.m_matrix[1][1] = cosAngle;
			matrix4.m_matrix[1][2] = sinAngle;
			matrix4.m_matrix[2][1] = -sinAngle;
			matrix4.m_matrix[2][2] = cosAngle;
		}

		return matrix4;
	}
	/// Return a rotation matrix for the y axis
	Matrix4		Matrix4::YRotation(float _angle, bool _isRowMajor)
	{
		Matrix4 matrix4;

		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);

		matrix4.m_matrix[1][1] = 1.0f;
		matrix4.m_matrix[3][3] = 1.0f;

		if (_isRowMajor)
		{
			matrix4.m_matrix[0][0] = cosAngle;
			matrix4.m_matrix[0][2] = sinAngle;
			matrix4.m_matrix[2][0] = -sinAngle;
			matrix4.m_matrix[2][2] = cosAngle;
		}
		else
		{
			matrix4.m_matrix[0][0] = cosAngle;
			matrix4.m_matrix[0][2] = -sinAngle;
			matrix4.m_matrix[2][0] = sinAngle;
			matrix4.m_matrix[2][2] = cosAngle;
		}

		return matrix4;
	}
	/// Return a rotation matrix for the z axis
	Matrix4		Matrix4::ZRotation(float _angle, bool _isRowMajor)
	{
		Matrix4 matrix4;

		float sinAngle = sinf(_angle);
		float cosAngle = cosf(_angle);

		if (_isRowMajor)
		{
			matrix4.m_matrix[0][0] = cosAngle;
			matrix4.m_matrix[0][1] = sinAngle;
			matrix4.m_matrix[1][0] = -sinAngle;
			matrix4.m_matrix[1][1] = cosAngle;
			matrix4.m_matrix[2][2] = 1.0f;
			matrix4.m_matrix[3][3] = 1.0f;
		}
		else
		{
			matrix4.m_matrix[0][0] = cosAngle;
			matrix4.m_matrix[0][1] = -sinAngle;
			matrix4.m_matrix[1][0] = sinAngle;
			matrix4.m_matrix[1][1] = cosAngle;
			matrix4.m_matrix[2][2] = 1.0f;
			matrix4.m_matrix[3][3] = 1.0f;
		}

		return matrix4;
	}
	/// Calcul the translate matrix
	Matrix4		Matrix4::Translate(const Vector3& _vector, bool _isRowMajor)
	{
		if (_isRowMajor)
		{
			float matrix[4][4] =
			{
				{1.f, 0.f, 0.f, _vector.m_x},
				{0.f, 1.f, 0.f, _vector.m_y},
				{0.f, 0.f, 1.f, _vector.m_z},
				{0.f, 0.f, 0.f, 1.f}
			};

			return Matrix4(matrix);
		}
		else
		{
			float matrix[4][4] =
			{
				{1.f, 0.f, 0.f, 0.f},
				{0.f, 1.f, 0.f, 0.f},
				{0.f, 0.f, 1.f, 0.f},
				{_vector.m_x, _vector.m_y, _vector.m_z, 1.f}
			};

			return Matrix4(matrix);
		}
	}
	/// Calcul the scale matrix
	Matrix4		Matrix4::Scale(const Vector3& _vector)
	{
		float matrix[4][4] =
		{
			{_vector.m_x, 0.f, 0.f, 0.f},
			{0.f, _vector.m_y, 0.f, 0.f},
			{0.f, 0.f,_vector.m_z, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};

		return Matrix4(matrix);
	}
	/// Function to do the perspective projection matrix
	Matrix4		Matrix4::PerspectiveProjection(float _fovy, float _aspect, float _near, float _far)
	{
		LibMath::Matrix4 projectionMatrix;
		const float pi = 3.14f;
		_fovy = _fovy * (pi / 180.0f);

		float tanAngle = tanf(_fovy / 2.0f);

		projectionMatrix.m_matrix[0][0] = 1.0f / (_aspect * tanAngle);
		projectionMatrix.m_matrix[1][1] = 1.0f / tanAngle;
		projectionMatrix.m_matrix[2][2] = -(_far + _near) / (_far - _near);
		projectionMatrix.m_matrix[2][3] = -(2.0f * _far * _near) / (_far - _near);
		projectionMatrix.m_matrix[3][2] = -1.0f;
		projectionMatrix.m_matrix[3][3] = 0.0f;

		return projectionMatrix.Transpose(projectionMatrix);
	}
	/// Function to do the orthographic matrix
	Matrix4		Matrix4::Orthographique(Vector3 _vector1, Vector3 _vector2)
	{
		Matrix4 ortho;

		ortho.m_matrix[0][0] = 2 / (_vector2.m_x - _vector1.m_x);
		ortho.m_matrix[3][0] = -(_vector2.m_x + _vector1.m_x) / (_vector2.m_x - _vector1.m_x);
		ortho.m_matrix[1][1] = 2 / (_vector2.m_y - _vector1.m_y);
		ortho.m_matrix[3][1] = -(_vector2.m_y + _vector1.m_y) / (_vector2.m_y - _vector1.m_y);
		ortho.m_matrix[2][2] = -2 / (_vector2.m_z - _vector1.m_z);
		ortho.m_matrix[3][2] = -(_vector2.m_z + _vector1.m_z) / (_vector2.m_z - _vector1.m_z);
		ortho.m_matrix[3][3] = 1;

		return ortho;
	}

#pragma endregion

#pragma region In class operator
	 
	/// Operator to return the value attach to the index
	float* Matrix4::operator[](int _index)
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (_index < 0 || _index > 4)
			throw std::logic_error("Index must be in range [0, 4[");

		return this->m_matrix[_index];
	}
	/// Operator to return the value attach to the index
	const float* Matrix4::operator[](int _index) const
	{
		/********************\
		* Operator to return *
		* the value assigned *
		*	to this index    *
		\********************/
		if (_index < 0 || _index > 4)
			throw std::logic_error("Index must be in range [0, 4[");

		return this->m_matrix[_index];
	}

	/// Set a matrix equal to another
	Matrix4&	Matrix4::operator=(const Matrix4& _other)
	{
		for (int i = 0; i < 16; ++i)
		{
			this->m_matrix[i / 4][i % 4] = _other.m_matrix[i / 4][i % 4];
		}

		return *this;
	}
	/// Add 2 matrices together & return the result
	Matrix4		Matrix4::operator+(const Matrix4& _other) const
	{
		Matrix4 result = Matrix4();

		for (int i = 0; i < 16; ++i)
		{
			result.m_matrix[i / 4][i % 4] = this->m_matrix[i / 4][i % 4] + _other.m_matrix[i / 4][i % 4];
		}

		return result;
	}
	/// Subtract one matrix from another & return the result
	Matrix4		Matrix4::operator-(const Matrix4& _other) const
	{
		Matrix4 result = Matrix4();

		for (int i = 0; i < 16; ++i)
		{
			result.m_matrix[i / 4][i % 4] = this->m_matrix[i / 4][i % 4] - _other.m_matrix[i / 4][i % 4];
		}

		return result;
	}
	/// Multiply two matrices together & return the result
	Matrix4		Matrix4::operator*(const Matrix4& _other) const
	{
		// Create a null 4x4 matrix
		float initValues[4][4] =
		{
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		};

		LibMath::Matrix4 result = LibMath::Matrix4(initValues);

		// Iterate through matrix to set the result matrix equal to the result of the 2 matrices multiplied
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; ++k)
				{
					// Add the value obtained from multiplying the 2 matrices row * column
					result.m_matrix[i][j] += this->m_matrix[i][k] * _other.m_matrix[k][j];
				}
			}
		}

		return result;
	}
	/// Multiply a matrix with a scalar & return the result
	Matrix4		Matrix4::operator*(const float& _scalar) const
	{
		Matrix4 tmp = Matrix4();

		for (int i = 0; i < 16; ++i)
		{
			tmp.m_matrix[i / 4][i % 4] = m_matrix[i / 4][i % 4] * _scalar;
		}

		return tmp;
	}
	/// Add 2 matrices together & set the first matrix equal to the result
	Matrix4&	Matrix4::operator+=(const Matrix4 _other)
	{
		return *this = *this + _other;
	}
	/// Subtract 1 matrix from another & set the first matrix equal to the result
	Matrix4&	Matrix4::operator-=(const Matrix4 _other)
	{
		return *this = *this - _other;
	}
	/// Multiply 2 matrices & set the first matrix equal to the result
	Matrix4&	Matrix4::operator*=(const Matrix4 _other)
	{
		return *this = *this * _other;
	}
	/// Multiply a matrix by a scalar & modify the matrix values with the result
	Matrix4&	Matrix4::operator*=(const float& _scalar)
	{
		return *this = *this * _scalar;
	}
	/// Compare 2 matrices return true if they are equal to one another
	bool		Matrix4::operator==(const Matrix4 _other) const
	{
		// Check equality via epsilon test
		float difference = 0.0f;

		for (int i = 0; i < 16; ++i)
		{
			float num1 = absolute(m_matrix[i / 4][i % 4]);
			float num2 = absolute(_other.m_matrix[i / 4][i % 4]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference > scaledEpsilon)
				return false;
		}

		return true;
	}
	/// Compare 2 matrices return true if they are not equal to one another
	bool		Matrix4::operator!=(const Matrix4 _other) const
	{
		// Check equality via epsilon test
		float difference = 0.0f;

		for (int i = 0; i < 16; ++i)
		{
			float num1 = absolute(m_matrix[i / 4][i % 4]);
			float num2 = absolute(_other.m_matrix[i / 4][i % 4]);

			float scaledEpsilon = FLT_EPSILON * max(num1, num2);

			if (difference <= scaledEpsilon)
				return false;
		}

		return true;
	}

#pragma endregion

#pragma region Out class operator

	/// Operator to multiply a Vector4 and a matrix 4
	Vector4 operator*(const Vector4& _vector, const Matrix4& _matrix)
	{
		Vector4 result = Vector4::zero();

		for (int i = 0; i < 4; ++i)
		{
			result[i] = 0;
			
			for (int j = 0; j < 4; ++j)
			{
				result[i] += _matrix.m_matrix[j][i] * _vector[j];
			}
		}
		return result;
	}

#pragma endregion


} // !Namespace LibMath