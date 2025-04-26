#pragma once

#pragma region LibMath

#include "LibMath/Header/Vector/Vector3.h"
#include "LibMath/Header/Quaternion.h"

#pragma endregion

/// Basic struct of a transform without scale (considered as 1)
struct Transform
{
	LibMath::Vector3	m_position;
	LibMath::Quaternion m_rotation;
	LibMath::Vector3    m_scale;

	/// Constructor
	// Set all value to zero except the w of the quaternion
						Transform();

	Transform&			operator=(Transform const& _rhs);

};

/// Operators
// Negate operator
Transform				operator-(Transform const& _other);
// Multiplication operator considered as combine two transforms
Transform				operator*(Transform const& _lhs, Transform const& _rhs);


/// Conversion
// Convert a vector 3 position to matrix4
LibMath::Matrix4		positionToMatrix4(LibMath::Vector3 const& _position);
// Convert a vector 3 scale to matrix4
LibMath::Matrix4		scaleToMatrix4(LibMath::Vector3 const& _scale);
// Convert a transform to a matrix4
LibMath::Matrix4		transformToMatrix4(Transform const& _transform);

/// Interpolation
// Interpolate between two transforms
Transform				interpolate(Transform const& _a, Transform const& _b, float _t);