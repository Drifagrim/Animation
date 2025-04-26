/// Header
#include <cmath>

#include "Arithmetic.h"

namespace LibMath
{
	/// Function to return the good sign of the value
	float absolute(float value)
	{
		return std::abs(value);
	}
	/// Check if the two value are almost same to be equal
	bool almostEqual(float lhs, float rhs)
	{
		const float precision = 0.000001f;

		return absolute(lhs - rhs) < precision;
	}
	/// Function to round lower the value
	float floor(float value)
	{
		return ::floorf(value);
	}
	/// Function to round upper the value
	float ceiling(float value)
	{
		return ::ceilf(value);
	}
	/// Function to clamp the value between a range
	float clamp(float value, float min, float max)
	{
		if (min > max)
		{
			std::cerr << "Warning: min is greater than max in clamp function. Swapping the values." << std::endl;
			swap(min, max);
		}

		return (value < min) ? min : (value > max ? max : value);
	}
	/// Calcul the square root of the value
	float squareRoot(float _value)
	{
		if (_value <= 0.f)
		{
			std::cerr << "Impossible to calcul the square root of a number inferior to 0.";
			return 0.f;
		}

		return ::sqrtf(_value);
	}
	/// Calcul the power of the value
	float power(float _value, int _exponent)
	{
		if (_exponent == 0)
		{
			std::cerr << "We can't calcul the power of a number if exponent is equal to 0";
			return -1.f;
		}

		if (_exponent == 1)
			return _value;

		if (_value == 0.f)
			return 0.f;

		float result = _value;

		for (int i = 1; i < _exponent; i++)
			_value *= result;

		return _value;
	}
	/// Return the rest of the division
	float fmod(float numerator, float denominator)
	{
		// Return the rest of the division
		return ::fmod(numerator, denominator);
	}
	/// Function to swap two integers
	void swap(int& _x, int& _y)
	{
		int temp = _x;
		_x = _y;
		_y = temp;
	}
	/// Function to swap two floats
	void swap(float& _x, float& _y)
	{
		float temp = _x;
		_x = _y;
		_y = temp;
	}
	/// Function to return the min between two value
	float& min(float& _x, float& _y)
	{
		return (_x < _y) ? _x : _y;
	}
	/// Function to return the max between two values
	float& max(float& _x, float& _y)
	{
		return (_x > _y) ? _x : _y;
	}
	/// Return parameter as value inside the given range
	float wrap(float value, float min, float max)
	{
		if (min > max)
			// Change the min and the max to set in the good order
			return wrap(value, max, min);

		else if (min == max)
			return min;

		if (value >= min && value <= max)
			return value;

		else
			return (value >= 0 ? min : max) + LibMath::fmod(value, max - min);
	}
	
} // !Namespace LibMath