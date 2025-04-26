///Header
#include "Angles/Angle.h"

namespace LibMath
{
#pragma region Degree

#pragma region Constructor

	///Constructor wich takes value to give to m_value
						Degree::Degree(float value)
	{
		this->m_value = value;
	}
	///Copy constructor give the value of other to a no existing object
						Degree::Degree(Degree const& other)
	{
		this->m_value = other.m_value;
	}

#pragma endregion Constructor

#pragma region In class operator

	///Convert degree angle in radian angle
	Degree::operator	Radian() const
	{
		return Radian(this->m_value * ((float)PI / 180));
	}
	///Copy assignement to give a value to an existing object
	Degree&				Degree::operator=(Degree const& other)
	{
		if (this != &other)
		{
			this->m_value = other.m_value;
		}

		return *this;
	}
	///Add other degree to the value
	Degree&				Degree::operator+=(Degree other)
	{
		this->m_value += other.m_value;

		return *this;
	}
	///Substract other degree to the value
	Degree&				Degree::operator-=(Degree other)
	{
		this->m_value -= other.m_value;

		return *this;
	}
	///Multiply degree with a float value
	Degree&				Degree::operator*=(float value)
	{
		this->m_value *= value;

		return *this;
	}
	///Divide degree by a float value
	Degree&				Degree::operator/=(float value)
	{
		this->m_value /= value;

		return *this;
	}

#pragma endregion In class operator

#pragma region Other functions

	///Call degree function to wrap the range
	void				Degree::wrap(bool range)
	{
		this->m_value = degree(range);
	}
	///Function to return degree in float and clamp the range
	float				Degree::degree(bool range) const
	{
		// Value in degree of a complete circle
		const float	circle		= 360.0f;
		// Value in degree of the half of a circle
		const float halfCircle	= 180.0f;
		// Check the absolute value sign
		float		absValue	= (this->m_value >= 0) ? this->m_value : -this->m_value;

		// if absolute value is > 360
		if (absValue >= circle)
		{
			// Divide absolute value by 360
			int	count = static_cast<int>(absValue / circle);

			// Substract the absolute value to the previous result multiply by 360
			absValue -= count * circle;
		}

		// If we want to clamp [-180, 180[
		if (range)
		{
			// If absolute value is > 180
			if (absValue >= halfCircle)
				// Substract the absolute value to 360
				absValue -= circle;

			// If the angle < 0
			if (this->m_value < 0)
				// Absolute value become negative
				absValue = -absValue;
		}

		// If the clamp is [0, 360[ and the angle < 0
		else if (!range && this->m_value < 0)
			// Absolute value is equal to 360 - absolute value
			absValue = circle - absValue;

		// Return the angle in regard to the clamp needed
		return absValue;
	}
	///Return angle in radian 
	float				Degree::radian(bool range) const 
	{
		// Value in degree of a complete circle
		const float	circle		= 360.f;
		// Value in radian of a complete circle
		const float radCircle	= PI * 2.f;
		// Check the absolute value sign
		float		absValue	= (this->m_value >= 0) ? this->m_value : -this->m_value;

		// If absolute value >= to 360
		if (absValue >= circle)
		{
			// Divide absolute value to 360
			int	circleCount = static_cast<int>(absValue / circle);

			// Substract absolute value with the previous result multiply by 360
			absValue -= circleCount * circle;
		}

		// Convert angle from degree to radian
		absValue *= (PI / 180.f);

		// If clamp the range is [-pi, pi[
		if (range)
		{
			// If absolute value >= pi
			if (absValue >= PI)
				// Substract absolute value to pi * 2
				absValue -= radCircle;

			// If the angle is < 0
			if (this->m_value < 0)
				// Absolute value become negative
				absValue = -absValue;
		}
		// If not clamp the range is [0, pi * 2[
		else if (!range && this->m_value < 0)
			// Absolute value is equal to pi * 2 substract by absolute value
			absValue = radCircle - absValue;

		// Return the angle in regard to the clamp needed
		return absValue;
	}
	///Return m_value
	float				Degree::raw() const
	{
		return this->m_value;
	}

#pragma endregion Other functions

#pragma region Out class operator

