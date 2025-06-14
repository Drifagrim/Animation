
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	vec4 pos = vec4(inputPosition, 1.0f);
	
	float scalar = 1.0 / (boneWeights.x + boneWeights.y + boneWeights.z + boneWeights.w);

	mat4 result = (scalar * boneWeights.w) * skin.mat[int(boneIndices.w)] +
				  (scalar * boneWeights.z) * skin.mat[int(boneIndices.z)] +
				  (scalar * boneWeights.y) * skin.mat[int(boneIndices.y)] +
				  (scalar * boneWeights.x) * skin.mat[int(boneIndices.x)];

	pos = result * pos;

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(pos.xyz, 1.0f));
	outNormal = mat3(modelViewMatrix) * normal;
	
	outNormal = normalize(outNormal);
}
