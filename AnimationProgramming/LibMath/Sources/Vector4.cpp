///Header
#include "Vector/Vector4.h"

namespace LibMath
{

#pragma region Constructor

	/// Constructor to set all component to the same value
	Vector4::Vector4(float value)
	{
		this->m_x = value;
		this->m_y = value;
		this->m_z = value;
		this->m_w = value;
	}
	/// Constructor to set all component individually
	Vector4::Vector4(float x, float y, float z, float w)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
		this->m_w = w;
	}

#pragma endregion

#pragma region Set vector

	/// Function to set all vector components to 0
	Vector4			Vector4::zero(void)
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	/// Function to set all vector components to 1
	Vector4			Vector4::one(void)
	{
		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

#pragma endregion

#pragma region Other functions

	/// Function to calcul the angle between two vectors
	Radian			Vector4::angleFrom(Vector4 const& other) const
	{
		float dot = this->dot(other);
		float radian = std::acosf(dot / (this->magnitude() * other.magnitude()));

		return Radian(radian);
	}
	/// Function to calcul the distance between two points
	float			Vector4::distanceFrom(Vector4 const& other) const
	{
		return float(std::sqrtf(std::powf(other.m_x - this->m_x, 2) +
								std::powf(other.m_y - this->m_y, 2) +
								std::powf(other.m_z - this->m_z, 2) +
								std::powf(other.m_w - this->m_w, 2)));
	}
	/// Function to return the square of the distance between two points
	float			Vector4::distanceSquaredFrom(Vector4 const& other) const
	{
		return float(std::powf(other.m_x - this->m_x, 2) +
					 std::powf(other.m_y - this->m_y, 2) +
					 std::powf(other.m_z - this->m_z, 2) +
					 std::powf(other.m_w - this->m_w, 2));
	}
	/// Function to calcul the distance between 2 points on the x and y axis
	float			Vector4::distance2DFrom(Vector4 const& other) const
	{
		return float(std::sqrt(std::powf(other.m_x - this->m_x, 2) +
							   std::powf(other.m_y - this->m_y, 2)));
	}
	/// Function to calcul the square of the distance between two points on the x and y axis
	float			Vector4::distance2DSquaredFrom(Vector4 const& other) const
	{
		return float(std::powf(other.m_x - this->m_x, 2) +
					 std::powf(other.m_y - this->m_y, 2));
	}
	/// Calcul the dot product between two vector
	float			Vector4::dot(Vector4 const& other) const
	{
		return float(this->m_x * other.m_x +
					 this->m_y * other.m_y +
					 this->m_z * other.m_z +
					 this->m_w * other.m_w);
	}
	/// Function to determine if this vector magnitude is greater than the other vector
	bool			Vector4::isLongerThan(Vector4 const& other) const
	{
		if (this->magnitude() > other.magnitude())
			return true;

		return false;
	}
	/// Function to determine if this vector magnitude is shorter than the other vector
	bool			Vector4::isShorterThan(Vector4 const& other) const
	{
		if (this->magnitude() < other.magnitude())
			return true;

		return false;
	}
	/// Function to determine if the vector is a unit vector
	bool			Vector4::isUnitVector(void) const
	{
		if (this->magnitude() == 1)
			return true;

		return false;
	}

	/// Calcul the magnitude of a vector
	float			Vector4::magnitude(void) const
	{
		return float(std::sqrtf(std::powf(this->m_x, 2) +
								std::powf(this->m_y, 2) +
								std::powf(this->m_z, 2) +
								std::powf(this->m_w, 2)));
	}
	/// Calcul the squared magnitude of a vector
	float			Vector4::magnitudeSquared(void) const
	{
		return float(std::powf(this->m_x, 2) +
					 std::powf(this->m_y, 2) +
					 std::powf(this->m_z, 2) +
					 std::powf(this->m_w, 2));
	}
	/// Normalize the vector
	Vector4&		Vector4::normalize(void)
	{
		this->m_x /= (this->magnitude());
		this->m_y /= (this->magnitude());
		this->m_z /= (this->magnitude());
		this->m_w /= (this->magnitude());

		return *this;
	}
	/// Function to project this vector on another one
	Vector4&		Vector4::projectOnto(Vector4 const& other)
	{
		float dot = this->dot(other);
		*this = other * Vector4(dot / other.magnitudeSquared());

		return *this;
	}
	/// Function to reflect this vector with another
	Vector4&		Vector4::reflectOnto(Vector4 const& other)
	{
		if (other.isUnitVector())
		{
			const float dot = this->dot(other);
			*this -= Vector4(2 * dot).scale(other);
		}

		else *this -= this->projectOnto(other).scale(Vector4(2.f));

		return *this;
	}
	/// Function to scale this vector
	Vector4&		Vector4::scale(Vector4 const& other)
	{
		this->m_x *= other.m_x;
		this->m_y *= other.m_y;
		this->m_z *= other.m_z;
		this->m_w *= other.m_w;

		return *this;
	}
	/// Function to translate this vector
	Vector4&		Vector4::translate(Vector4 const& other)
	{
		this->m_x += other.m_x;
		this->m_y += other.m_y;
		this->m_z += other.m_z;
		this->m_w += other.m_w;

		return *this;
	}
	/// Function to represent the vector to string
	std::string		Vector4::string() const
	{
		std::stringstream stream;
		stream << "{ " << this->m_x << ", " << this->m_y << ", " << this->m_z << ", " << this->m_w << " }";

		return std::string(stream.str());
	}
	/// Function to represent the vector to long long string
	std::string		Vector4::stringLong(void) const
	{
		std::stringstream stream;
		stream << "Vector4{ x: " << this->m_x << ", y: " << this->m_y << ", z: " << this->m_z << ", w: " << this->m_w << " }";
		return std::string(stream.str());
	}

#pragma endregion

#pragma region In class operator

	/// Assignement operator to assign components of another vector to this vector
	Vector4&		Vector4::operator=(Vector4 const& other)
	{
		this->m_x = other.m_x;
		this->m_y = other.m_y;
		this->m_z = other.m_z;
		this->m_w = other.m_w;

		return *this;
	}
	/// Function to assign a component of a vector to an index
	float&			Vector4::operator[](int index)
	{
		switch (index)
		{
		case 0 :
			return this->m_x;
		case 1 :
			return this->m_y;
		case 2 :
			return this->m_z;
		case 3 :
			return this->m_w;
		default :
			throw std::logic_error("Index must be in range [0, 4[");
		}
	}
	/// Const function to assigne a component of a vector to an index 
	float			Vector4::operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		case 3:
			return this->m_w;
		default:
			throw std::logic_error("Index must be in range [0, 4[");
		}
	}
	/// Calcul the addition between this vector and a scalar
	Vector4			Vector4::operator+(float scalar)
	{
		return Vector4(this->m_x + scalar,
					   this->m_y + scalar,
					   this->m_z + scalar,
					   this->m_w + scalar);
	}
	/// Calcul the substraction between this vector and a scalar
	Vector4			Vector4::operator-(float scalar)
	{
		return Vector4(this->m_x - scalar,
					   this->m_y - scalar,
					   this->m_z - scalar,
					   this->m_w - scalar);
	}
	/// Calcul the multiplication between this vector and a scalar
	Vector4			Vector4::operator*(float scalar)
	{
		return Vector4(this->m_x * scalar,
					   this->m_y * scalar,
					   this->m_z * scalar,
					   this->m_w * scalar);
	}
	/// Calcul the division between this vector and a scalar
	Vector4			Vector4::operator/(float scalar)
	{
		return Vector4(this->m_x / scalar,
					   this->m_y / scalar,
					   this->m_z / scalar,
					   this->m_w / scalar);
	}
	/// Calcul the addition between this vector and a scalar
	Vector4&		Vector4::operator+=(float scalar)
	{
		this->m_x += scalar;
		this->m_y += scalar;
		this->m_z += scalar;
		this->m_w += scalar;

		return *this;
	}
	/// Calcul the substraction between this vector and a scalar
	Vector4&		Vector4::operator-=(float scalar)
	{
		this->m_x -= scalar;
		this->m_y -= scalar;
		this->m_z -= scalar;
		this->m_w -= scalar;

		return *this;
	}
	/// Calcul the multiplication between this vector and a scalar
	Vector4&		Vector4::operator*=(float scalar)
	{
		this->m_x *= scalar;
		this->m_y *= scalar;
		this->m_z *= scalar;
		this->m_w *= scalar;

		return *this;
	}
	/// Calcul the division between this vector and a scalar
	Vector4&		Vector4::operator/=(float scalar)
	{
		this->m_x /= scalar;
		this->m_y /= scalar;
		this->m_z /= scalar;
		this->m_w /= scalar;

		return *this;
	}
	/// Convert the vector 4 into a vector 2
	Vector4::operator Vector2(void) const
	{
		return Vector2(this->m_x, this->m_y);
	}
	/// Convert the vector 4 into a vector 3
	Vector4::operator Vector3(void) const
	{
		return Vector3(this->m_x, this->m_y, this->m_z);
	}

