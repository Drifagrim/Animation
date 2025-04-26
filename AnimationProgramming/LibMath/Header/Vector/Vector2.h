#pragma once

#ifndef __LIBMATH__VECTOR__VECTOR2_H__
#define __LIBMATH__VECTOR__VECTOR2_H__

#pragma region Header

///Standard librairies
#include <string>
#include <iostream>
#include <sstream>

///Vector librairies
#include "Vector/Vector.h"

///Angle librairies
#include "Angles/Angle.h"

#pragma endregion

namespace LibMath
{
	class Vector3;
	class Vector4;


	///Vector in 2 dimensions
	class Vector2
	{
	public:

#pragma region Constructor

		///Constructor

							/// Constructor to zero
							Vector2(void) = default;
							/// Constructor with on scalar where x and y take the same value
		explicit			Vector2(float);
							/// Constructor with two scalar where x takes a value, and y takes b value
							Vector2(float, float);
							/// Copy constructor to default
							Vector2(Vector2 const&) = default;
							/// Move constructor to default
							Vector2(Vector2&& other) = default;
#pragma endregion

#pragma region Set vector

		///Static

		/// set all components to zero
		static Vector2		zero(void); 
		/// set all components to one
		static Vector2		one(void);
		/// return a unit vector pointing upward
		static Vector2		up(void);
		/// return a unit vector pointing downward
		static Vector2		down(void);
		/// return a unit vector pointing left
		static Vector2		left(void);
		/// return a unit vector pointing right
		static Vector2		right(void);
#pragma endregion

#pragma region Other functions

		///Other vector functions

		/// return smallest angle between 2 vector
		Radian				angleFrom(Vector3 const&) const;

		/// return distance between 2 points
		float				distanceFrom(const Vector2&) const;
		/// return square value of the distance between 2 points
		float				squaredDistanceFrom(const Vector2&) const;
		/// Dot product between two vectors
		float				dotProduct(const Vector2&) const;
		/// Calcul the magnitude of a vector
		float				magnitude(void) const;
		/// Calcul the square magnitude of a vector
		float				squareMagnitude(void) const;
		/// return a copy of the cross product result
		float				crossProduct(const Vector2&) const;

		/// Check if the vector is unitary or not
		bool				isUnit(void) const;
		/// return true if this vector magnitude is greater than the other
		bool				isLongerThan(const Vector2&) const;
		/// return true if this vector magnitude is less than the other
		bool				isShorterThan(const Vector2&) const;

		
		/// Calcul the normalise vector
		Vector2&			normalize(void);
		/// Calcul projection of a vector on another
		Vector2&			project(const Vector2&);
		/// Calcul the reflect vector of a vector
		Vector2&			reflection(const Vector2&);
		//Vector2&			rotate(Quaternion const&); //todo quaternion			/// rotate this vector using a quaternion rotor
		/// scale this vector by a given factor
		Vector2&			scale(const Vector2&);
		/// offset this vector by a given distance
		Vector2&			translate(const Vector2&);

		/// return a string representation of this vector
		std::string			string(void) const;
		/// return a verbose string representation of this vector
		std::string			stringLong(void) const;
#pragma endregion

#pragma region In class operator

		///In class operator

		/// copy assignement
		Vector2&			operator=(Vector2 const&);

		/// return this vector component value
		float&				operator[](int);
		/// return this vector component value
		float				operator[](int) const;

		/// Calcul the addition between vector 2 and scalar
		Vector2				operator+(float);
		/// Calcul the substraction between vector 2 and scalar
		Vector2				operator-(float);
		/// Calcul the multiplication between vector 2 and scalar
		Vector2				operator*(float);
		/// Calcul the division between vector 2 and scalar
		Vector2				operator/(float);

		/// Calcul the addition between vector 2 and scalar
		Vector2&			operator+=(float);
		/// Calcul the substraction between vector 2 and scalar
		Vector2&			operator-=(float);
		/// Calcul the multipplication between vector 2 and scalar
		Vector2&			operator*=(float);
		/// Calcul the division between vector 2 and scalar
		Vector2&			operator/=(float);

							/// Convert vector 2 into vector 3
							operator Vector3(void) const;
							/// Convert vector 2 into vector 4
							operator Vector4(void) const;
#pragma endregion

#pragma region Destructor

		///Destructor

							/// Default destructor
							~Vector2(void) = default;
#pragma endregion


		///Variables
		float m_x{ 0 };
		float m_y{ 0 };
	};

#pragma region Out class operator

	///Out class operator
	
	/// Vector3{ 1 } == Vector3::one()		// true					// return if 2 vectors have the same component
	bool					operator==(const Vector2&, const Vector2&);
	/// Vector3{ 1 } != Vector3::one()		// false				// return if 2 vectors differ by at least a component
	bool					operator!=(const Vector2&, const Vector2);

	/// - Vector3{ .5, 1.5, -2.5 }			// { -.5, -1.5, 2.5 }	// return a copy of a vector with all its component inverted
	Vector2					operator-(Vector2);

	/// Addition of two vectors
	Vector2					operator+(const Vector2&, const Vector2&);
	/// Substraction of two vectors
	Vector2					operator-(const Vector2&, const Vector2&);
	/// Scalar Multiplication of two vectors
	Vector2					operator*(const Vector2&, const Vector2&);
	/// Multiplication of a vector with a scalar
	Vector2					operator/(const Vector2, const Vector2&);

	/// addition component wise
	Vector2&				operator+=(Vector2&, const Vector2&);
	/// substraction component wise
	Vector2&				operator-=(Vector2&, const Vector2&);
	/// multiplication component wise
	Vector2&				operator*=(Vector2&, const Vector2&);
	/// division component wise
	Vector2&				operator/=(Vector2&, const Vector2&);

	/// cout << Vector3{ .5, 1.5, -2.5 }			// add a vector string representation to an output stream
	std::ostream&			operator<<(std::ostream&, const Vector2&);
	/// ifstream file{ save.txt }; file >> vector;	// parse a string representation from an input stream into a vector
	std::istream&			operator>>(std::istream&, Vector2&);
#pragma endregion
}	

#endif // !__LIBMATH__VECTOR__VECTOR2_H__