#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D textura1;
uniform sampler2D textura2;
uniform int has_alpha;

in vec2 texcoord;
varying vec4 position;

void main(){

	vec3 texel = texture(textura2, texcoord).xyz;
	
	if (has_alpha == 1){
		if(position[0] <= -50 || position[0] >= 50)
			discard;
		if(texel.x == 0 && texel.y == 0 && texel.z == 0)
			discard;
	}
	out_color = texture(textura1, texcoord);
}