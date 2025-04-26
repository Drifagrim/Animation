/// Header
#include "Vector/Vector2.h"

namespace LibMath
{
#pragma region Constructor

	///Vector 2D constructor with one scalar
	Vector2::Vector2(float a)
	{
		this->m_x = a;
		this->m_y = a;
	}
	///Vector 2D constructor with two scalar
	Vector2::Vector2(float a, float b)
	{
		this->m_x = a;
		this->m_y = b;
	}

#pragma endregion

#pragma region Static

	/// Set all components to zero
	Vector2		Vector2::zero(void)
	{
		return Vector2(0.f);
	}
	/// Set all components to one
	Vector2		Vector2::one(void)
	{
		return Vector2(1.f);
	}
	/// Set components to vector pointing upward
	Vector2		Vector2::up(void)
	{
		return Vector2(0.f, 1.f);
	}
	/// Set components to vector pointing dowward
	Vector2		Vector2::down(void)
	{
		return Vector2(0.f, -1.f);
	}
	/// Set components to vector pointing left
	Vector2		Vector2::left(void)
	{
		return Vector2(-1.f, 0.f);
	}
	/// Set components to vector pointing right
	Vector2		Vector2::right(void)
	{
		return Vector2(1.f, 0.f);
	}

#pragma endregion

#pragma region Other functions

	/// Function to calcul the angle between two vector
	Radian Vector2::angleFrom(Vector3 const& other) const
	{
		float dot = this->dotProduct(other);
		float radian = std::acosf(dot / (this->magnitude() * other.magnitude()));

		return Radian(radian);
	}
	/// Calcul the cross product between two vector
	float			Vector2::crossProduct(const Vector2& other) const
	{
		return float(this->m_x * other.m_y - this->m_y * other.m_x);
	}
	/// Calcul the distance between two vector
	float			Vector2::distanceFrom(const Vector2& other) const
	{
		return float(std::sqrtf(std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2)));
	}
	/// Calcul the square distance between two vector
	float			Vector2::squaredDistanceFrom(const Vector2& other) const
	{
		return float(std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2));
	}
	/// Calcul the dot product between two vector
	float			Vector2::dotProduct(const Vector2& other) const
	{
		return float(this->m_x * other.m_x + this->m_y * other.m_y);
	}
	/// Calcul the magnitude of this vector
	float			Vector2::magnitude(void) const///Calcul the magnitude of a vector 2D
	{
		return float(std::sqrt(std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2)));
	}
	/// Calcul the square magnitude of this vector
	float			Vector2::squareMagnitude(void) const///Calcul the square magnitude of a vector 2D
	{
		return float(std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2));
	}
	///Check if the vector 2D is unitary or not
	bool			Vector2::isUnit(void) const 
	{
		float unitary = this->magnitude();

		if (unitary == 1)
		{
			return true;
		}

		return false;
	}
	/// Check if this vector is greater than the other vector
	bool			Vector2::isLongerThan(const Vector2& other) const
	{
		if (this->magnitude() > other.magnitude())
			return true;

		return false;
	}
	/// Check if this vector is longer than the other vector
	bool			Vector2::isShorterThan(const Vector2& other) const
	{
		if (this->magnitude() < other.magnitude())
			return true;

		return false;
	}
	/// Calcul the normalize vector
	Vector2&		Vector2::normalize(void)
	{
		this->operator/=(this->magnitude());

		return *this;
	}
	/// Calcul the projection of this vector on the other vector
	Vector2&		Vector2::project(const Vector2& other)
	{
		const float dot = this->dotProduct(other);
		*this = other * Vector2(dot / other.squareMagnitude());

		return *this;
	}
	/// Calcul the reflection of this vector in regard to the other vector
	Vector2&		Vector2::reflection(const Vector2& other)
	{
		if (other.isUnit())
		{
			float dot = this->dotProduct(other);
			*this -= Vector2(2 * dot).scale(other);
		}
		else
			*this -= this->project(other).scale(Vector2(2.0f));

		return *this;
	}
	/// Calcul the scale of this vector
	Vector2&		Vector2::scale(const Vector2& other)
	{
		*this *= other;

		return *this;
	}
	/// Calcul the translation of this vector
	Vector2&		Vector2::translate(const Vector2& other)
	{
		*this += other;

		return *this;
	}
	/// Do the string representation of the vector
	std::string		Vector2::string(void) const
	{
		std::stringstream stream;
		stream << "{ " << this->m_x << ", " << this->m_y << " }";
		return std::string(stream.str());
	}
	/// Do the string long long representation of the vector
	std::string		Vector2::stringLong(void) const
	{
		std::stringstream stream;
		stream << "Vector2{ x: " << this->m_x << ", y: " << this->m_y << " }";
		return std::string(stream.str());
	}

