#ifndef __LIBMATH__QUATERNION_H__
#define __LIBMATH__QUATERNION_H__

#pragma region Vector

#include "Vector/Vector4.h"

#pragma endregion

#pragma region Matrix

#include "Matrix/Matrix4.h"

#pragma endregion

namespace LibMath
{
	class Quaternion
	{
	public :

		Quaternion(void) : m_a(0.0f), m_b(0.0f), m_c(0.0f), m_d(0.0f) {}
		Quaternion(float _a, float _b, float _c, float _d) : m_a(_a), m_b(_b), m_c(_c), m_d(_d) {}

		/// Class members.

		float m_a;
		float m_b;
		float m_c;
		float m_d;

	}; // !Class Quaternion.


	/// Out of class operators.
	Quaternion	operator-(Quaternion const& _other);
	Quaternion	operator+(Quaternion _lhs, Quaternion const& _rhs);
	Quaternion	operator*(Quaternion const& _lhs, Quaternion const& _rhs);
	Quaternion	operator*(Quaternion _lhs, float _scalar);
	Quaternion	operator/(Quaternion _lhs, float _scalar);
	Vector3		operator*(Vector3 const& _lhs, Quaternion const& _rhs);
	Quaternion	operator*=(Quaternion& _lhs, Quaternion const& _rhs);

	/// Out of class functions.
	Quaternion	conjugate(Quaternion const& _other);
	float		quaternionMagnitude(Quaternion const& _other);
	float 		quaternionMagnitudeSquared(Quaternion const& _other);
	float 		quaternionDotProduct(Quaternion const& _lhs, Quaternion const& _rhs);
	Quaternion  quaternionCrossProduct(Quaternion const& _lhs, Quaternion const& _rhs);
	bool		isUnitQuaternion(Quaternion const& _other);
	Quaternion	normalize(Quaternion const& _other);
	Quaternion	inverse(Quaternion const& _other);
	Quaternion	slerp(Quaternion const& _quat1, Quaternion const& _quat2, float _scalar);
	Vector4		rotatePoint(Quaternion const&, Vector4 const&);
	Matrix4		toMatrix4(Quaternion const& _other);

	float		floatSelect(float _comparand);

} // !Namespace LibMath.

#endif // !__LIBMATH__QUATERNION_H__
