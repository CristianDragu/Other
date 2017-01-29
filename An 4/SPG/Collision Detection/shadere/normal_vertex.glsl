#version 330

layout(location = 0) in vec3 in_position;		
uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec3 texcoord;
uniform int objNo;
uniform float x_off_bunny;
uniform float y_off_bunny;
uniform float z_off_bunny;

void main(){

    texcoord = normalize(in_position);
	
	if(objNo == 0) {
		gl_Position = projection_matrix * view_matrix * model_matrix*vec4(in_position,1) + vec4(x_off_bunny, y_off_bunny, z_off_bunny, 0);
	} else {
		gl_Position = projection_matrix * view_matrix * model_matrix*vec4(in_position,1);
	}
}
