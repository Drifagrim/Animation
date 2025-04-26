#pragma region LibMath

#include "Quaternion.h"
#include "Trigonometry.h"

#pragma endregion

#pragma region Standard

#include <cmath>

#pragma endregion

namespace LibMath
{
	Quaternion operator-(Quaternion const& _other)
	{
		return Quaternion(_other.m_a, -_other.m_b, -_other.m_c, -_other.m_d);
	}
	Quaternion operator+(Quaternion _lhs, Quaternion const& _rhs)
	{
		_lhs.m_a = _lhs.m_a + _rhs.m_a;
		_lhs.m_b = _lhs.m_b + _rhs.m_b;
		_lhs.m_c = _lhs.m_c + _rhs.m_c;
		_lhs.m_d = _lhs.m_d + _rhs.m_d;

		return Quaternion(_lhs);
	}

	Quaternion operator*(Quaternion const& _lhs, Quaternion const& _rhs)
	{
		return Quaternion(
			_lhs.m_a * _rhs.m_a - _lhs.m_b * _rhs.m_b - _lhs.m_c * _rhs.m_c - _lhs.m_d * _rhs.m_d,  // 1
			_lhs.m_a * _rhs.m_b + _lhs.m_b * _rhs.m_a + _lhs.m_c * _rhs.m_d - _lhs.m_d * _rhs.m_c,  // i
			_lhs.m_a * _rhs.m_c - _lhs.m_b * _rhs.m_d + _lhs.m_c * _rhs.m_a + _lhs.m_d * _rhs.m_b,  // j
			_lhs.m_a * _rhs.m_d + _lhs.m_b * _rhs.m_c - _lhs.m_c * _rhs.m_b + _lhs.m_d * _rhs.m_a   // k
		);
	}

	Quaternion operator*(Quaternion _lhs, float _scalar)
	{
		_lhs.m_a = _lhs.m_a * _scalar;
		_lhs.m_b = _lhs.m_b * _scalar;
		_lhs.m_c = _lhs.m_c * _scalar;
		_lhs.m_d = _lhs.m_d * _scalar;

		return Quaternion(_lhs);
	}
	Vector3				operator*(Vector3 const& _lhs, Quaternion const& _rhs)
	{
		Quaternion pos = Quaternion(0.f, _lhs.m_x, _lhs.m_y, _lhs.m_z);
		Quaternion result = (_rhs * pos) * LibMath::conjugate(_rhs);

		return Vector3(result.m_b, result.m_c, result.m_d);
	}
	Quaternion operator/(Quaternion _lhs, float _scalar)
	{
		_lhs.m_a = _lhs.m_a / _scalar;
		_lhs.m_b = _lhs.m_b / _scalar;
		_lhs.m_c = _lhs.m_c / _scalar;
		_lhs.m_d = _lhs.m_d / _scalar;

		return Quaternion(_lhs);
	}

	Quaternion	operator*=(Quaternion& _lhs, Quaternion const& _rhs)
	{
		_lhs.m_a = _lhs.m_a * _rhs.m_a - _lhs.m_b * _rhs.m_b - _lhs.m_c * _rhs.m_c - _lhs.m_d * _rhs.m_d; // 1
		_lhs.m_b = _lhs.m_a * _rhs.m_b + _lhs.m_b * _rhs.m_a + _lhs.m_c * _rhs.m_d - _lhs.m_d * _rhs.m_c; // i
		_lhs.m_c = _lhs.m_a * _rhs.m_c - _lhs.m_b * _rhs.m_d + _lhs.m_c * _rhs.m_a + _lhs.m_d * _rhs.m_b; // j
		_lhs.m_d = _lhs.m_a * _rhs.m_d + _lhs.m_b * _rhs.m_c - _lhs.m_c * _rhs.m_b + _lhs.m_d * _rhs.m_a; // k

		return (_lhs);
	}

	Quaternion conjugate(Quaternion const& _other)
	{
		return Quaternion(_other.m_a, -_other.m_b, -_other.m_c, -_other.m_d);
	}

	float quaternionMagnitude(Quaternion const& _other)
	{
		return float(squareRoot(quaternionMagnitudeSquared(_other)));
	}

	float quaternionMagnitudeSquared(Quaternion const& _other)
	{
		return (
			_other.m_d * _other.m_d +
			_other.m_a * _other.m_a +
			_other.m_b * _other.m_b +
			_other.m_c * _other.m_c);
	}

	float quaternionDotProduct(Quaternion const& _lhs, Quaternion const& _rhs)
	{
		return float(
			_lhs.m_a * _rhs.m_a +
			_lhs.m_b * _rhs.m_b +
			_lhs.m_c * _rhs.m_c +
			_lhs.m_d * _rhs.m_d);
	}