	///Check if degree lhs is equal to degree rhs
	bool				LibMath::operator==(Degree lhs, Degree rhs)
	{
		// Call trigonometry function to adjust the precision
		return almostEqual(lhs.degree(), rhs.degree());
	}
	///Check if thee degree lhs is equal to radian rhs
	bool				operator==(Degree lhs, Radian const& rhs)
	{
		// Call trigonometry function to adjust the precision
		return almostEqual(lhs.degree(), rhs.degree());
	}
	///Change the angle sign
	Degree				operator-(Degree other)
	{
		return Degree(-other.raw());
	}
	///Add two degree object
	Degree				operator+(Degree lhs, Degree rhs)
	{
		return Degree(lhs.raw() + rhs.raw());
	}
	///Substract two degree object
	Degree				operator-(Degree lhs, Degree rhs)
	{
		return Degree(lhs.raw() - rhs.raw());
	}
	///Multiply degree object to float value
	Degree				operator*(Degree lhs, float scalar)
	{
		return Degree(lhs.raw() * scalar);
	}
	///Divide degree object by a float value
	Degree				operator/(Degree lhs, float scalar)
	{
		return Degree(lhs.raw() / scalar);
	}
	///Define the suffix of the value
	Degree				Literal::operator""_deg(long double value)
	{
		return Degree((float)value);
	}
	///Define the suffix of the value
	Degree				Literal::operator""_deg(unsigned long long int value)
	{
		return Degree((float)value);
	}

#pragma endregion Out class operator

#pragma endregion



#pragma region Radian

#pragma region Constructor

	///Radian constructor
						Radian::Radian(float value)
	{
		this->m_value = value;
	}
	///Radian copy constructor
						Radian::Radian(Radian const& other)
	{
		this->m_value = other.m_value;
	}

#pragma endregion Constructor

#pragma region In class operator

	///Convert radian angle to degree angle
	Radian::operator	Degree() const
	{
		return Degree(this->m_value * (180 / (float)PI));
	}
	///Copy assignement
	Radian&				Radian::operator=(Radian const& other)
	{
		this->m_value = other.m_value;

		return *this;
	}
	///Add the radian angle with another radian angle
	Radian&				Radian::operator+=(Radian other)
	{
		this->m_value += other.m_value;

		return *this;
	}
	///Substract the radian angle with another radian angle
	Radian&				Radian::operator-=(Radian other)
	{
		this->m_value -= other.m_value;

		return *this;
	}
	///Multiply the radian angle by a scalar
	Radian&				Radian::operator*=(float scalar)
	{
		this->m_value *= scalar;

		return *this;
	}
	///Divide the radian angle by a scalar
	Radian&				Radian::operator/=(float scalar)
	{
		this->m_value /= scalar;

		return *this;
	}

#pragma endregion In class operator

#pragma region Other functions

