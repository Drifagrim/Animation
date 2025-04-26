#pragma region Simulation

#include "MySimulation.h"
#include "Engine.h"

#pragma endregion

#pragma region Standard

#include <stdio.h>
#include <cassert>

#pragma endregion

/// Initialize members
void				MySimulation::initMembers()
{
	/*Get the number of bones*/
	getBoneCount();

	/*Resize the bone array*/
	m_walkAnimation.m_skeletonAnim.resize(m_boneCount);
	m_runAnimation.m_skeletonAnim.resize(m_boneCount);

	/*Get the animation key count*/
	m_walkAnimation.m_frameCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	m_runAnimation.m_frameCount = GetAnimKeyCount("ThirdPersonRun.anim");

	m_walkAnimation.m_isActivated = true;

	m_currentAnimation = &m_walkAnimation;
	m_nextAnimation = &m_runAnimation;
}

/// Initialize the scale to {1.f, 1.f, 1.f}
void				MySimulation::initScale(std::vector<Bone>& _skeleton, int _animKeyCount)
{
	for (int index = 0; index < m_boneCount; ++index)
	{
		_skeleton[index].m_localTransform.m_scale = { 1.f, 1.f, 1.f };
		_skeleton[index].m_worldTransform.m_scale = { 1.f, 1.f, 1.f };

		for (int j = 0; j < _animKeyCount; ++j)
		{
			_skeleton[index].m_localTransforms[j].m_scale = { 1.f, 1.f, 1.f };
			_skeleton[index].m_worldTransforms[j].m_scale = { 1.f, 1.f, 1.f };
		}
	}
}

/// Initialize the simulation
void				MySimulation::init()
{
	printBoneHierarchy();

	initMembers();

	printBoneHierarchyWithoutIK();

	getBoneInformations(m_walkAnimation.m_skeletonAnim);
	getBoneInformations(m_runAnimation.m_skeletonAnim);

	getAnimationInformations("ThirdPersonWalk.anim", m_walkAnimation.m_skeletonAnim, m_walkAnimation.m_frameCount);
	getAnimationInformations("ThirdPersonRun.anim", m_runAnimation.m_skeletonAnim, m_runAnimation.m_frameCount);

	initScale(m_walkAnimation.m_skeletonAnim, m_walkAnimation.m_frameCount);
	initScale(m_runAnimation.m_skeletonAnim, m_runAnimation.m_frameCount);
}

/// Print the bone hierarchy
void				MySimulation::printBoneHierarchy()
{
	/*Print the bone hierarchy*/
	for (int i = 0; i < GetSkeletonBoneCount(); ++i)
	{
		const char* boneName = GetSkeletonBoneName(i);

		int parentIndex = GetSkeletonBoneParentIndex(i);

		while (parentIndex != -1)
		{
			std::cout << "  ";
			parentIndex = GetSkeletonBoneParentIndex(parentIndex);
		}

		std::cout << boneName << std::endl;
	}
}

/// Get the number of bones without the IK bones
void				MySimulation::printBoneHierarchyWithoutIK()
{
	/*Print the bone hierarchy*/
	for (int i = 0; i < m_boneCount; ++i)
	{
		const char* boneName = GetSkeletonBoneName(i);

		int parentIndex = GetSkeletonBoneParentIndex(i);

		while (parentIndex != -1)
		{
			std::cout << "  ";
			parentIndex = GetSkeletonBoneParentIndex(parentIndex);
		}

		std::cout << boneName << std::endl;
	}
}

/// Get the number of bones without the IK bones
void				MySimulation::getBoneCount()
{
	for (int index = 0; index < GetSkeletonBoneCount(); ++index)
	{
		if (memcmp(GetSkeletonBoneName(index), "ik_", 3) != 0)
		{
			++m_boneCount;
		}
	}
}

