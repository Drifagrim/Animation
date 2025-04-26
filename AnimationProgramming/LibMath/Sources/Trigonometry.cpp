/// Header
#include <cmath>

#include "Trigonometry.h"

namespace LibMath
{
	float const trigoPi		= 3.141592653589793f;
	float const trigo2Pi	= 6.283185307179586f;
	float const trigoHalfPi = 1.570796326794896f;

	/// Calcul the sinus of the radian angle
	float	sin(Radian _value)
	{
		return ::sin(_value.raw());
	}
	/// Calcul the cosinus of the radian angle
	float	cos(Radian _value)
	{
		return ::cos(_value.raw());
	}
	/// Calcul the tangent of the radian angle
	float	tan(Radian _value)
	{
		return ::tan(_value.raw());
	}
	/// Calcul the arcsin of a float parameter and return a radian angle
	Radian asin(float _value)
	{
		return Radian(::asin(_value));
	}
	///	Calcul the arccos of a float parameter and return radian angle
	Radian acos(float _value)
	{
		return Radian(::acos(_value));
	}
	/// Calcul the arctan of a float parameter and return radian angle
	Radian atan(float _value)
	{
		return Radian(::atan(_value));
	}
	/// Calcul the arctan of two float parameters and return radian angle
	Radian atan2(float _x, float _y)
	{
		if (_x == 0.f && _y == 0.f)
		{
			throw std::invalid_argument("Atan2 with x and y == 0 is undefined.");
		}

		return Radian(::atan2(_x, _y));
	}

} // !Namespace LibMath