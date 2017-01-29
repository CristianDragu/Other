#version 330
layout(lines) in;
layout(triangle_strip, max_vertices = 256) out;

uniform mat4 view_matrix, projection_matrix;
uniform vec4[100] control_p;
uniform int nr_control_p;
uniform int tipCurba;
uniform int num_puncte_generate;
uniform int num_instante;
uniform float max_translate;
uniform float max_rotate;
uniform int rotate;

in int instanta[2];
int BEZIER = 0;
int HERMITE = 1;
int BSPLINE = 2;
int NURBS = 3;
int SPLINE = 4;

vec3 rotateY(vec3 punct, float u){
	float x = punct.x * cos(u) - punct.z *sin(u);
	float z = punct.x * sin(u) + punct.z *cos(u);
	return vec3(x, punct.y, z);
}

vec4 rotateY(vec4 punct, float u){
	float x = punct.x * cos(u) - punct.z *sin(u);
	float z = punct.x * sin(u) + punct.z *cos(u);
	return vec4(x, punct.y, z, punct.w);
}

vec3 translateX(vec3 punct, float s){
	return vec3(punct.x + s, punct.y, punct.z);
}

vec4 translateX(vec4 punct, float s){
	return vec4(punct.x + s, punct.y, punct.z, punct.w);
}

int fact(int n) {
	int factorial = 1;

	for (int i = 2; i <= n; i++)
		factorial *= i;

	return factorial;
}

float power(float t, int k) {
	float p = 1.0;

	for (int i = 1; i <= k; i++)
		p *= t;

	return p;
}

float polynomialBernstein(float t, int i){

	return ( fact(nr_control_p - 1) * power(t, i) * power(1 - t, nr_control_p - i - 1) ) / ( fact(i) * fact(nr_control_p - i - 1) );

}

vec4 bezier(float t) {
	
	vec4 bezierPoint = vec4(0, 0, 0, 0);

	for(int i = 0; i < nr_control_p; i++)
		bezierPoint += control_p[i] * polynomialBernstein(t, i);

	return bezierPoint;

}

void drawPoints(vec4 point1, vec4 point2, vec4 point3, vec4 point4) {

	gl_Position = projection_matrix * view_matrix * point1; EmitVertex();
	gl_Position = projection_matrix * view_matrix * point2; EmitVertex();
	gl_Position = projection_matrix * view_matrix * point3; EmitVertex();
	gl_Position = projection_matrix * view_matrix * point4; EmitVertex();

	EndPrimitive();
}

void drawBezierCurve(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_instante = max_translate / num_instante;

	point1 = translateX(bezier(t1), instanta[0] * distanta_instante);
	point2 = translateX(bezier(t1), (instanta[0] + 1) * distanta_instante);
	point3 = translateX(bezier(t2), instanta[0] * distanta_instante);
	point4 = translateX(bezier(t2), (instanta[0] + 1) * distanta_instante);

	drawPoints(point1, point2, point3, point4);
}

void drawBezierCurveRotate(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_rotatie = max_rotate / num_instante;

	point1 = rotateY(bezier(t1), instanta[0] * distanta_rotatie);
	point2 = rotateY(bezier(t1), (instanta[0] + 1) * distanta_rotatie);
	point3 = rotateY(bezier(t2), instanta[0] * distanta_rotatie);
	point4 = rotateY(bezier(t2), (instanta[0] + 1) * distanta_rotatie);

	drawPoints(point1, point2, point3, point4);
}

vec4 bspline(float t, int i) {

	vec4 p;
	float t2 = t * t, b, b1, b2;

	b = 0.5 * (1 - 2 * t + t2);
	b1 = 0.5 * (-2 * t2 + 2 * t + 1);
	b2 = 0.5 * t2;

	p = b * control_p[i - 1] + b1 * control_p[i] + b2 * control_p[i + 1];

	return p;
}

void drawBsplineCurve(float t1, float t2) {
	
	vec4 point1, point2, point3, point4;
	float distanta_instante = max_translate / num_instante;

	for(int i = 1; i < nr_control_p - 1; i++) {
		point1 = translateX(bspline(t1, i), instanta[0] * distanta_instante);
		point2 = translateX(bspline(t1, i), (instanta[0] + 1) * distanta_instante);
		point3 = translateX(bspline(t2, i), instanta[0] * distanta_instante);
		point4 = translateX(bspline(t2, i), (instanta[0] + 1) * distanta_instante);

		drawPoints(point1, point2, point3, point4);
	}
}

