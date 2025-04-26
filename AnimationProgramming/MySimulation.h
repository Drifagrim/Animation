#pragma once

#pragma region Simulation

#include "Simulation.h"
#include "Transform.h"

#pragma endregion

#pragma region Standard

#include <vector>

#pragma endregion

#pragma region LibMath

#include "LibMath/Header/Vector/Vector3.h"
#include "LibMath/Header/Vector/Vector4.h"
#include "LibMath/Header/Quaternion.h"

#pragma endregion

struct Bone
{
	std::vector<Transform>	m_localTransforms; // Vector to store local transforms by frame
	std::vector<Transform>	m_worldTransforms; // Vector to store world transforms by frame

	Transform				m_localTransform; // Local transform
	Transform				m_worldTransform; // World transform/bind pose

	int						m_parentIndex = 0; // Parent index
};

struct Animation
{
	std::vector<Bone>	m_skeletonAnim;

	size_t				m_frameCount;

	float				m_duration;

	bool				m_isActivated = false;
};

class MySimulation : public ISimulation
{
	/// Variables
	Animation*						m_currentAnimation = nullptr;
	Animation*						m_nextAnimation = nullptr;
	Animation						m_walkAnimation;
	Animation						m_runAnimation;

	float 							m_accumulatedTime = 0.f; // Accumulated time
	float							m_currentPartialFrame = 0.f;
	float							m_offset = 50.f;
	float							m_transitionTime = 2.f;
	float							m_transitionProgress = 0.f;

	size_t							m_boneCount = 0; // Number of bones

	int 							m_currentFrame = 0; // Current walk animation frame
	
	bool							m_isTransitioning = false;

	/// Initialize
	// Initialize members
	void 					initMembers();
	// Initialize the scale to {1.f, 1.f, 1.f}
	void					initScale(std::vector<Bone>& _skeleton, int _animKeyCount);
	// Initialize the simulation
	virtual void			init() override;

	/// Print
	// Print the bone hierarchy
	void					printBoneHierarchy();
	// Print the bone hierarchy without the IK bones
	void					printBoneHierarchyWithoutIK();

	/// Getter
	// Get the number of bones without the IK bones
	void					getBoneCount();
	// Get bone informations
	void					getBoneInformations(std::vector<Bone>& _skeleton);
	// Get skeleton bone local bind transform
	void					getSkeletonBoneLocalBindTransform(int _boneIndex, LibMath::Vector3& _position, 
															  LibMath::Quaternion& _rotation);
	// Get the walk animation informations
	void					getAnimationInformations(const char* _animName, std::vector<Bone>& _skeleton, size_t _animKeyCount);

	// Get the walk animation local bone transformation
	void					getAnimLocalBoneTransform(const char* _animeName, int _boneIndex, int _frameIndex, 
													  LibMath::Vector3& _position, LibMath::Quaternion& _rotation);
	// Get the next frame transform
	void					getTheNextFrameTransform(std::vector<Bone>& _skeleton, size_t _animKeyCount);
	// Get animation duration
	float 					getAnimationDuration(size_t _animKeyCount, float _frameTime);
	// Get the result of interpolation between the two animations
	Transform				GetThefinalTransform(float& _frameTime);

	/// Update
	// Update the simulation
	virtual void			update(float frameTime) override;

	/// Draw
	// Draw axis of the world
	void					drawWorldMarker();
	// Draw skeleton
	void					drawSkeleton(LibMath::Vector3& _childPosition, LibMath::Vector3& _parentPosition, 
										 float _offset, LibMath::Vector3 _color);

	/// Timer
	// Frame counter to update animation in regard to the frameTime
	void					frameCounter(float _frameTime, size_t _animKeyCount);

	/// Interpolate
	// Interpolate between current frame and next frame
	Transform				interpolateBetweenFrames(int& _index, std::vector<Bone>& _skeleton, int& _frame, 
													 size_t& _animKeyCount);
	// Interpolate between two animation
	Transform				interpolateAnimation(Animation* _anim, float _frameTime);

	/// Bind
	// Bind skeleton to animation
	void					bindSkeletonToAnimation(std::vector<Bone>& _skeleton);

	/// Animate
	// Animate the mesh in regard to the running animation
	void					animateTheMesh(std::vector<Bone>& _skeleton, std::vector<LibMath::Matrix4>& _skinningMatrix,
										   LibMath::Matrix4& _boneMatrix, int _index, int _ancestorIndex);

	/// Create
	// Create the interpolated matrix
	LibMath::Matrix4		createInterpolatedMatrix(int _index, std::vector<Bone>& _skeleton, int _frame, size_t _animKeyCount);

	/// Play
	// Play animation
	void					playAnimation(std::vector<Bone>& _skeleton, size_t& _animKeyCount, int& _currentFrame, 
										  float& _frameTime);
	/// Switch
	// Switch between walk animation and run animation
	void					switchAnimation(float _frameTime);	

	/// Steps
	// Step 1 : draw the skeleton by using the bind pose and regarding the hierarchy
	void					step1(float frameTime);
	// Step 2 : Draw the skeleton from frame 1 to frame 30
	void					step2(float frameTime);
	// Step 3 : Animate the mesh
	void					step3(float frameTime);
	// Step 4 : Interpolate poses between frames
	void					step4(float frameTime);

}; // !class MySimulation