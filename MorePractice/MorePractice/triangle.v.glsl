#version 330

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec4 vertexColour;
layout (location = 2) in vec2 vertexTexCoord;

out vec4 colour;
out vec2 TexCoord;

uniform mat4 projectionView;
uniform mat4 world;

void main()
{
	TexCoord = vertexTexCoord;
	
	gl_Position = projectionView * world * vertexPosition ;
	colour = vertexColour;
}