void drawBsplineCurveRotate(float t1, float t2) {
	
	vec4 point1, point2, point3, point4;
	float distanta_rotatie = max_rotate / num_instante;

	for(int i = 1; i < nr_control_p - 1; i++) {
		point1 = rotateY(bspline(t1, i), instanta[0] * distanta_rotatie);
		point2 = rotateY(bspline(t1, i), (instanta[0] + 1) * distanta_rotatie);
		point3 = rotateY(bspline(t2, i), instanta[0] * distanta_rotatie);
		point4 = rotateY(bspline(t2, i), (instanta[0] + 1) * distanta_rotatie);

		drawPoints(point1, point2, point3, point4);
	}
}

vec4 hermite(float t, int i) {
	
	float t2, t3, h1, h2, h3, h4;
	
	vec4 p;

	t2 = t * t;
	t3 = t * t * t;

	h1 = 2 * t3 - 3 * t2 + 1;
	h2 = -2 * t3 + 3 * t2;
	h3 = t3 - 2 * t2 + t;
	h4 = t3 - t2;

	p = h1 * control_p[i] + h2 * control_p[i + 1] + h3 * 0.5 * (control_p[i + 1] - control_p[i - 1]) + h4 * 0.5 * (control_p[i + 2] - control_p[i]);

	return p;
}

void drawHermite(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_instante = max_translate / num_instante;

	for(int i = 0; i < nr_control_p - 2; i++) {
		point1 = translateX(hermite(t1, i), instanta[0] * distanta_instante);
		point2 = translateX(hermite(t1, i), (instanta[0] + 1) * distanta_instante);
		point3 = translateX(hermite(t2, i), instanta[0] * distanta_instante);
		point4 = translateX(hermite(t2, i), (instanta[0] + 1) * distanta_instante);

		drawPoints(point1, point2, point3, point4);
	}
}

void drawHermiteRotate(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_rotatie = max_rotate / num_instante;

	for(int i = 0; i < nr_control_p - 2; i++) {
		point1 = rotateY(hermite(t1, i), instanta[0] * distanta_rotatie);
		point2 = rotateY(hermite(t1, i), (instanta[0] + 1) * distanta_rotatie);
		point3 = rotateY(hermite(t2, i), instanta[0] * distanta_rotatie);
		point4 = rotateY(hermite(t2, i), (instanta[0] + 1) * distanta_rotatie);

		drawPoints(point1, point2, point3, point4);
	}
}

vec4 nurbs(float t, int i) {

	vec4 p;
	float t2 = t * t, b, b1, b2;

	b = 0.5 * (1 - 2 * t + t2);
	b1 = 0.5 * (-2 * t2 + 2 * t + 1);
	b2 = 0.5 * t2;

	p = (b * control_p[i - 1] + b1 * control_p[i] + b2 * control_p[i + 1]) / (b + b1 + b2);

	return p;
}

void drawNurbs(float t1, float t2) {
	
	vec4 point1, point2, point3, point4;
	float distanta_instante = max_translate / num_instante;

	for(int i = 1; i < nr_control_p - 1; i++) {
		point1 = translateX(nurbs(t1, i), instanta[0] * distanta_instante);
		point2 = translateX(nurbs(t1, i), (instanta[0] + 1) * distanta_instante);
		point3 = translateX(nurbs(t2, i), instanta[0] * distanta_instante);
		point4 = translateX(nurbs(t2, i), (instanta[0] + 1) * distanta_instante);

		drawPoints(point1, point2, point3, point4);
	}
}

void drawNurbsRotate(float t1, float t2) {
	
	vec4 point1, point2, point3, point4;
	float distanta_rotatie = max_rotate / num_instante;

	for(int i = 1; i < nr_control_p - 1; i++) {
		point1 = rotateY(nurbs(t1, i), instanta[0] * distanta_rotatie);
		point2 = rotateY(nurbs(t1, i), (instanta[0] + 1) * distanta_rotatie);
		point3 = rotateY(nurbs(t2, i), instanta[0] * distanta_rotatie);
		point4 = rotateY(nurbs(t2, i), (instanta[0] + 1) * distanta_rotatie);

		drawPoints(point1, point2, point3, point4);
	}
}

