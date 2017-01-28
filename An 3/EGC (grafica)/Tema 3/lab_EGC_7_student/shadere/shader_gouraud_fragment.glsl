#version 330
layout(location = 0) out vec4 out_color;

in float light;
in vec3 basicColor;

void main(){

	out_color = vec4(basicColor.x + light, basicColor.y + light, basicColor.z + light, 1);

}