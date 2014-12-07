#version 330

in vec4 vertexPosition;
in vec4 vertexColour;
in vec2 vertexTexCoord;

out vec2 TexCoord;
out vec4 colour;

uniform mat4 projectionView;
uniform mat4 world;

void main()
{
	TexCoord = vertexTexCoord;
	
	gl_Position = projectionView * world * vertexPosition ;
	colour = vertexColour;
}