/// Get the bone information
void				MySimulation::getBoneInformations(std::vector<Bone>& _skeleton)
{
	for (int i = 0; i < m_boneCount; ++i)
	{
		/*Get the bone local transform*/
		getSkeletonBoneLocalBindTransform(i, _skeleton[i].m_localTransform.m_position,
										  _skeleton[i].m_localTransform.m_rotation);

		/*Get bone parent index*/
		_skeleton[i].m_parentIndex = GetSkeletonBoneParentIndex(i);

		/*Make sure the parent index is valid*/
		assert(_skeleton[i].m_parentIndex < i);
	}
}

/// Get skeleton bone local bind transform
void				MySimulation::getSkeletonBoneLocalBindTransform(int _boneIndex, LibMath::Vector3& _position, 
																	LibMath::Quaternion& _rotation)
{
	GetSkeletonBoneLocalBindTransform(_boneIndex, _position.m_x, _position.m_y, _position.m_z,
									  _rotation.m_a, _rotation.m_b, _rotation.m_c, _rotation.m_d);
}

/// Get animation informations
void				MySimulation::getAnimationInformations(const char* _animName, std::vector<Bone>& _skeleton, 
														   size_t _animKeyCount)
{
	for (int i = 0; i < m_boneCount; ++i)
	{
		_skeleton[i].m_localTransforms.resize(_animKeyCount);
		_skeleton[i].m_worldTransforms.resize(_animKeyCount);

		for (int j = 0; j < _animKeyCount; ++j)
		{
			getAnimLocalBoneTransform(_animName, i, j, _skeleton[i].m_localTransforms[j].m_position,
				_skeleton[i].m_localTransforms[j].m_rotation);
		}
		/*Get bone parent index*/
		_skeleton[i].m_parentIndex = GetSkeletonBoneParentIndex(i);

		/*Make sure the parent index is valid*/
		assert(_skeleton[i].m_parentIndex < i);
	}
}

/// Get the walk animation local bone transformationn
void				MySimulation::getAnimLocalBoneTransform(const char* _animeName, int _boneIndex, int _frameIndex,
															LibMath::Vector3& _position, LibMath::Quaternion& _rotation)
{
	GetAnimLocalBoneTransform(_animeName, _boneIndex, _frameIndex, 
							  _position.m_x, _position.m_y, _position.m_z,
							  _rotation.m_a, _rotation.m_b, _rotation.m_c, _rotation.m_d);
}

/// Get the next frame transform
void				MySimulation::getTheNextFrameTransform(std::vector<Bone>& _skeleton, size_t _animKeyCount)
{
	for (int i = 0; i < m_boneCount; ++i)
	{
		int ancestorIndex = _skeleton[i].m_parentIndex;

		int nextFrame = (m_currentFrame + 1) % _animKeyCount;

		if (nextFrame >= _animKeyCount)
		{
			nextFrame = 0;
		}

		/*Update with anim by combining the local transform at the current frame with the local transform*/
		_skeleton[i].m_worldTransforms[nextFrame] = _skeleton[i].m_localTransforms[nextFrame] *
													_skeleton[i].m_localTransform;

		if (ancestorIndex != -1)
		{
			/*update the world transform by combining the world transform at the current frame with the world transform*/
			_skeleton[i].m_worldTransforms[nextFrame] = _skeleton[i].m_worldTransforms[nextFrame] *
														_skeleton[ancestorIndex].m_worldTransforms[nextFrame];
		}
	}
}

/// Get animation duration
float				MySimulation::getAnimationDuration(size_t _animKeyCount, float _frameTime)
{
	return _animKeyCount * _frameTime;
}

