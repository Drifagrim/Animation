///Header
#include "Vector/Vector3.h"

namespace LibMath
{
#pragma region Constructor
	
	/// Constructor to set all components too the same value
	Vector3::Vector3(float value)
	{
		this->m_x = value;
		this->m_y = value;
		this->m_z = value;
	}
	/// Constructor to set all components individually
	Vector3::Vector3(float x, float y, float z)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
	}

#pragma endregion

#pragma region Set vector

	/// Function to set all components to zero
	Vector3				Vector3::zero(void)
	{
		return Vector3(0, 0, 0);
	}
	/// Function to set all components to one
	Vector3				Vector3::one(void)
	{
		return Vector3(1, 1, 1);
	}
	/// Function to set a vector pointing upward
	Vector3				Vector3::up(void)
	{
		return Vector3(0, 1, 0);
	}
	/// Function to set a vector pointing downward
	Vector3				Vector3::down(void)
	{
		return Vector3(0, -1, 0);
	}
	/// Function to set vector pointing left
	Vector3				Vector3::left(void)
	{
		return Vector3(-1, 0, 0);
	}
	/// Function to set vector pointind right
	Vector3				Vector3::right(void)
	{
		return Vector3(1, 0, 0);
	}
	/// Function to set vector pointing forward
	Vector3				Vector3::front(void)
	{
		return Vector3(0, 0, 1);
	}
	/// Function to set vector pointing backward
	Vector3				Vector3::back(void)
	{
		return Vector3(0, 0, -1);
	}

#pragma endregion

