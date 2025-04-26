#ifndef __LIBMATH__ANGLE__DEGREE_H__
#define __LIBMATH__ANGLE__DEGREE_H__

#pragma region Header

///Angle librairie
#include "Radian.h"

#pragma endregion

namespace LibMath
{
	class Radian;

	class Degree
	{
	public:

#pragma region Constructor

		///Constructor
		
					///Constructor by default
					Degree() = default;	
					///Constructor wich takes float to give a value		// explicit so no ambiguous / implicit conversion from float to angle can happen
					explicit Degree(float value);
					///Copy constructor
					Degree(Degree const& other);
#pragma endregion

#pragma region Destructor

		///Destructor
					
					///Destructor set to default
					~Degree() = default;
#pragma endregion

#pragma region In class operator

		///In class Operator
		
		/// Radian angle = Degree{45};		// implicit conversion from Degree to Radian
		operator	Radian() const;
		///Copy assignement
		Degree&		operator=(Degree const& other);
		///Operator += to add two degrees
		Degree&		operator+=(Degree other);
		///Operator -= to substract two degree
		Degree&		operator-=(Degree other);
		///Operator *= to multiply degree by a value
		Degree&		operator*=(float value);
		///Operator /= to divide degree by a value
		Degree&		operator/=(float value);
#pragma endregion

#pragma region Other functions

		///Other functions

		/// true -> limite m_value to range [-180, 180[	// false -> limite m_value to range [0, 360[
		void		wrap(bool = false);
		///Return degree in float and check the range	// return angle in degree	
		/// true -> limite value to range [-180, 180[	// false -> limite value to range [0, 360[
		float		degree(bool = false) const;
		/// return angle in radian	// true -> limite value to range [-pi, pi[
		/// false -> limite value to range [0, 2 pi[
		float		radian(bool = true) const;
		///Return m_value
		float		raw() const;
#pragma endregion

	private:

		///Variables

		float		m_value{ 0.f };

	}; // !Class Degree

#pragma region Out class operator

	///Out class Operator

	///Check the equality between two degree value		// bool isEqual = Degree{45} == Degree{45};		// true
	bool			operator==(Degree lhs, Degree rhs);
	///Check the equality between degree and radian		// bool isEqual = Degree{60} == Radian{0.5};	// false
	bool			operator==(Degree lhs, Radian const& rhs);
	///Set positive angle to negative angle				// Degree angle = - Degree{45};					// Degree{-45}
	Degree			operator-(Degree other);
	///Add two degree object							// Degree angle = Degree{45} + Degree{45};		// Degree{90}
	Degree			operator+(Degree lhs, Degree rhs);
	///Substract two degree object						// Degree angle = Degree{45} - Degree{45};		// Degree{0}
	Degree			operator-(Degree lhs, Degree rhs);
	///Multiply a degree object to a float value		// Degree angle = Degree{45} * 3;				// Degree{135}
	Degree			operator*(Degree lhs, float rhs);
	///Divide a degree object to a float value			// Degree angle = Degree{45} / 3;				// Degree{15}
	Degree			operator/(Degree lhs, float rhs);

	inline namespace Literal
	{
		///Define suffix			// Degree angle = 45_deg;
		LibMath::Degree operator""_deg(long double value);
		///Define suffix	// Degree angle = 7.5_deg;
		LibMath::Degree operator""_deg(unsigned long long int value);

	} // !Namespace Literal

#pragma endregion

} // !Namespace LibMath

#endif // !__LIBMATH__ANGLE__DEGREE_H__