Transform			MySimulation::GetThefinalTransform(float& _frameTime)
{
	if (m_transitionProgress < 1.f)
	{
		m_transitionProgress += _frameTime / m_transitionTime;
	}
	if (m_transitionProgress > 1.f)
	{
		m_transitionProgress = 1.f;
	}

	float walkSpeed = 30.f / m_currentAnimation->m_frameCount;
	float runSpeed = 30.f / m_nextAnimation->m_frameCount;

	float interpolatedSpeed = walkSpeed + (runSpeed - walkSpeed) * m_transitionProgress;

	float currentFrameTime = _frameTime * interpolatedSpeed;

	Transform walkTransform = interpolateAnimation(m_currentAnimation, currentFrameTime);
	Transform runTransform = interpolateAnimation(m_nextAnimation, currentFrameTime);

	Transform finalTransform = interpolate(walkTransform, runTransform, m_transitionProgress);

	return finalTransform;
}

/// Update the simulation
void				MySimulation::update(float frameTime)
{
	///*Limit the frame time*/
	//if (frameTime > 0.1f)
	//{
	//	frameTime = 1.0f / 60.0f;
	//}
	////frameTime /= 10.0f;

	///*Draw world axis*/
	//drawWorldMarker();

	///*Process steps*/
	////step1(frameTime);
	////step2(frameTime);
	////step3(frameTime);
	step4(frameTime);
}

/// Draw axis of the world
void				MySimulation::drawWorldMarker()
{
	/*X axis*/
	DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

	/*Y axis*/
	DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

	/*Z axis*/
	DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
}

/// Draw skeleton
void				MySimulation::drawSkeleton(LibMath::Vector3& _childPosition, LibMath::Vector3& _parentPosition,
											   float _offset, LibMath::Vector3 _color)
{
	DrawLine(_childPosition.m_x, _childPosition.m_y - _offset, _childPosition.m_z, 
			 _parentPosition.m_x, _parentPosition.m_y - _offset, _parentPosition.m_z, 
			 _color.m_x, _color.m_y, _color.m_z);
}

/// Frame counter to update animation in regard to the frameTime
void				MySimulation::frameCounter(float _frameTime, size_t _animKeyCount)
{
	/*Update the accumulated time*/
	m_accumulatedTime += _frameTime;

	/*Duration of a frame in seconds*/
	float frameDuration = 1.f / 30.f;

	/*If the accumulated time is greater than the frame duration we go to the next frame*/
	while (m_accumulatedTime >= frameDuration)
	{
		/*Increment the current frame*/
		m_currentFrame++;

		if (m_currentFrame >= _animKeyCount)
		{
			/*Loop the animation if the current frame is greater than the animation key count*/
			m_currentFrame = 0;
		}

		/*Reduce the accumulated time by the frame duration*/
		m_accumulatedTime -= frameDuration;
	}

	m_currentPartialFrame = m_accumulatedTime / frameDuration;
}

/// Interpolate between current frame and next frame
Transform			MySimulation::interpolateBetweenFrames(int& _index, std::vector<Bone>& _skeleton, int& _frame, 
														   size_t& _animKeyCount)
{
	Transform result;

	if (m_currentFrame + 1 < _animKeyCount)
	{
		result = interpolate(_skeleton[_index].m_worldTransforms[_frame],
							 _skeleton[_index].m_worldTransforms[_frame + 1], m_currentPartialFrame);
	}
	else
	{
		result = interpolate(_skeleton[_index].m_worldTransforms[_frame],
							 _skeleton[_index].m_worldTransforms[0], m_currentPartialFrame);
	}

	return result;
}

Transform MySimulation::interpolateAnimation(Animation* _anim, float _frameTime)
{
	int frameIndex = static_cast<int>(_frameTime) % _anim->m_frameCount;

	return _anim->m_skeletonAnim[frameIndex].m_localTransform;
}

