#version 330

in vec4 colour;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textureSampler;

void main()
{
	vec4 fontTexColour = texture(textureSampler, TexCoord).bgra;
	FragColor =  fontTexColour * colour;
	FragColor.a = fontTexColour.b;
}