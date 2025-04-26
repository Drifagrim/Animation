#ifndef __LIBMATH__VECTOR__VECTOR4_H__
#define __LIBMATH__VECTOR__VECTOR4_H__

#pragma region Header

///Standard librairies
#include <iostream>
#include <string>

///Angle librairies
#include "Angles/Angle.h"

///Vector librairies
#include "Vector.h"

///Arithmertic librairies
#include "Arithmetic.h"

#pragma endregion

namespace LibMath
{
	class Vector2;
	class Vector3;


	///Vector in 4 dimensions
	class Vector4
	{
	public:

#pragma region Constructor

		///Constructor

							/// Default constructor
							Vector4(void) = default;
							/// set all component to the same value
		explicit			Vector4(float);
							/// set all component individually
							Vector4(float, float, float, float);
							/// Default copy constructor
							Vector4(Vector4 const&) = default;
#pragma endregion

#pragma region Set vector

		///Static

		/// return a vector with all its component set to 0
		static Vector4		zero(void);
		/// return a vector with all its component set to 1
		static Vector4		one(void);
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
		Radian				angleFrom(Vector4 const&) const;

		/// return distance between 2 points
		float				distanceFrom(Vector4 const&) const;
		/// return square value of the distance between 2 points
		float				distanceSquaredFrom(Vector4 const&) const;
		/// return the distance between 2 points on the X-Y axis only
		float				distance2DFrom(Vector4 const&) const;
		/// return the square value of the distance between 2 points points on the X-Y axis only
		float				distance2DSquaredFrom(Vector4 const&) const;
		/// return dot product result
		float				dot(Vector4 const&) const;
		/// return vector magnitude
		float				magnitude(void) const;
		/// return square value of the vector magnitude
		float				magnitudeSquared(void) const;

		/// return true if this vector magnitude is greater than the other
		bool				isLongerThan(Vector4 const&) const;
		/// return true if this vector magnitude is less than the other
		bool				isShorterThan(Vector4 const&) const;
		/// return true if this vector magnitude is 1
		bool				isUnitVector(void) const;

		/// return a copy of the cross product result
		Vector4				cross(Vector4 const&) const;
		/// scale this vector to have a magnitude of 1
		Vector4&			normalize(void);
		/// project this vector onto an other
		Vector4&			projectOnto(Vector4 const&);
		/// reflect this vector by an other
		Vector4&			reflectOnto(Vector4 const&);
		//Vector4&			rotate(Radian, Radian, Radian);					/// rotate this vector using euler angle apply in the z, x, y order
		//Vector4&			rotate(Radian, Vector4 const&);					/// rotate this vector around an arbitrary axis
		//Vector4&			rotate(Quaternion const&); todo quaternion		/// rotate this vector using a quaternion rotor
		/// scale this vector by a given factor
		Vector4&			scale(Vector4 const&);
		/// offset this vector by a given distance
		Vector4&			translate(Vector4 const&);

		/// return a string representation of this vector
		std::string			string(void) const;
		/// return a verbose string representation of this vector
		std::string			stringLong(void) const;
#pragma endregion

#pragma region In class operator

		///In class operator

		/// assignement operator
		Vector4&			operator=(Vector4 const&);

		/// return this vector component value
		float&				operator[](int);
		/// return this vector component value
		float				operator[](int) const;

		/// return the sum between this vectoor and a scalar
		Vector4				operator+(float);
		/// return the difference between this vector and a scalar
		Vector4				operator-(float);
		/// return the product between this vector and a scalar
		Vector4				operator*(float);
		/// return the quotient between this vector and a scalar
		Vector4				operator/(float);

		/// return the vector add to the scalar
		Vector4&			operator+=(float);
		/// return the vector substract by the scalar
		Vector4&			operator-=(float);
		/// return the vector multiply by the scalar
		Vector4&			operator*=(float);
		/// retuurn the vector divide by the scalar
		Vector4&			operator/=(float);

							/// return the vector 4 convert into vector 2
							operator Vector2(void) const;
							/// return the vector 4 convert into vector 3
							operator Vector3(void) const;
#pragma endregion

#pragma region Destructor

		///Destructor

							/// Default destructor
							~Vector4() = default;
#pragma endregion

		///Variables
		/// Put z before x and y because of glm initailize before them
		/// And it does an error while do the memcmp in Vector_UniTest
		//float m_z{ 0 };
		//float m_x{ 0 };
		//float m_y{ 0 };
		//float m_w{ 0 };
		float m_x{ 0 };
		float m_y{ 0 };
		float m_z{ 0 };
		float m_w{ 0 };

	}; // !Class Vector4

#pragma region Out class operator

	///Out class operator
	
	/// Vector4{ 1 } == Vector4::one()	// true					// return if 2 vectors have the same component
	bool					operator==(Vector4 const&, Vector4 const&);
	/// Vector4{ 1 } != Vector4::one()	// false				// return if 2 vectors differ by at least a component
	bool					operator!=(Vector4 const&, Vector4 const&);

	/// - Vector4{ .5, 1.5, -2.5 }		// { -.5, -1.5, 2.5 }	// return a copy of a vector with all its component inverted
	Vector4					operator-(Vector4 const&);

	/// Vector4{ .5, 1.5, -2.5 } + Vector4::one()	// { 1.5, 2.5, -1.5 }	// add 2 vectors component wise
	Vector4					operator+(Vector4 const&, Vector4 const&);
	/// Vector4{ .5, 1.5, -2.5 } - Vector4{ 1 }		// { -.5, .5, -3.5 }	// substract 2 vectors component wise
	Vector4					operator-(Vector4 const&, Vector4 const&);
	/// Vector4{ .5, 1.5, -2.5 } * Vector4::zero()	// { 0, 0, 0 }			// multiply 2 vectors component wise
	Vector4					operator*(Vector4 const&, Vector4 const&);
	/// Vector4{ .5, 1.5, -2.5 } / Vector4{ 2 }		// { .25, .75, -1.25 }	// divide 2 vectors component wise
	Vector4					operator/(Vector4 const&, Vector4 const&);

	/// addition component wise
	Vector4&				operator+=(Vector4&, Vector4 const&);
	/// substraction component wise
	Vector4&				operator-=(Vector4&, Vector4 const&);
	/// multiplication component wise
	Vector4&				operator*=(Vector4&, Vector4 const&);
	/// division component wise
	Vector4&				operator/=(Vector4&, Vector4 const&);

	/// cout << Vector4{ .5, 1.5, -2.5 }			// add a vector string representation to an output stream
	std::ostream&			operator<<(std::ostream&, Vector4 const&);
	/// ifstream file{ save.txt }; file >> vector;	// parse a string representation from an input stream into a vector
	std::istream&			operator>>(std::istream&, Vector4&);
#pragma endregion

} // !Namespace LibMath

#ifdef __LIBMATH__MATRIX__MATRIX4_H__
#endif // __LIBMATH__MATRIX__MATRIX4_H__

#endif // !__LIBMATH__VECTOR__VECTOR4_H__
