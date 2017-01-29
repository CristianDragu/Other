#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D textura_cubemap;

in vec3 texcoord;
uniform int objNo;

void main(){
	
	if(objNo == 0)
		out_color = vec4(1, 0.8, 0, 1);
	else {
		vec3 tex = texture(textura_cubemap, texcoord.xy).xyz;
		out_color = vec4(tex, 1);
	}
}