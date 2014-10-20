#version 330

in vec4 colour;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textureSampler;

void main(void)
{
	
	FragColor = texture(textureSampler, TexCoord).bgra * colour;
	
}