	Quaternion quaternionCrossProduct(Quaternion const& _lhs, Quaternion const& _rhs)
	{
		return Quaternion(
			_lhs.m_d * _rhs.m_d - _lhs.m_a * _rhs.m_a - _lhs.m_b * _rhs.m_b - _lhs.m_c * _rhs.m_c,  // 1
			_lhs.m_d * _rhs.m_a + _lhs.m_a * _rhs.m_d + _lhs.m_b * _rhs.m_c - _lhs.m_c * _rhs.m_b,  // i
			_lhs.m_d * _rhs.m_b - _lhs.m_a * _rhs.m_c + _lhs.m_b * _rhs.m_d + _lhs.m_c * _rhs.m_a,  // j
			_lhs.m_d * _rhs.m_c + _lhs.m_a * _rhs.m_b - _lhs.m_b * _rhs.m_a + _lhs.m_c * _rhs.m_d   // k
		);
	}

	bool isUnitQuaternion(Quaternion const& _other)
	{
		if (quaternionMagnitude(_other) == 1.f)
		{
			return true;
		}

		return false;
	}

	Quaternion normalize(Quaternion const& _other)
	{
		return Quaternion(_other / quaternionMagnitude(_other));
	}

	Quaternion inverse(Quaternion const& _other)
	{
		return Quaternion(conjugate(_other) / quaternionMagnitudeSquared(_other));
	}

	Quaternion slerp(Quaternion const& _quat1, Quaternion const& _quat2, float _scalar)
	{
		float cosHalfTheta = quaternionDotProduct(_quat1, _quat2);

		const float sign = floatSelect(cosHalfTheta);
		cosHalfTheta *= sign;

		float scale0 = 1.f - _scalar;
		float scale1 = _scalar * sign;

		if (cosHalfTheta < 0.9999f)
		{
			const float omega = acosf(cosHalfTheta);
			const float invSin = 1.f / sinf(omega);
			scale0 = sinf(scale0 * omega) * invSin;
			scale1 = sinf(scale1 * omega) * invSin;
		}

		return Quaternion(
			scale0 * _quat1.m_a + scale1 * _quat2.m_a,
			scale0 * _quat1.m_b + scale1 * _quat2.m_b,
			scale0 * _quat1.m_c + scale1 * _quat2.m_c,
			scale0 * _quat1.m_d + scale1 * _quat2.m_d);
	}

	Vector4 rotatePoint(Quaternion const& _quat, Vector4 const& _vec)
	{
		Quaternion result = _quat * Quaternion{ _vec.m_x, _vec.m_y, _vec.m_z, _vec.m_w } * conjugate(_quat);

		return Vector4(result.m_a, result.m_b, result.m_c, result.m_d);
	}

	Matrix4 toMatrix4(Quaternion const& _other)
	{
		Matrix4 mat;

		mat.m_matrix[0][0] = power(_other.m_a, 2) + power(_other.m_b, 2) - power(_other.m_c, 2) - power(_other.m_d, 2);
		mat.m_matrix[0][1] = 2 * (_other.m_b * _other.m_c) + 2 * (_other.m_a * _other.m_d);
		mat.m_matrix[0][2] = 2 * (_other.m_b * _other.m_d) - 2 * (_other.m_a * _other.m_c);
		mat.m_matrix[0][3] = 0.f;

		mat.m_matrix[1][0] = 2 * (_other.m_b * _other.m_c) - 2 * (_other.m_a * _other.m_d);
		mat.m_matrix[1][1] = power(_other.m_a, 2) - power(_other.m_b, 2) + power(_other.m_c, 2) - power(_other.m_d, 2);
		mat.m_matrix[1][2] = 2 * (_other.m_c * _other.m_d) + 2 * (_other.m_a * _other.m_b);
		mat.m_matrix[1][3] = 0.f;

		mat.m_matrix[2][0] = 2 * (_other.m_b * _other.m_d) + 2 * (_other.m_a * _other.m_c);
		mat.m_matrix[2][1] = 2 * (_other.m_c * _other.m_d) - 2 * (_other.m_a * _other.m_b);
		mat.m_matrix[2][2] = power(_other.m_a, 2) - power(_other.m_b, 2) - power(_other.m_c, 2) + power(_other.m_d, 2);
		mat.m_matrix[2][3] = 0.f;

		mat.m_matrix[3][0] = 0.f;
		mat.m_matrix[3][1] = 0.f;
		mat.m_matrix[3][2] = 0.f;
		mat.m_matrix[3][3] = 1.f;

		return mat;
	}

	float		floatSelect(float _comparand)
	{
		return _comparand >= 0.f ? 1.f : -1.f;
	}

} // !Namespace LibMath.