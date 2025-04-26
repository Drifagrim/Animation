#ifndef __LIBMATH__VECTOR__VECTOR3_H__
#define __LIBMATH__VECTOR__VECTOR3_H__

#pragma region Header

///Standard librairies
#include <iostream>
#include <string>
#include <sstream>

///Angle librairies
#include "Angles/Angle.h"

///Vector librairies
#include "Vector.h"

///Arithmetic librairie
#include "Arithmetic.h"

#pragma endregion

namespace LibMath
{
	class Vector2;
	class Vector4;


	///Vector in 3 dimensions
	class Vector3
	{
	public:

#pragma region Constructor

		///Constructor
							/// default constructor
							Vector3(void) = default;
							/// set all component to the same value
		explicit			Vector3(float);
							/// set all component individually
							Vector3(float, float, float);
							/// copy all component
							Vector3(Vector3 const&) = default;
							/// Move constructor
							Vector3(Vector3&& other) = default;
#pragma endregion

#pragma region Set vector

		///Static

		/// return a vector with all its component set to 0
		static Vector3		zero(void);
		/// return a vector with all its component set to 1
		static Vector3		one(void);
		/// return a unit vector pointing upward
		static Vector3		up(void);
		/// return a unit vector pointing downward
		static Vector3		down(void);
		/// return a unit vector pointing left
		static Vector3		left(void);
		/// return a unit vector pointing right
		static Vector3		right(void);
		/// return a unit vector pointing forward
		static Vector3		front(void);
		/// return a unit vector pointing backward
		static Vector3		back(void);
#pragma endregion

#pragma region Other functions

		///Other functions
		
		/// return smallest angle between 2 vector
		Radian				angleFrom(Vector3 const&) const;

		/// return distance between 2 points
		float				distanceFrom(Vector3 const&) const;
		/// return square value of the distance between 2 points
		float				distanceSquaredFrom(Vector3 const&) const;
		/// return the distance between 2 points on the X-Y axis only
		float				distance2DFrom(Vector3 const&) const;
		/// return the square value of the distance between 2 points points on the X-Y axis only
		float				distance2DSquaredFrom(Vector3 const&) const;
		/// return dot product result
		float				dot(Vector3 const&) const;
		/// return vector magnitude
		float				magnitude(void) const;
		/// return square value of the vector magnitude
		float				magnitudeSquared(void) const;

		/// return true if this vector magnitude is greater than the other
		bool				isLongerThan(Vector3 const&) const;
		/// return true if this vector magnitude is less than the other
		bool				isShorterThan(Vector3 const&) const;
		/// return true if this vector magnitude is 1
		bool				isUnitVector(void) const;

		/// return a copy of the cross product result
		Vector3				cross(Vector3 const&) const;
		/// scale this vector to have a magnitude of 1
		Vector3&			normalize(void);
		/// project this vector onto an other
		Vector3&			projectOnto(Vector3 const&);
		/// reflect this vector by an other
		Vector3&			reflectOnto(Vector3 const&);
		/// rotate this vector using euler angle apply in the z, x, y order
		Vector3&			rotate(Radian, Radian, Radian);
		/// rotate this vector around an arbitrary axis
		Vector3&			rotate(Radian, Vector3 const&);
		//Vector3&			rotate(Quaternion const&); todo quaternion					/// rotate this vector using a quaternion rotor
		/// scale this vector by a given factor
		Vector3&			scale(Vector3 const&);
		/// offset this vector by a given distance
		Vector3&			translate(Vector3 const&);

		/// Lerp position
		static Vector3		lerpPosition(Vector3 const& _start, Vector3 const& _end, float _t);

		/// Lerp scale
		static Vector3		lerpScale(Vector3 const& _start, Vector3 const& _end, float _t);
		/// return a string representation of this vector
		std::string			string(void) const;
		/// return a verbose string representation of this vector
		std::string			stringLong(void) const;
#pragma endregion

#pragma region In class operator