void				MySimulation::bindSkeletonToAnimation(std::vector<Bone>& _skeleton)
{
	for (int i = 0; i < m_boneCount; ++i)
	{
		int ancestorIndex = _skeleton[i].m_parentIndex;

		if (i == 0)
		{
			/*Init root bind position/rotation*/
			_skeleton[0].m_worldTransform = _skeleton[0].m_localTransform;
		}

		else
		{
			/*Update with anim by combining the local transform at the current frame with the local transform*/
			_skeleton[i].m_worldTransforms[m_currentFrame] = _skeleton[i].m_localTransforms[m_currentFrame] *
															 _skeleton[i].m_localTransform;

			/*update the world transform by combining the world transform at the current frame with the world transform*/
			_skeleton[i].m_worldTransforms[m_currentFrame] = _skeleton[i].m_worldTransforms[m_currentFrame] *
															 _skeleton[ancestorIndex].m_worldTransforms[m_currentFrame];
		}
	}
}

void				MySimulation::animateTheMesh(std::vector<Bone>& _skeleton, std::vector<LibMath::Matrix4>& _skinningMatrix,
												 LibMath::Matrix4& _boneMatrix, int _index, int _ancestorIndex)
{
	if (_ancestorIndex != -1)
	{
		_skeleton[_index].m_worldTransform = _skeleton[_index].m_localTransform * _skeleton[_ancestorIndex].m_worldTransform;
	}

	/*Get the inverse of the local transform to place in bone space*/
	LibMath::Matrix4 localMatrixInverse = transformToMatrix4(_skeleton[_index].m_worldTransform).GetInverse();

	/**/
	LibMath::Matrix4 skinningMatrix = localMatrixInverse * _boneMatrix;

	_skinningMatrix.push_back(skinningMatrix);
}

LibMath::Matrix4	MySimulation::createInterpolatedMatrix(int _index, std::vector<Bone>& _skeleton, int _frame, 
														   size_t _animKeyCount)
{
	Transform interpolatedWorldTransforms = interpolateBetweenFrames(_index, _skeleton, _frame, _animKeyCount);

	/*Convert the bone transform to a matrix*/
	LibMath::Matrix4 boneMatrix = transformToMatrix4(interpolatedWorldTransforms);

	return boneMatrix;
}

void				MySimulation::playAnimation(std::vector<Bone>& _skeleton, size_t& _animKeyCount, int& _currentFrame, 
												float& _frameTime)
{
	frameCounter(_frameTime, _animKeyCount);

	if (m_isTransitioning)
	{
		m_currentFrame = 0;
		m_accumulatedTime = 0.f;
	}

	bindSkeletonToAnimation(_skeleton);

	/*Create vector to store all skinning matrices*/
	std::vector<LibMath::Matrix4> skinningMatrices;

	getTheNextFrameTransform(_skeleton, _animKeyCount);

	for (int i = 0; i < m_boneCount; ++i)
	{
		int ancestorIndex = _skeleton[i].m_parentIndex;

		animateTheMesh(_skeleton, skinningMatrices, createInterpolatedMatrix(i, _skeleton, _currentFrame,
					   _animKeyCount), i, ancestorIndex);
	}
	
	m_isTransitioning = false;

	SetSkinningPose(&skinningMatrices[0][0][0], m_boneCount);
}

/// Switch between transition without crossfading
void				MySimulation::switchAnimation(float _frameTime)
{
	if (m_currentFrame >= m_walkAnimation.m_frameCount - 1 && m_walkAnimation.m_isActivated)
	{
		m_walkAnimation.m_isActivated = false;
		m_runAnimation.m_isActivated = true;
		m_isTransitioning = true;
	}
	else if (m_currentFrame >= m_runAnimation.m_frameCount - 1 && m_runAnimation.m_isActivated)
	{
		m_runAnimation.m_isActivated = false;
		m_walkAnimation.m_isActivated = true;
		m_isTransitioning = true;
	}

	if (m_walkAnimation.m_isActivated)
	{
		playAnimation(m_walkAnimation.m_skeletonAnim, m_walkAnimation.m_frameCount, m_currentFrame, _frameTime);
	}
	else if (m_runAnimation.m_isActivated)
	{
		playAnimation(m_runAnimation.m_skeletonAnim, m_runAnimation.m_frameCount, m_currentFrame, _frameTime);
	}
}

