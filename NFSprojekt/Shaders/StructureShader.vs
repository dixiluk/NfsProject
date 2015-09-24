attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;
attribute vec3 inTangent;
attribute vec3 inBitangent;

uniform mat4 MVP;

void main()
{
	gl_TexCoord[0].st = inTexcoord;
	gl_Position = MVP * vec4(inPosition, 1.0);
}
