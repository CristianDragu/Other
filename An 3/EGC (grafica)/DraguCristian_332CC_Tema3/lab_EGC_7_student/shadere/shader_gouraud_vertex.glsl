#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 1) in vec3 normala;		

uniform mat4 model_matrix, view_matrix, projection_matrix;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;
uniform float end_time;

const int maxUnde = 3;
const float PI2 = 6.28318;

struct Unda {
	int eCirculara;
	float amplitudine, lungimeUnda, s;
	vec2 directie;
};

uniform Unda sinusoida[maxUnde];

out float light;
out vec3 basicColor;

vec2 calcDirectie(vec2 centru, vec2 p) {
	vec2 aux = vec2(centru[0] - p[0], centru[1] - p[1]);
	float modul = sqrt((centru[0] + p[0]) * (centru[0] + p[0]) + (centru[1] + p[1]) * (centru[1] + p[1]));
	return vec2(aux[0] / modul, aux[1] / modul);
}

void main(){

	gl_Position = model_matrix * vec4(in_position, 1); 

	float y = 0.0;
	float y1 = gl_Position[1];
	float y2 = gl_Position[1];
	float y3 = gl_Position[1];
	float y4 = gl_Position[1];
	float y5 = gl_Position[1];
	vec2 aux;
	
	for(int i = 0; i < 3; i+=2)
		if(sinusoida[i].eCirculara == 0){
			y = (distance(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])) / 141.0) * 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			gl_Position[1] = gl_Position[1] + y;

			y2 += (distance(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])) / 141.0) * 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(sinusoida[i].directie, vec2(gl_Position[0] - 1.0, gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y3 += (distance(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])) / 141.0) * 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(sinusoida[i].directie, vec2(gl_Position[0] + 1.0, gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y4 += (distance(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])) / 141.0) * 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2] - 1.0))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y5 += (distance(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])) / 141.0) * 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2] + 1.0))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
		}
		else if(sinusoida[i].eCirculara == 1){
			y =  2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(calcDirectie(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2])), vec2(gl_Position[0], gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			gl_Position[1] = gl_Position[1] + y;

			y2 += 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(calcDirectie(sinusoida[i].directie, vec2(gl_Position[0] - 1.0, gl_Position[2])), vec2(gl_Position[0] - 1.0, gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y3 += 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(calcDirectie(sinusoida[i].directie, vec2(gl_Position[0] + 1.0, gl_Position[2])), vec2(gl_Position[0] + 1.0, gl_Position[2]))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y4 += 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(calcDirectie(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2] - 1.0)), vec2(gl_Position[0], gl_Position[2] - 1.0))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
			y5 += 2 * sinusoida[i].amplitudine 
					* pow( (sin(dot(calcDirectie(sinusoida[i].directie, vec2(gl_Position[0], gl_Position[2] + 1.0)), vec2(gl_Position[0], gl_Position[2] + 1.0))
								* (PI2 / sinusoida[i].lungimeUnda)
								+ end_time * (sinusoida[i].s * (PI2 / sinusoida[i].lungimeUnda))) 
								+ 1.0) / 2.0 
						,2 );
		}

	vec3 v1 = normalize( vec3(gl_Position[0], y5, gl_Position[2] + 1.0) - gl_Position.xyz);
	vec3 v2 = normalize( vec3(gl_Position[0] + 1.0, y3, gl_Position[2]) - gl_Position.xyz);
	vec3 v3 = normalize( vec3(gl_Position[0], y4, gl_Position[2] - 1.0) - gl_Position.xyz);
	vec3 v4 = normalize( vec3(gl_Position[0] - 1.0, y2, gl_Position[2]) - gl_Position.xyz);

	vec3 normala = cross(v1, v2) + cross(v2, v3) + cross(v3, v4) + cross(v4, v1);
	normala.x = normala.x / 4.0;
	normala.y = normala.y / 4.0;
	normala.z = normala.z / 4.0;

	vec3 world_pos = (model_matrix * vec4(in_position, 1)).xyz;
	vec3 world_normal = normalize( mat3(model_matrix) * normala);
	vec3 L = normalize(light_position - world_pos);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);

	light = material_kd * max(dot(world_normal, L), 0) 
		+ material_ks * pow(max (dot(world_normal, H), 0), material_shininess);

	float aux2 = gl_Position[1];
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1); 	
	gl_Position[1] = aux2;

	basicColor = vec3(0.15, 0.16, 0.3);
}
