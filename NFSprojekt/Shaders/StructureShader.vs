attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;
attribute vec3 inTangent;
attribute vec3 inBitangent;

uniform mat4 MVP, ModelViewMatrix, ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 InvertedViewMatrix;
uniform vec3 EyePosition;
uniform float Shift;

varying vec4 LightSpacePosition;
varying vec3 Normal;
varying vec3 Tangent;
varying vec3 Binormal;
varying vec3 WorldPosition;
varying float DepthValue;


void main()
{
	gl_TexCoord[0].st = inTexcoord;
	Normal = normalize (NormalMatrix * inNormal);
	Tangent = normalize (NormalMatrix * inTangent);
	Binormal = normalize (NormalMatrix * inBitangent);
	
	gl_Position = MVP * vec4(inPosition, 1.0);
}
