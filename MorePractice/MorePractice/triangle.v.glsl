#version 330

in vec4 vertexPosition;
in vec4 vertexColour;
in vec2 vertexTexCoord;

out vec2 TexCoord;
out vec4 colour;

uniform mat4 RotationMatrix;

void main()
{
	TexCoord = vertexTexCoord;
	
	gl_Position = vertexPosition;
	colour = vertexColour;
}