vec4 spline(float t, int i) {
	
	float t2, t3, f1, f2, f3, f4;
	
	vec4 p;

	t2 = t * t;
	t3 = t * t * t;

	f1 = 2 * t3 - 3 * t2 + 1;
	f2 = -2 * t3 + 3 * t2;
	f3 = t3 - 2 * t2 + t;
	f4 = t3 - t2;

	vec4 tanP1 = 0.5 * (control_p[i + 1] - control_p[i - 1]);
	vec4 tanP2 = 0.5 * (control_p[i + 2] - control_p[i]);

	p = f1 * control_p[i] + f2 * control_p[i + 1] + f3 * tanP1 + f4 * tanP2;

	return p;
}

void drawSpline(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_instante = max_translate / num_instante;

	for(int i = 0; i < nr_control_p - 2; i++) {
		point1 = translateX(spline(t1, i), instanta[0] * distanta_instante);
		point2 = translateX(spline(t1, i), (instanta[0] + 1) * distanta_instante);
		point3 = translateX(spline(t2, i), instanta[0] * distanta_instante);
		point4 = translateX(spline(t2, i), (instanta[0] + 1) * distanta_instante);

		drawPoints(point1, point2, point3, point4);
	}
}

void drawSplineRotate(float t1, float t2) {

	vec4 point1, point2, point3, point4;
	float distanta_rotatie = max_rotate / num_instante;

	for(int i = 0; i < nr_control_p - 2; i++) {
		point1 = rotateY(spline(t1, i), instanta[0] * distanta_rotatie);
		point2 = rotateY(spline(t1, i), (instanta[0] + 1) * distanta_rotatie);
		point3 = rotateY(spline(t2, i), instanta[0] * distanta_rotatie);
		point4 = rotateY(spline(t2, i), (instanta[0] + 1) * distanta_rotatie);

		drawPoints(point1, point2, point3, point4);
	}
}

void main(){
	vec4 aux1, aux2, aux3, aux4, aux;

	for (int i = 0; i < nr_control_p; i++) {
		aux = control_p[i];
		aux1 = vec4(aux.x + 1.0, aux.y + 1.0, aux.z, 1.0);
		aux2 = vec4(aux.x - 1.0, aux.y + 1.0, aux.z, 1.0);
		aux3 = vec4(aux.x + 1.0, aux.y - 1.0, aux.z, 1.0);
		aux4 = vec4(aux.x - 1.0, aux.y - 1.0, aux.z, 1.0);

		drawPoints(aux1, aux2, aux3, aux4);
	}

	if(nr_control_p >= 2){

		if(rotate == 0) {
			float t1, t2;

			for(float i = 0.0; i < num_puncte_generate; i += 1.0) {
		
				t1 = i / num_puncte_generate;
				t2 = (i + 1.0) / num_puncte_generate;

				if(tipCurba == BEZIER)
					drawBezierCurve(t1, t2);
				else if(tipCurba == BSPLINE)
					drawBsplineCurve(t1, t2);
				else if(tipCurba == HERMITE)
					drawHermite(t1, t2);
				else if(tipCurba == NURBS)
					drawNurbs(t1, t2);
				else if(tipCurba == SPLINE)
					drawSpline(t1, t2);
			}
		}
		else {
			float t1, t2;

			for(float i = 0.0; i < num_puncte_generate; i += 1.0) {
		
				t1 = i / num_puncte_generate;
				t2 = (i + 1.0) / num_puncte_generate;

				if(tipCurba == BEZIER)
					drawBezierCurveRotate(t1, t2);
				else if(tipCurba == BSPLINE)
					drawBsplineCurveRotate(t1, t2);
				else if(tipCurba == HERMITE)
					drawHermiteRotate(t1, t2);
				else if(tipCurba == NURBS)
					drawNurbsRotate(t1, t2);
				else if(tipCurba == SPLINE)
					drawSplineRotate(t1, t2);
			}
		}
	}
}