/// Step 1 : draw the skeleton by using the bind pose and regarding the hierarchy
void				MySimulation::step1(float frameTime)
{
	/*Init root bind position/rotation*/
	m_walkAnimation.m_skeletonAnim[0].m_worldTransform = m_walkAnimation.m_skeletonAnim[0].m_localTransform;

	for (int i = 1; i < m_boneCount; ++i)
	{
		/*Get the parent index*/
		int ancestorIndex = m_walkAnimation.m_skeletonAnim[i].m_parentIndex;

		/*Combine the local transform with the parent transform*/
		m_walkAnimation.m_skeletonAnim[i].m_worldTransform = m_walkAnimation.m_skeletonAnim[i].m_localTransform * 
															 m_walkAnimation.m_skeletonAnim[ancestorIndex].m_worldTransform;

		/*Draw the bone*/
		drawSkeleton(m_walkAnimation.m_skeletonAnim[i].m_worldTransform.m_position, 
					 m_walkAnimation.m_skeletonAnim[ancestorIndex].m_worldTransform.m_position,
					 m_offset, { 0.95, 0.22, 0.42 });
	}
}

/// Step 2 : Draw the skeleton from frame 1 to frame 30
void				MySimulation::step2(float frameTime)
{
	frameCounter(frameTime, m_walkAnimation.m_frameCount);

	bindSkeletonToAnimation(m_walkAnimation.m_skeletonAnim);

	for (int i = 1; i < m_boneCount; ++i)
	{
		int ancestorIndex = m_walkAnimation.m_skeletonAnim[i].m_parentIndex;

		/*Draw the bone for each frame*/
		drawSkeleton(m_walkAnimation.m_skeletonAnim[i].m_worldTransforms[m_currentFrame].m_position,
					 m_walkAnimation.m_skeletonAnim[ancestorIndex].m_worldTransforms[m_currentFrame].m_position,
					 m_offset, { 0.95, 0.22, 0.42 });
	}
}

/// Step 3 : Animate the mesh
void				MySimulation::step3(float frameTime)
{
	frameCounter(frameTime, m_walkAnimation.m_frameCount);

	bindSkeletonToAnimation(m_walkAnimation.m_skeletonAnim);

	///*Create vector to store all skinning matrices*/
	std::vector<LibMath::Matrix4> skinningMatrices;

	for (int i = 0; i < m_boneCount; ++i)
	{
		int ancestorIndex = m_walkAnimation.m_skeletonAnim[i].m_parentIndex;

		/*Convert the bone transform to a matrix*/
		LibMath::Matrix4 boneMatrix = transformToMatrix4(m_walkAnimation.m_skeletonAnim[i].m_worldTransforms[m_currentFrame]);

		animateTheMesh(m_walkAnimation.m_skeletonAnim, skinningMatrices, boneMatrix, i, ancestorIndex);
	}
	SetSkinningPose(&skinningMatrices[0][0][0], m_boneCount);
}

/// Step 4 : Interpolate poses between frames
void				MySimulation::step4(float frameTime)
{
	frameCounter(frameTime, m_walkAnimation.m_frameCount);

	bindSkeletonToAnimation(m_walkAnimation.m_skeletonAnim);

	/*Create vector to store all skinning matrices*/
	std::vector<LibMath::Matrix4> skinningMatrices;

	getTheNextFrameTransform(m_walkAnimation.m_skeletonAnim, m_walkAnimation.m_frameCount);

	for (int i = 0; i < m_boneCount; ++i)
	{
		int ancestorIndex = m_walkAnimation.m_skeletonAnim[i].m_parentIndex;

		animateTheMesh(m_walkAnimation.m_skeletonAnim, skinningMatrices, 
					   createInterpolatedMatrix(i, m_walkAnimation.m_skeletonAnim, m_currentFrame, m_walkAnimation.m_frameCount),
					   i, ancestorIndex);
	}
	SetSkinningPose(&skinningMatrices[0][0][0], m_boneCount);
}