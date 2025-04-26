#include "Transform.h"

#pragma region LibMath

#include "LibMath/Header/Matrix/Matrix4.h"
#include "LibMath/Header/Arithmetic.h"

#pragma endregion

/// Set all value to zero except the w of the quaternion
Transform::Transform()
{
	m_position = LibMath::Vector3(0.f, 0.f, 0.f);
	m_rotation = LibMath::Quaternion(1.f, 0.f, 0.f, 0.f);
}

Transform& Transform::operator=(Transform const& _rhs)
{
	m_position	= _rhs.m_position;
	m_rotation	= _rhs.m_rotation;
	m_scale		= _rhs.m_scale;

	return *this;
}

/// Negate operator
Transform operator-(Transform const& _other)
{
	Transform result;
	result.m_rotation = LibMath::conjugate(_other.m_rotation);
	result.m_position = _other.m_position * result.m_rotation;
	result.m_position = -result.m_position;

	return result;
}

/// Multiplication operator considered as combine two transforms
Transform operator*(Transform const& _lhs, Transform const& _rhs)
{
	Transform result;

	result.m_position	= (_lhs.m_position * _rhs.m_rotation) * _rhs.m_scale + _rhs.m_position;
	result.m_rotation	= _rhs.m_rotation * _lhs.m_rotation;
	result.m_scale		= _lhs.m_scale * _rhs.m_scale;

	return result;
}

/// Convert a vector 3 position to matrix4
LibMath::Matrix4 positionToMatrix4(LibMath::Vector3 const& _position)
{
	LibMath::Matrix4 resultPosition = LibMath::Matrix4::Identity();

	resultPosition = LibMath::Matrix4::Translate(_position, false);

	return resultPosition;
}

/// Convert a vector 3 scale to matrix4
LibMath::Matrix4 scaleToMatrix4(LibMath::Vector3 const& _scale)
{
	LibMath::Matrix4 resultScale = LibMath::Matrix4::Identity();

	resultScale = LibMath::Matrix4::Scale(_scale);

	return resultScale;
}

/// Convert a transform to a matrix4
LibMath::Matrix4 transformToMatrix4(Transform const& _transform)
{
	LibMath::Matrix4 scaleMatrix = scaleToMatrix4(_transform.m_scale);

	LibMath::Matrix4 rotationMatrix = LibMath::toMatrix4(_transform.m_rotation);

	LibMath::Matrix4 translationMatrix = positionToMatrix4(_transform.m_position);

	LibMath::Matrix4 transformMatrix = (scaleMatrix * rotationMatrix) * translationMatrix;

	return transformMatrix;
}

/// Interpolate between two transforms
Transform interpolate(Transform const& _a, Transform const& _b, float _t)
{
	Transform result;

	result.m_position	= LibMath::Vector3::lerpPosition(_a.m_position, _b.m_position, _t);
	result.m_rotation	= LibMath::slerp(_a.m_rotation, _b.m_rotation, _t);
	result.m_scale		= LibMath::Vector3::lerpScale(_a.m_scale, _b.m_scale, _t);

	return result;
}