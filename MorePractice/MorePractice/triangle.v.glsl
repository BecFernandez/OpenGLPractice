#version 330

in vec3 vertexPosition;
in vec4 vertexColour;
in vec3 vertexTexCoord;

out vec3 TexCoord;
out vec4 colour;

uniform mat4 RotationMatrix;

void main()
{
	//TexCoord = vertexTexCoord;
	
	gl_Position = vec4(vertexPosition, 1.0);
	colour = vertexColour;
}