#pragma region Other functions

	/// Function to calcul the angle between two vector
	Radian				Vector3::angleFrom(Vector3 const& other) const
	{
		float dot = this->dot(other);
		float radian = std::acosf(dot / (this->magnitude() * other.magnitude()));

		return Radian(radian);
	}
	/// Function to calcul the distance between two vector
	float				Vector3::distanceFrom(Vector3 const& other) const
	{
		return float(std::sqrt(std::powf(other.m_x - this->m_x, 2) +
							   std::powf(other.m_y - this->m_y, 2) +
							   std::powf(other.m_z - this->m_z, 2)));
	}
	/// Function to calcul the square distance between two vector
	float				Vector3::distanceSquaredFrom(Vector3 const& other) const
	{
		return float(std::powf(other.m_x - this->m_x, 2) +
					 std::powf(other.m_y - this->m_y, 2) +
					 std::powf(other.m_z - this->m_z, 2));
	}
	/// Function to calcul the distance between two vector on the x and y axis
	float				Vector3::distance2DFrom(Vector3 const& other) const
	{
		return float(std::sqrt(std::powf(other.m_x - this->m_x, 2) +
							   std::powf(other.m_y - this->m_y, 2)));
	}
	/// Function to calcul the sqaure distance between two vector on the x and y axis
	float				Vector3::distance2DSquaredFrom(Vector3 const& other) const
	{
		return float(std::powf(other.m_x - this->m_x, 2) +
					 std::powf(other.m_y - this->m_y, 2));
	}
	/// Function to calcul the dot product between two vector
	float				Vector3::dot(Vector3 const& other) const
	{
		return float(this->m_x * other.m_x + 
					 this->m_y * other.m_y +
					 this->m_z * other.m_z);
	}
	/// Function to calcul the magnitude of this vector
	float				Vector3::magnitude(void) const
	{
		return float(std::sqrtf(std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2) +
			std::powf(this->m_z, 2)));
	}
	/// Functioon to calcul the sqaure magnituude of this vector
	float				Vector3::magnitudeSquared(void) const
	{
		return float(std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2) +
			std::powf(this->m_z, 2));
	}

	/// Check if the magnitude of this vector is greater than the other vector
	bool				Vector3::isLongerThan(Vector3 const& other) const
	{
		if (this->magnitude() > other.magnitude())
			return true;

		return false;
	}
	/// Check if the magnitude of this vector is shorter than the other vector
	bool				Vector3::isShorterThan(Vector3 const& other) const
	{
		if (this->magnitude() < other.magnitude())
			return true;

		return false;
	}
	/// Check if the vector is unit vector
	bool				Vector3::isUnitVector(void) const
	{
		if (this->magnitude() == 1)
			return true;

		return false;
	}
	/// Calcul the cross product between two vector
	Vector3				Vector3::cross(Vector3 const& other) const
	{
		float x = this->m_y * other.m_z - this->m_z * other.m_y;
		float y = this->m_z * other.m_x - this->m_x * other.m_z;
		float z = this->m_x * other.m_y - this->m_y * other.m_x;

		return Vector3(x, y, z);
	}
	/// Calcul the vector normalize
	Vector3&			Vector3::normalize(void)
	{
		this->operator/= (this->magnitude());

		return *this;
	}
	/// Calcul the projection of this vector on the other vector
	Vector3&			Vector3::projectOnto(Vector3 const& other)
	{
		float dot = this->dot(other);
		*this = other * Vector3(dot / other.magnitudeSquared());

		return *this;
	}
	/// Calcul the reeflection of this vector in regard to the other vector
	Vector3&			Vector3::reflectOnto(Vector3 const& other)
	{
		if (other.isUnitVector())
		{
			const float dot = this->dot(other);
			*this -= Vector3(2 * dot).scale(other);
		}

		else *this -= this->projectOnto(other).scale(Vector3(2));

		return *this;
	}
	/// Calcul the rotation of the vector
	Vector3&			Vector3::rotate(Radian z, Radian x, Radian y)
	{
		float x_vertex = this->m_x * std::cosf(z.radian(false)) - this->m_y * std::sinf(z.radian(false));
		float y_vertex = -this->m_x * std::sinf(z.radian(false)) + this->m_y * std::cosf(z.radian(false));

		this->m_x = x_vertex, this->m_y = y_vertex;

		y_vertex = this->m_y * std::cosf(x.radian(false)) - this->m_z * std::sinf(x.radian(false));
		float z_vertex = this->m_y * std::sinf(x.radian(false)) + this->m_z * std::cosf(x.radian(false));

		this->m_y = y_vertex, this->m_z = z_vertex;

		x_vertex = this->m_x * std::cosf(y.radian(false)) + this->m_z * std::sinf(y.radian(false));
		z_vertex = -this->m_x * -std::sinf(y.radian(false)) + this->m_z * std::cosf(y.radian(false));

		this->m_x = x_vertex, this->m_z = z_vertex;

		return *this;
	}
	/// Calcul the rotation of the vector around an axis given
	Vector3&			Vector3::rotate(Radian r, Vector3 const& other)
	{
		return this->rotate(other.m_z > 0.f ? r : Radian(0.f),
							other.m_x > 0.f ? r : Radian(0.f),
							other.m_y > 0.f ? r : Radian(0.f));
	}
	/// Scale the vector
	Vector3&			Vector3::scale(Vector3 const& other)
	{
		this->m_x *= other.m_x;
		this->m_y *= other.m_y;
		this->m_z *= other.m_z;

		return *this;
	}
	/// Translate the vector
	Vector3&			Vector3::translate(Vector3 const& other)
	{
		this->m_x += other.m_x;
		this->m_y += other.m_y;
		this->m_z += other.m_z;

		return *this;
	}
	/// Lerp position
	Vector3				Vector3::lerpPosition(Vector3 const& _start, Vector3 const& _end, float _t)
	{
		return (_end - _start) * _t + _start;
	}
	/// Lerp scale
	Vector3				Vector3::lerpScale(Vector3 const& _start, Vector3 const& _end, float _t)
	{
		return (_end - _start) * _t + _start;
	}
	/// Do the string representation of the vector
	std::string			Vector3::string() const
	{
		std::stringstream stream;
		stream << "{ " << this->m_x << ", " << this->m_y << ", " << this->m_z << " }";
		return stream.str().c_str();
	}
	/// Do the string long long representation of the vector
	std::string			Vector3::stringLong() const
	{
		std::stringstream stream;
		stream << "Vector3{ x: " << this->m_x << ", y: " << this->m_y << ", z: " << this->m_z << " }";
		return stream.str().c_str();
	}

#pragma endregion

