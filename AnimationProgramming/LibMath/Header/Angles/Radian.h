#ifndef __LIBMATH__ANGLE__RADIAN_H__
#define __LIBMATH__ANGLE__RADIAN_H__

#pragma region Header

///Angle librairy
#include "Degree.h"

#pragma endregion

namespace LibMath
{
	class Degree;

	class Radian
	{
	public:

#pragma region Constructor

		///Constructor

					/// Default constructor
					Radian() = default;
					/// Explicit constructor
					explicit Radian(float);
					/// Copy constructor
					Radian(Radian const&);
#pragma endregion

#pragma region Destructor

		///Destructor

					/// Default destructor
					~Radian() = default;
#pragma endregion

#pragma region In class operator

		///In class operator

		/// Conversion operator form radian to degree // Degree angle = Radian{0.5}
		operator	Degree() const;
		/// Copy assignement
		Radian&		operator=(Radian const&);
		/// Add operator between two radian angle // Radian angle += Radian{0.5};
		Radian&		operator+=(Radian);
		/// Substract operator between two radian angle // Radian angle -= Radian{0.5};
		Radian&		operator-=(Radian);
		/// Multiplication operator between a radian angle and a scalar // Radian angle *= 3;
		Radian&		operator*=(float);
		/// Divide operator between a radian angle and a scalar // Radian angle /= 3;
		Radian&		operator/=(float);
#pragma endregion

#pragma region Other functions

		///Other functions

		/// true -> limite m_value to range [-pi, pi[	// false -> limite m_value to range [0, 2 pi[
		void		wrap(bool = false);
		/// return angle in degree						// true -> limite value to range [-180, 180[	
														/// false -> limite value to range [0, 360[
		float		degree(bool = false) const;
		/// return angle in radian						// true -> limite value to range [-pi, pi[		
														/// false -> limite value to range [0, 2 pi[
		float		radian(bool = true) const;
		/// return m_angle
		float		raw() const;
#pragma endregion

	private:

		///Variables
		float		m_value{ 0.f };

	}; // !Class Radian

#pragma region Out class operator

	///Out class operator

	/// Check if two angle are equal			// bool isEqual = Radian{0.5} == Radian{0.5};	// true
	bool			operator==(Radian, Radian);
	/// Check if two angle are inequal			// bool isEqual = Radian{0.5} == Degree{60};	// false
	bool			operator==(Radian, Degree const&);
	/// Reverse the angle sign					// Degree angle = - Radian{0.5};				// Radian{-0.5}
	Radian			operator-(Radian);
	/// Add two radian angle together			// Radian angle = Radian{0.5} + Radian{0.5};	// Radian{1}
	Radian			operator+(Radian, Radian);
	/// Substract two radian angle together		// Radian angle = Radian{0.5} - Radian{0.5};	// Radian{0}
	Radian			operator-(Radian, Radian);
	/// Mulitiply two radian angle together		// Radian angle = Radian{0.5} * 3;				// Radian{1.5}
	Radian			operator*(Radian, float);
	/// Divide two radian angle together		// Radian angle = Radian{0.5} / 3;				// Radian{0.166...}
	Radian			operator/(Radian, float);
	/// Add a radian angle and a float			// Radian angle = Radian{0.5} + 3;				// Radian{3.5}
	Radian			operator+(Radian, float);
	/// Substract a radian angle and a float	// Radian angle = Radian{0.5} - 3;				// Radian{-2.5}
	Radian			operator-(Radian, float);

	inline namespace Literal
	{
		/// Put the _rad suffix // Radian angle = 0.5_rad;
		LibMath::Radian operator""_rad(long double);
		/// Put the _rad suffix // Radian angle = 1_rad;
		LibMath::Radian operator""_rad(unsigned long long int);
	}

#pragma endregion

} // ! Namespace LibMath

#endif // !__LIBMATH__ANGLE__RADIAN_H__