		///In class operator

		/// copy assignement
		Vector3&			operator=(Vector3 const&);

		/// return this vector component value
		float&				operator[](int);
		/// return this vector component value
		float				operator[](int) const;

		/// Calcul the addition between vector 3 and scalar
		Vector3				operator+(float);
		/// Calcul the substraction between vector 3 and scalar
		Vector3				operator-(float);
		/// Calcul the multiplication between vector 3 and scalar
		Vector3				operator*(float);
		/// Calcul the division between vector 3 and scalar
		Vector3				operator/(float);

		/// Calcul the addition between vector 3 and scalar
		Vector3&			operator+=(float);
		/// Calcul the substraction between vector 3 and scalar
		Vector3&			operator-=(float);
		/// Calcul the multipplication between vector 3 and scalar
		Vector3&			operator*=(float);
		/// Calcul the division between vector 3 and scalar
		Vector3&			operator/=(float);

							/// Convert vector 3 into vector 2
							operator Vector2(void) const;
							/// Convert vector 3 into vector 4
							operator Vector4(void) const;
#pragma endregion

#pragma region Destructor

		///Destructor
							
							/// Default destructor
							~Vector3(void) = default;
#pragma endregion
		
		/// Variables
		/// Put z before x and y because of glm initailize before them
		/// And it does an error while do the memcmp in Vector_UniTest
		/// In the instanciation line 56
		float m_z{ 0 };
		float m_x{ 0 };
		float m_y{ 0 };

	}; // !Class Vector3

#pragma region Out class operator

	///Out class operator

	/// Vector3{ 1 } == Vector3::one()				// true					// return if 2 vectors have the same component
	bool					operator==(Vector3 const&, Vector3 const&);
	/// Vector3{ 1 } != Vector3::one()				// false				// return if 2 vectors differ by at least a component
	bool					operator!=(Vector3 const&, Vector3 const&);

	/// - Vector3{ .5, 1.5, -2.5 }					// { -.5, -1.5, 2.5 }	// return a copy of a vector with all its component inverted
	Vector3					operator-(Vector3);

	/// Vector3{ .5, 1.5, -2.5 } + Vector3::one()	// { 1.5, 2.5, -1.5 }	// add 2 vectors component wise
	Vector3					operator+(Vector3 const&, Vector3 const&);
	/// Vector3{ .5, 1.5, -2.5 } - Vector3{ 1 }		// { -.5, .5, -3.5 }	// substract 2 vectors component wise
	Vector3					operator-(Vector3 const&, Vector3 const&);
	/// Vector3{ .5, 1.5, -2.5 } * Vector3::zero()	// { 0, 0, 0 }			// multiply 2 vectors component wise
	Vector3					operator*(Vector3 const&, Vector3 const&);
	/// Vector3{ .5, 1.5, -2.5 } / Vector3{ 2 }		// { .25, .75, -1.25 }	// divide 2 vectors component wise
	Vector3					operator/(Vector3 const&, Vector3 const&);


	/// addition component wise
	Vector3&				operator+=(Vector3&, Vector3 const&);
	/// substraction component wise
	Vector3&				operator-=(Vector3&, Vector3 const&);
	/// multiplication component wise
	Vector3&				operator*=(Vector3&, Vector3 const&);
	/// division component wise
	Vector3&				operator/=(Vector3&, Vector3 const&);

	/// cout << Vector3{ .5, 1.5, -2.5 }			// add a vector string representation to an output stream
	std::ostream&			operator<<(std::ostream&, Vector3 const&);
	/// ifstream file{ save.txt }; file >> vector;	// parse a string representation from an input stream into a vector
	std::istream&			operator>>(std::istream&, Vector3&);
#pragma endregion

} // !Namespace LibMath

#endif // !__LIBMATH__VECTOR__VECTOR3_H__