#pragma region In class operator

	/// Assign the value of the other vector to this vector
	Vector3&			Vector3::operator=(Vector3 const& other)
	{
		this->m_x = other.m_x;
		this->m_y = other.m_y;
		this->m_z = other.m_z;

		return *this;
	}
	/// Assign an index to thee components of the vector
	float&				Vector3::operator[](int index)
	{
		switch (index)
		{
		case 0 :
			return this->m_x;
		case 1 :
			return this->m_y;
		case 2 :
			return this->m_z;
		default :
			throw std::logic_error("Index must be in range [0, 3[");
		}
	}
	/// Assign an index to the components of the vector
	float				Vector3::operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		default:
			throw std::logic_error("Index must be in range [0, 3[");
		}
	}
	/// Calcul the addition between this vector and a scalar
	Vector3				Vector3::operator+(float scalar)
	{
		return Vector3(this->m_x + scalar,
					   this->m_y + scalar,
					   this->m_z + scalar);
	}
	/// Calcul the substraction between this vector and a scalar
	Vector3				Vector3::operator-(float scalar)
	{
		return Vector3(this->m_x - scalar,
					   this->m_y - scalar,
					   this->m_z - scalar);
	}
	/// Calcul the multiplication between this vector and a scalar
	Vector3				Vector3::operator*(float scalar)
	{
		return Vector3(this->m_x * scalar,
					   this->m_y * scalar,
					   this->m_z * scalar);
	}
	/// Calcul the division between this vector and a scalar
	Vector3				Vector3::operator/(float scalar)
	{
		return Vector3(this->m_x / scalar,
					   this->m_y / scalar,
					   this->m_z / scalar);
	}
	/// Calcul the addition between this vector and a scalar
	Vector3&			Vector3::operator+=(float scalar)
	{
		this->m_x += scalar;
		this->m_y += scalar;
		this->m_z += scalar;

		return *this;
	}
	/// Calcul the substraction between this vector and a scalar
	Vector3&			Vector3::operator-=(float scalar)
	{
		this->m_x -= scalar;
		this->m_y -= scalar;
		this->m_z -= scalar;

		return *this;
	}
	/// Calcul the multiplication between this vector and a scalar
	Vector3&			Vector3::operator*=(float scalar)
	{
		this->m_x *= scalar;
		this->m_y *= scalar;
		this->m_z *= scalar;

		return *this;
	}
	/// Calcul the division between this vector and a scalar
	Vector3&			Vector3::operator/=(float scalar)
	{
		this->m_x /= scalar;
		this->m_y /= scalar;
		this->m_z /= scalar;

		return *this;
	}
	/// Convert vector 3 into vector 2
	Vector3::operator Vector2(void) const
	{
		return Vector2(this->m_x, this->m_y);
	}
	/// Convert vector 3 into vector 4
	Vector3::operator Vector4(void) const
	{
		return Vector4(this->m_x, this->m_y, this->m_z, 1.0f);
	}

#pragma endregion

#pragma region Out class operator

	/// Check the equality between left hand vector and right hand vector
	bool				operator==(Vector3 const& lhs, Vector3 const& rhs)
	{
		if (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_z)
			return true;

		return false;
	}
	/// Check the inequality between left hand vector and right hand vector
	bool				operator!=(Vector3 const& lhs, Vector3 const& rhs)
	{
		if (lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y || lhs.m_z != rhs.m_z)
			return true;

		return false;
	}
	/// Change the sign of the vector
	Vector3				operator-(Vector3 other)
	{
		return Vector3(-(other.m_x), -(other.m_y), -(other.m_z));
	}

	/// Calcul the addition between left hand vector and right hand vector
	Vector3				operator+(Vector3 const& lhs, Vector3 const& rhs)
	{
		return Vector3(lhs.m_x + rhs.m_x, 
					   lhs.m_y + rhs.m_y, 
					   lhs.m_z + rhs.m_z);
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector3				operator-(Vector3 const& lhs, Vector3 const& rhs)
	{
		return Vector3(lhs.m_x - rhs.m_x, 
					   lhs.m_y - rhs.m_y, 
					   lhs.m_z - rhs.m_z);
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector3				operator*(Vector3 const& lhs, Vector3 const& rhs)
	{
		return Vector3(lhs.m_x * rhs.m_x, 
					   lhs.m_y * rhs.m_y, 
					   lhs.m_z * rhs.m_z);
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector3				operator/(Vector3 const& lhs, Vector3 const& rhs)
	{
		return Vector3(lhs.m_x / rhs.m_x, 
					   lhs.m_y / rhs.m_y, 
					   lhs.m_z / rhs.m_z);
	}
	
	/// Calcul the addition between left hand vector and right hand vector
	Vector3&			operator+=(Vector3& lhs, Vector3 const& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;
		lhs.m_z += rhs.m_z;

		return lhs;
	}
	/// Calcul the substraction between left hand vector and right hand vector
	Vector3&			operator-=(Vector3& lhs, Vector3 const& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;
		lhs.m_z -= rhs.m_z;

		return lhs;
	}
	/// Calcul the multiplication between left hand vector and right hand vector
	Vector3&			operator*=(Vector3& lhs, Vector3 const& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;
		lhs.m_z *= rhs.m_z;

		return lhs;
	}
	/// Calcul the division between left hand vector and right hand vector
	Vector3&			operator/=(Vector3& lhs, Vector3 const& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;
		lhs.m_z /= rhs.m_z;

		return lhs;
	}
	/// Function to display the string representation of the vector on the console
	std::ostream&		operator<<(std::ostream& os, Vector3 const& other)
	{
		return os << other.string();
	}
	/// Function to parse and store into text file the string representation of the vector
	std::istream&		operator>>(std::istream& is, Vector3& other)
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