#pragma endregion

#pragma region Out class operator

	/// Check the equality between left hand vector and right hand vector
	bool			operator==(Vector4 const& lhs, Vector4 const& rhs)
	{
		if (lhs.m_x == rhs.m_x &&
			lhs.m_y == rhs.m_y &&
			lhs.m_z == rhs.m_z &&
			lhs.m_w == rhs.m_w)
			return true;

		return false;
	}
	/// Check the inequality between left hand vector and right hand vector
	bool			operator!=(Vector4 const& lhs, Vector4 const& rhs)
	{
		if (lhs.m_x != rhs.m_x ||
			lhs.m_y != rhs.m_y ||
			lhs.m_z != rhs.m_z ||
			lhs.m_w != rhs.m_w)
			return true;

		return false;
	}
	/// Change the sign of the vector
	Vector4			operator-(Vector4 const& other)
	{
		return Vector4(-(other.m_x), -(other.m_y), -(other.m_z), -(other.m_w));
	}
	/// Calcul the addition between left hand vector and right hand vector
	Vector4			operator+(Vector4 const& lhs, Vector4 const& rhs)
	{
		float x = lhs.m_x + rhs.m_x;
		float y = lhs.m_y + rhs.m_y;
		float z = lhs.m_z + rhs.m_z;
		float w = lhs.m_w + rhs.m_w;

		return Vector4(x, y, z, w);
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector4			operator-(Vector4 const& lhs, Vector4 const& rhs)
	{
		float x = lhs.m_x - rhs.m_x;
		float y = lhs.m_y - rhs.m_y;
		float z = lhs.m_z - rhs.m_z;
		float w = lhs.m_w - rhs.m_w;

		return Vector4(x, y, z, w);
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector4			operator*(Vector4 const& lhs, Vector4 const& rhs)
	{
		float x = lhs.m_x * rhs.m_x;
		float y = lhs.m_y * rhs.m_y;
		float z = lhs.m_z * rhs.m_z;
		float w = lhs.m_w * rhs.m_w;

		return Vector4(x, y, z, w);
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector4			operator/(Vector4 const& lhs, Vector4 const& rhs)
	{
		float x = lhs.m_x / rhs.m_x;
		float y = lhs.m_y / rhs.m_y;
		float z = lhs.m_z / rhs.m_z;
		float w = lhs.m_w / rhs.m_w;

		return Vector4(x, y, z, w);
	}
	/// Calcul the addition between left hand vector and right hand vector
	Vector4&		operator+=(Vector4& lhs, Vector4 const& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;
		lhs.m_z += rhs.m_z;
		lhs.m_w += rhs.m_w;

		return lhs;
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector4&		operator-=(Vector4& lhs, Vector4 const& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;
		lhs.m_z -= rhs.m_z;
		lhs.m_w -= rhs.m_w;

		return lhs;
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector4&		operator*=(Vector4& lhs, Vector4 const& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;
		lhs.m_z *= rhs.m_z;
		lhs.m_w *= rhs.m_w;

		return lhs;
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector4&		operator/=(Vector4& lhs, Vector4 const& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;
		lhs.m_z /= rhs.m_z;
		lhs.m_w /= rhs.m_w;

		return lhs;
	}
	/// Function to display the vector on the console
	std::ostream&	operator<<(std::ostream& os, Vector4 const& other)
	{
		return os << other.string();
	}
	/// Function to parse and store the string representation of the vector
	std::istream&	operator>>(std::istream& is, Vector4& other)
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