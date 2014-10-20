#version 330

in vec4 colour;
in vec3 TexCoord;

out vec4 FragColor;

uniform BlobSettings
{
	vec4 InnerColour;
	vec4 OuterColour;
	float RadiusInner;
	float RadiusOuter;
};

void main(void)
{
	//float dx = TexCoord.x - 0.5;
	//float dy = TexCoord.y - 0.5;
	//float dist = sqrt(dx*dx + dy*dy);
	//FragColor = mix(InnerColour, OuterColour, smoothstep(RadiusInner, RadiusOuter, dist));
	FragColor = colour;
	//FragColor = vec4(gl_FragCoord.x/640.0, gl_FragCoord.y/480.0, 0.5, floor(mod(gl_FragCoord.y, 2.0)));
}