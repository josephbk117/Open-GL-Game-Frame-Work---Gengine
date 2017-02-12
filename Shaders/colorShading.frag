#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;
void main()
{
	
	vec4 textureColor = texture(mySampler,fragmentUV);
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x - time*2.15) + 1.0) * 0.5,
		     fragmentColor.g * (cos(fragmentPosition.y+ time*1.5) + 1.0) * 0.5,
		      fragmentColor.b * (cos(fragmentPosition.x *0.3-+time*1.35) + 1.0) * 0.5,fragmentColor.a) *textureColor;
	
}