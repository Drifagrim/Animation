#ifndef __LIBMATH__TRIGONOMETRY_H__
#define __LIBMATH__TRIGONOMETRY_H__

#pragma region Header

/// Standard librairies
#include <iostream>

/// Angle librairies
#include "Angles/Angle.h"

/// Arithmetic librairies
#include "Arithmetic.h"

#pragma endregion

#pragma region Define

///Define
#define PI 3.14159265f

#pragma endregion

namespace LibMath
{
	/// float result = sin(Radian{0.5});	// 0.479426
	float	sin(Radian);
	/// float result = sin(Degree{45});		// 0.707107			// this make use implicit conversion
	float	cos(Radian);
	/// float result = sin(0.5_rad);		// 0.479426			// this make use user defined litteral
	float	tan(Radian);
	/// Radian angle = asin(0.479426);		// Radian{0.500001}
	Radian	asin(float);
	/// Degree angle = acos(0.707107);		// Degree{44.99998}	// this make use implicit conversion
	Radian	acos(float);
	/// Radian angle = atan(0.546302);		// Radian{0.500000}
	Radian	atan(float);
	/// Radian angle = atan(1, -2);			// Radian{2.677945}
	Radian	atan2(float, float);

} // !Namespace LibMath

#endif // !__LIBMATH__TRIGONOMETRY_H__