#pragma endregion

#pragma region In class operator
	
	/// Copy the other vector into this vector
	Vector2& Vector2::operator=(const Vector2& other)
	{
		this->m_x = other.m_x;
		this->m_y = other.m_y;

		return *this;
	}
	/// Assign to the components an index
	float&			Vector2::operator[](int index)
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		default:
			throw std::logic_error("Index must be in range [0, 2[");
		}
	}
	/// Assign to the components an index
	float			Vector2::operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		default:
			throw std::logic_error("Index must be in range [0, 2[");
		}
	}
	/// Calcul the addition between this vector and a scalar
	Vector2			Vector2::operator+(float scalar)
	{
		return Vector2(this->m_x + scalar, this->m_y + scalar);
	}
	/// Calcul the substraction between this vector and a scalar
	Vector2			Vector2::operator-(float scalar)
	{
		return Vector2(this->m_x - scalar, this->m_y - scalar);
	}
	/// Calcul the multiplication between this vector and a scalar
	Vector2			Vector2::operator*(float scalar)
	{
		return Vector2(this->m_x * scalar, this->m_y * scalar);
	}
	/// Calcul the division between this vector and a scalar
	Vector2			Vector2::operator/(float scalar)
	{
		return Vector2(this->m_x / scalar, this->m_y / scalar);
	}

	/// Calcul the addition between this vector and a scalar
	Vector2&		Vector2::operator+=(float scalar)
	{
		this->m_x += scalar;
		this->m_y += scalar;

		return *this;
	}
	/// Calcul the substraction between this vector and a scalar
	Vector2&		Vector2::operator-=(float scalar)
	{
		this->m_x -= scalar;
		this->m_y -= scalar;

		return *this;
	}
	/// Calcul the multiplication of this vector with a scalar
	Vector2&		Vector2::operator*=(float scalar)
	{
		this->m_x *= scalar;
		this->m_y *= scalar;

		return *this;
	}
	/// Calcul the division of this vector with a scalar
	Vector2&		Vector2::operator/=(float scalar)
	{
		this->m_x /= scalar;
		this->m_y /= scalar;

		return *this;
	}
	/// Convert this vector 2 into vector 3
	Vector2::operator Vector3(void) const
	{
		return Vector3(this->m_x, this->m_y, 1.0f);
	}
	/// Convert this vector 2 into vector 4
	Vector2::operator Vector4(void) const
	{
		return Vector4(this->m_x, this->m_y, 1.0f, 1.0f);
	}

#pragma endregion

#pragma region Out class operator
	
	/// Check the equality between left hand vector and right hand vector
	bool			operator==(const Vector2& lhs, const Vector2& rhs)
	{
		if (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y)
			return true;

		return false;
	}
	/// Check the inequality between left hand vector and right hand vector
	bool			operator!=(const Vector2& lhs, const Vector2 rhs)
	{
		if (lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y)
			return true;

		return false;
	}
	/// Change the vector sign
	Vector2			operator-(Vector2 other)
	{
		return Vector2(-other.m_x, -other.m_y);
	}

	/// Calcul the addition between left hand vector and right hand vector
	Vector2			operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y);
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector2			operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector2			operator*(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y);
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector2			operator/(const Vector2 lhs, const Vector2& rhs)
	{
		return Vector2(lhs.m_x / rhs.m_x, lhs.m_y / rhs.m_y);
	}
	/// Calcul the addition between left hand vector and right hand vector
	Vector2&		operator+=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;

		return lhs;
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector2&		operator-=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;

		return lhs;
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector2&		operator*=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;

		return lhs;
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector2&		operator/=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;

		return lhs;
	}
	/// Display the string representation of the vector on the console
	std::ostream&	operator<<(std::ostream& os, const Vector2& other)
	{
		return os << other.string();
	}
	/// Parse and store the string representation of the vector into a text file
	std::istream&	operator>>(std::istream& is, Vector2& other)
	{
		std::string str;

		char c;
		while (is.get(c))
		{
			str += c;
			if (c == '}') break;
		}

		std::string token;
		size_t pos = 0;

		str.erase(0, str.find("{") + 1);
		str.erase(str.find("}"), str.length());
		str += ',';

		int index = 0;
		while ((pos = str.find(",")) != std::string::npos)
		{
			token = str.substr(0, pos);
			float component = std::stof(token);
			other[index++] = component;
			str.erase(0, pos + 1);
		}
		return is;
	}

#pragma endregion

} // !Namespace LibMath