	///Call radian function to wrap the range
	void				Radian::wrap(bool range)
	{
		this->m_value = radian(range);
	}
	///Function to convert a degree angle in radian and clamp it then return the value of the angle
	float				Radian::degree(bool range) const
	{
		// Value in radian of a complete circle
		const float	circle		= PI * 2.f;
		// Value in degree of a complete circle
		const float degCircle	= 360.f;
		// Value in degree of the half of a circle
		const float halfCircle	= 180.f;
		// Check the sign of the angle
		float		absValue	= (this->m_value >= 0) ? this->m_value : -this->m_value;

		// If the absolute value > 2 * pi
		if (absValue >= circle)
		{
			// Divide the absolute angle by 2 * pi
			int	circleCount = static_cast<int>(absValue / circle);

			// Absolute value is substract by the previous result multiply by 2 * pi
			absValue -= circleCount * circle;
		}

		// Convert in degree the angle
		absValue *= (180 / PI);

		// If the clamp needed is [-180, 180[
		if (range)
		{
			// If absolute value is >= 180
			if (absValue >= halfCircle)
				// Substract absolute value with 360
				absValue -= degCircle;

			// If the angle < 0 and absolute value > 0
			if (this->m_value < 0 && absValue > 0)
				// Absolute value is equal to the reverse absolute value
				absValue = -absValue;
		}
		// If the clamp needed is [0, 360[ and the angle < 0
		else if (!range && this->m_value < 0)
			// Absolute value is equal to 360 - absolute value
			absValue = degCircle - absValue;

		// Return in regard to the clamp needed the angle
		return absValue;
	}
	///Function to clamp the angle then return the value of the angle
	float				Radian::radian(bool range) const
	{
		// Value in radian of a complete circle
		const float	circle		= PI * 2.f;
		// Check the sign of the angle
		float		absValue	= (this->m_value >= 0) ? this->m_value : -this->m_value;

		// If absolute value >= pi * 2
		if (absValue >= circle)
		{
			// Divide the absolute value by pi * 2
			int	circleCount = static_cast<int>(absValue / circle);

			// Substract absolute value by the previous result multiply by pi * 2
			absValue -= circleCount * circle;
		}
			
		// If clamp needed is [-pi, pi[
		if (range)
		{
			// If absolute value >= pi
			if (absValue >= PI)
				// Substract absolute value by pi * 2
				absValue -= circle;

			// If the angle < 0 and absolute value > 0
			if (this->m_value < 0 && absValue > 0)
				// Absolute value is equal to it reverse
				absValue = -absValue;
		}
		// If the clamp needed is [0, 2 * pi[
		else if (!range && this->m_value < 0)
			// Absolute value is equal to 2 * pi substract by absolute value
			absValue = circle - absValue;

		// Return the angle in the clamp needed
		return absValue;
	}
	///Function to return the radian angle in value
	float				Radian::raw() const
	{
		return this->m_value;
	}

#pragma endregion Other functions

#pragma region Out class operator

	///Check the equality between two radian angle
	bool				operator==(Radian lhs, Radian rhs)
	{
		if (lhs.raw() == rhs.raw())
		{
			return true;
		}
		if (lhs.raw() < rhs.raw())
		{
			Radian result = rhs;

			if (result.radian(true))
			{
				return true;
			}
			else if (lhs.raw() == 0.0f && rhs.raw() == (2 * PI))
			{
				return true;
			}
			else
				return false;
		}

		return false;
	}
	///Check the inequality between radian angle and degree angle
	bool				operator==(Radian lhs, Degree const& rhs)
	{
		rhs.operator LibMath::Radian();

		if (lhs.raw() == rhs.raw())
		{
			return true;
		}
		if (lhs.raw() < rhs.raw())
		{
			Radian result = rhs;

			if (result.radian(true))
			{
				return true;
			}
			else if (lhs.raw() == 0.0f && rhs.raw() == (2 * PI))
			{
				return true;
			}
			else
				return false;
		}

		return false;
	}
	///Change the angle sign
	Radian				operator-(Radian other)
	{
		return Radian(-other.raw());
	}
	///Add two radian angle
	Radian				operator+(Radian lhs, Radian rhs)
	{
		return Radian(lhs.raw() + rhs.raw());
	}
	///Substract two radian angle
	Radian				operator-(Radian lhs, Radian rhs)
	{
		return Radian(lhs.raw() - rhs.raw());
	}
	///Multiply a radian angle by a scalar
	Radian				operator*(Radian lhs, float scalar)
	{
		return Radian(lhs.raw() * scalar);
	}
	///Divide a radian angle by a scalar
	Radian				operator/(Radian lhs, float scalar)
	{
		return Radian(lhs.raw() / scalar);
	}
	Radian				operator+(Radian lhs, float scalar)
	{
		return Radian(lhs.raw() + scalar);
	}
	Radian				operator-(Radian lhs, float scalar)
	{
		return Radian(lhs.raw() - scalar);
	}
	///Define the suffix of the value
	Radian				Literal::operator""_rad(long double value)
	{
		return Radian((float)value);
	}
	///Define the suffix of the value
	Radian				Literal::operator""_rad(unsigned long long int value)
	{
		return Radian((float)value);
	}

#pragma endregion Out class operator

#pragma endregion

} // !Namespace LibMath