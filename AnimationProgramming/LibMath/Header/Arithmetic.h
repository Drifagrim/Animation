#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__

#pragma region Header

///Standard librairies
#include <iostream>

#pragma endregion

namespace LibMath
{
	/// Function to return the good sign of the value
	float	absolute(float);
	/// Check if two floating are almost the same at the precision of 8 number after comma
	bool	almostEqual(float, float);
	/// Return highest integer value lower or equal to parameter
	float	floor(float);
	/// Return lowest integer value higher or equal to parameter
	float	ceiling(float);
	/// Return parameter limited by the given range
	float	clamp(float, float, float);
	/// Return square root of parameter
	float	squareRoot(float);
	/// Return parameter as value inside the given range
	float	wrap(float, float, float);
	/// Return the power of a number
	float	power(float, int);
	/// Return the rest of the division
	float	fmod(float, float);
	/// Swap the value of two int
	void	swap(int&, int&);
	/// Swap the value of two float;
	void	swap(float&, float&);
	/// Return the min between the two float
	float&	min(float&, float&);
	/// Return the max between the two float
	float&	max(float&, float&);

} // !Namespace LibMath

#endif // !__LIBMATH__ARITHMETIC_H__
