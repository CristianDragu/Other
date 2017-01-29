//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

#include "lab_mesh_loader.hpp"
#include "lab_geometry.hpp"
#include "lab_shader_loader.hpp"
#include "lab_glut.hpp"
#include "lab_texture_loader.hpp"
#include "lab_camera.hpp"
#include <ctime>
#include <algorithm>

#define SPHERE 0
#define TRIANGLE 1

class Laborator : public lab::glut::WindowListener{

//variabile
private:
    lab::Camera camera;
	glm::mat4 projection_matrix;											//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int shader_cubemap, shader_normal;											//id-ul de opengl al obiectului de tip program shader

	struct Point {
		float x, y, z;
	};

	//meshe
	lab::Mesh mesh_cubemap;	
    lab::Mesh mesh_bunny;

	//texturi
	unsigned int texture_cubemap;

	// obiectul care este trimis la shader
	unsigned int objNo;
	float sem;

	// pozitiile vertecsilor
	std::vector<lab::VertexFormat> verticesbox;
	std::vector<lab::VertexFormat> verticesbunny;

	float x_off_bunny, y_off_bunny, z_off_bunny;
	int direction; // directia de deplasare
	float Rbox, Rbunny;
	float speed = 0.6f;

	float d1, d2, dist_v[3], dist_u[3], interval1[2], interval2[2], projV[3], projU[3];
	glm::vec3 D, N1, N2;
	int i0 = 0, i1 = 0;
	bool coplanare;

	bool mode = false;

//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);
		glEnable(GL_DEPTH_TEST);

        shader_normal = lab::loadShader("shadere/normal_vertex.glsl", "shadere/normal_fragment.glsl");
        
		lab::loadObj("resurse\\box.obj",mesh_cubemap, 0, -30.0, -70.0, verticesbox);	
        lab::loadObj("resurse\\bunny.obj", mesh_bunny, 0, 50.0, -70.0, verticesbunny);
		
		texture_cubemap = lab::loadTextureBMP("resurse/ground.bmp");

        x_off_bunny = 0.0f; y_off_bunny = 0.0f; z_off_bunny = 0.0f;

		camera.set(glm::vec3(0,0,40), glm::vec3(0,0,0), glm::vec3(0,1,0));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		objNo = 0;
		direction = -1; // in jos

		Rbox = getRadius(verticesbox);
		Rbunny = getRadius(verticesbunny);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shadere
        glDeleteProgram(shader_normal);
	}

	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	
	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
    void notifyBeginFrame(){ }
	
	glm::vec3 getVector(glm::vec3 a, glm::vec3 b) {
		return glm::vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	int max(glm::vec3 a) {
		if (fabs(a.x) > fabs(a.y))
			if (fabs(a.x) > fabs(a.z))
				return 0;
			else
				return 2;
		else
			if (fabs(a.y) > fabs(a.z))
				return 1;
			else 
				return 2;
	}

	float getInterval(float pv0, float pv1, float dist0, float dist1) {
		return pv0 + (pv1 - pv0) * dist0 / (dist0 - dist1);
	}

	float sign(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		return (p1[i0] - p3[i0]) * (p2[i1] - p3[i1]) - (p2[i0] - p3[i0]) * (p1[i1] - p3[i1]);
	}

	bool PointInTriangle(glm::vec3 pt, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		bool b1, b2, b3;

		b1 = sign(pt, v1, v2) < 0.0f;
		b2 = sign(pt, v2, v3) < 0.0f;
		b3 = sign(pt, v3, v1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}

	bool doIntersect(glm::vec3 A, glm::vec3 v0, glm::vec3 u0, glm::vec3 u1) {

		glm::vec3 B = getVector(u0, u1);
		glm::vec3 C = getVector(v0, u0);

		float crossF = A[i1] * B[i0] - A[i0] * B[i1];
		float crossD = B[i1] * C[i0] - B[i0] * C[i1];

		if ((crossF > 0 && crossD >= 0 && crossD <= crossF) || (crossF < 0 && crossD <= 0 && crossD >= crossF)) {
			float crossE = A[i0] * C[i1] - A[i1] * C[i0];
			
			if (crossF > 0) {
				if (crossE >= 0 && crossE <= crossF)
					return true;
			}
			else {
				if (crossE <= 0 && crossE >= crossF)
					return true;
			}
		}

		return false;
	}

	bool edgeAgainstTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 u[3]) {

		glm::vec3 A = getVector(v1, v0);

		if (doIntersect(A, v0, u[0], u[1])) return true;
		if (doIntersect(A, v0, u[0], u[2])) return true;
		if (doIntersect(A, v0, u[1], u[2])) return true;

		return false;
	}

	bool checkCoplanarity(glm::vec3 v[3], glm::vec3 u[3]) {

		i0 = 0;
		i1 = 0;

		glm::vec3 n1 = glm::vec3(fabs(N1[0]), fabs(N1[1]), fabs(N1[2]));

		int id_max = max(n1);
	
		while (i0 == id_max)
			i0 = (i0 + 1) % 3;

		while (i1 == id_max || i1 == i0)
			i1 = (i1 + 1) % 3;
		
		if (edgeAgainstTriangle(v[0], v[1], u)) return true;
		if (edgeAgainstTriangle(v[1], v[2], u)) return true;
		if (edgeAgainstTriangle(v[2], v[0], u)) return true;

		// verific daca triunghiul t1 se gaseste in triunghiul t2
		bool inTriangle = true;
		for (int i = 0; i < 3; i++)
			if (!PointInTriangle(v[i], u[0], u[1], u[2]))
				inTriangle = false;
		if (inTriangle)
			return true;

		// si vice-versa
		inTriangle = true;
		for (int i = 0; i < 3; i++)
			if (!PointInTriangle(u[i], v[0], v[1], v[2]))
				inTriangle = false;
		if (inTriangle)
			return true;

		return false;
	}

	bool checkIntervals(float proj[], float dist[], float interval[], glm::vec3 v[3], glm::vec3 u[3]) {

		if (dist[0] * dist[1] > 0.0f) {
			interval[0] = getInterval(proj[2], proj[0], dist[2], dist[0]);
			interval[1] = getInterval(proj[2], proj[1], dist[2], dist[1]);
		}
		else if (dist[0] * dist[2] > 0.0f) {
			interval[0] = getInterval(proj[1], proj[0], dist[1], dist[0]);
			interval[1] = getInterval(proj[1], proj[2], dist[1], dist[2]);
		}
		else if (dist[1] * dist[2] > 0.0f || dist[0] != 0.0f) {
			interval[0] = getInterval(proj[0], proj[1], dist[0], dist[1]);
			interval[1] = getInterval(proj[0], proj[2], dist[0], dist[2]);
		}
		else if (dist[1] != 0.0f) {
			interval[0] = getInterval(proj[1], proj[0], dist[1], dist[0]);
			interval[1] = getInterval(proj[1], proj[2], dist[1], dist[2]);
		}
		else if (dist[2] != 0.0f) {
			interval[0] = getInterval(proj[2], proj[0], dist[2], dist[0]);
			interval[1] = getInterval(proj[2], proj[1], dist[2], dist[1]);
		}
		else {
			if (checkCoplanarity(v, u))
				return true;
			else
				coplanare = true;
		}
		
		return false;
	}

	bool TriangleToTriangleIntersection(glm::vec3 v[3], glm::vec3 u[3]) {

		// calculam planul pentru triunghiul (v0, v1, v2)
		// planul are ecuatia: N1 * X + d1 = 0
		N1 = glm::cross(getVector(v[1], v[0]), getVector(v[2], v[0]));
		d1 = -glm::dot(N1, v[0]);

		// calculez distantele de la orice punct din planul1 la planul2.
		for (int i = 0; i < 3; i++) {
			dist_u[i] = glm::dot(N1, u[i]) + d1;
			if (fabs(dist_u[i]) < 0.001)
				dist_u[i] = 0.0f;
		}

		if (dist_u[0] * dist_u[1] > 0.0f && dist_u[0] * dist_u[2] > 0.0f)
			return false;

		// calculez planul si pentru triunghiul (u0, u1, u2)
		// planul are ecuatia: N2 * X + d2 = 0
		N2 = glm::cross(getVector(u[1], u[0]), getVector(u[2], u[0]));
		d2 = -glm::dot(N2, u[0]);

		for (int i = 0; i < 3; i++) {
			dist_v[i] = glm::dot(N2, v[i]) + d2;
			if (fabs(dist_v[i]) < 0.001)
				dist_v[i] = 0.0f;
		}

		if (dist_v[0] * dist_v[1] > 0.0f && dist_v[0] * dist_v[2] > 0.0f)
			return false;

		// Daca cele 2 triunghiuri NU se afla complet in afara planului celuilalt triunghi,
		// atunci verificam daca intersectia este o linie de ecuatie: L = O + tD
		D = glm::cross(N1, N2);

		// ca sa calculam proiectiile punctelor catre celalalt plan ne folosim de o
		// optimizare. Proiectia este data de cea mai mare valoare absoluta din D
		int id_max = max(D);

		for (int i = 0; i < 3; i++) {
			projU[i] = u[i][id_max];
			projV[i] = v[i][id_max];
		}
		
		// verificam care sunt cele 2 puncte ale unui triunghi pe aceeasi parte a planului
		// despartit de linie
		interval1[0] = 0.0f, interval1[1] = 0.0f, interval2[0] = 0.0f, interval2[1] = 0.0f;

		coplanare = false;
		if (checkIntervals(projU, dist_u, interval1, u, v))
			return true;
		
		if (checkIntervals(projV, dist_v, interval2, v, u))
			return true;

		// daca intervalele de pe linia care intersecteaza triunghiurile nu se intersecteaza
		// atunci nici triunghiurile nu au coliziune
		if (glm::max(interval1[0], interval1[1]) < glm::min(interval2[0], interval2[1]) ||
			glm::max(interval2[0], interval2[1]) < glm::min(interval1[0], interval1[1]))
			return false;

		if (coplanare == true)
			return false;

		return true;
	}

	// gaseste centrul obiectului in functie de offsetul pe verticala
    Point findCenter(std::vector<lab::VertexFormat> vertices, float y_off){

    	Point center;
    	center.x = 0.0f; center.y = 0.0f; center.z = 0.0f;

    	for(unsigned int i = 0; i < vertices.size(); i++) {
    		center.x += vertices[i].position_x;
    		center.y += vertices[i].position_y + y_off;
    		center.z += vertices[i].position_z;
    	}

    	center.x /= vertices.size();
    	center.y /= vertices.size();
    	center.z /= vertices.size();
    	return center;
    }

    // returneaza raza sferei in care se incadreaza obiectul
    float getRadius(std::vector<lab::VertexFormat> vertices) {

    	float min_x = 1000, min_y = 1000, min_z = 1000;
    	float max_x = -1000, max_y = -1000, max_z = -1000;

    	for(unsigned int i = 0; i < vertices.size(); i++) {
    		
    		if (vertices[i].position_x < min_x)
    			min_x = vertices[i].position_x;

    		if (vertices[i].position_x > max_x)
    			max_x = vertices[i].position_x;
    		
    		if (vertices[i].position_y < min_y)
    			min_y = vertices[i].position_y;
    		
    		if (vertices[i].position_y > max_y)
    			max_y = vertices[i].position_y;
    		
    		if (vertices[i].position_z < min_z)
    			min_z = vertices[i].position_z;
    		
    		if (vertices[i].position_z > max_z)
    			max_z = vertices[i].position_z;
    	}

    	float radius_x, radius_y, radius_z;

    	radius_x = std::abs(float(max_x - min_x));
    	radius_y = std::abs(float(max_y - min_y));
    	radius_z = std::abs(float(max_z - min_z));

    	if (radius_x > radius_y && radius_x > radius_z)
    		return radius_x;

    	if (radius_y > radius_x && radius_y > radius_z)
    		return radius_y;

    	return radius_z;
    }

    float getDistance(Point P1, Point P2) {

    	return float(std::sqrt( (P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y) + (P1.z - P2.z) * (P1.z - P2.z)));
    }

    // returneaza 1 atunci cand exista coliziune. Primeste offset ul pe verticala al 
    //obiectului care se misca
    int checkCollision(float y_off) {

    	Point C1, C2;
		C1 = findCenter(verticesbox, 0);
		C2 = findCenter(verticesbunny, y_off);
		float distance = getDistance(C1,C2);
		float sphereDistance = float((Rbox+Rbunny)/2);

        if (distance > sphereDistance){
        	return 0;
        }
        return 1;
    }
	
	int checkCollisionT(float y_off) {

		glm::vec3 v[3], u[3];

		for (int i = 0; i < verticesbox.size() / 3; i++)
			for (int j = i + 1; j < verticesbox.size() / 3; j++)
				for (int k = j + 1; k < verticesbox.size() / 3; k++) {
					v[0] = glm::vec3(verticesbunny[4].position_x, verticesbunny[4].position_y + y_off, verticesbunny[4].position_z);
					v[1] = glm::vec3(verticesbunny[5].position_x, verticesbunny[5].position_y + y_off, verticesbunny[5].position_z);
					v[2] = glm::vec3(verticesbunny[7].position_x, verticesbunny[7].position_y + y_off, verticesbunny[7].position_z);
					u[0] = glm::vec3(verticesbox[i].position_x, verticesbox[i].position_y, verticesbox[i].position_z);
					u[1] = glm::vec3(verticesbox[j].position_x, verticesbox[j].position_y, verticesbox[j].position_z);
					u[2] = glm::vec3(verticesbox[k].position_x, verticesbox[k].position_y, verticesbox[k].position_z);
					if (TriangleToTriangleIntersection(v, u))
						return 1;
				}

		return 0;
	}

	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){

		if (mode == SPHERE) {
			if (checkCollision(y_off_bunny) == 1)
				direction = 1;
		}
		else {
			if (checkCollisionT(y_off_bunny) == 1)
				direction = 1;
		}
		
		if (findCenter(verticesbunny, y_off_bunny).y > 100.0f){
			direction = -1; // down
		}

		y_off_bunny += direction * speed;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//deseneaza cub
		glUseProgram(shader_normal);
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "view_matrix"), 1, false, glm::value_ptr(camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "model_matrix"), 1, false, glm::value_ptr(glm::mat4(1)));
		glActiveTexture(GL_TEXTURE0+1);
		glUniform1i(glGetUniformLocation(shader_normal, "objNo"), 1);
		glBindTexture(GL_TEXTURE_2D, texture_cubemap);
        glUniform1i(glGetUniformLocation(shader_normal, "textura_cubemap"), 1);
        mesh_cubemap.Bind();
        mesh_cubemap.Draw();

        //deseneaza obiectul reflectant
        glUseProgram(shader_normal);
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "view_matrix"), 1, false, glm::value_ptr(camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
        glUniformMatrix4fv(glGetUniformLocation(shader_normal, "model_matrix"), 1, false, glm::value_ptr(glm::mat4(1)));
        glActiveTexture(GL_TEXTURE0 + 1);
    //  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cubemap);
     // glUniform1i(glGetUniformLocation(shader_normal, "textura_cubemap"), 1);
        glUniform1i(glGetUniformLocation(shader_normal, "objNo"), 0);
        glUniform1f(glGetUniformLocation(shader_normal, "x_off_bunny"), x_off_bunny);
        glUniform1f(glGetUniformLocation(shader_normal, "y_off_bunny"), y_off_bunny);
        glUniform1f(glGetUniformLocation(shader_normal, "z_off_bunny"), z_off_bunny);
        mesh_bunny.Bind();
        mesh_bunny.Draw();
	}

	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		float aspect = (float)width / (float)height;
		glViewport(0,0,width,height);
		projection_matrix = glm::perspective(75.0f, aspect,0.1f, 10000.0f);
	}


	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
        if (key_pressed == 32) {
            //SPACE reincarca shaderul si recalculeaza locatiile (offseti/pointeri)
            
            glDeleteProgram(shader_normal);
            shader_normal = lab::loadShader("shadere/normal_vertex.glsl", "shadere/normal_fragment.glsl");
   
        }
        if (key_pressed == 'w') camera.translateForward(1.0f);
        if (key_pressed == 'a') camera.translateRight(-1.0f);
        if (key_pressed == 's') camera.translateForward(-1.0f);
        if (key_pressed == 'd') camera.translateRight(1.0f);
        if (key_pressed == 'q') camera.rotateFPSoY(1.0f);
        if (key_pressed == 'e') camera.rotateFPSoY(-1.0f);
        if (key_pressed == 'r') camera.translateUpword(1.0f);
        if (key_pressed == 'f') camera.translateUpword(-1.0f);
		if (key_pressed == 'm') {
			mode = !mode;
			std::cout << "MOD " << ((mode == SPHERE) ? "Sphere" : "Triangle-To-Triangle") << std::endl;
		}
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y){ }
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y){ }
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){ }
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ }

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("lab 4 - cubemaps"),800,600,100,100,true);
	lab::glut::ContextInfo context(3,0,false);
	lab::glut::FramebufferInfo framebuffer(true,true,true,true);
	lab::glut::init(window,context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Laborator mylab;
	lab::glut::setListener(&mylab);

	//taste
    std::cout << "Taste:" << std::endl << "\tESC ... iesire" << std::endl << "\tSPACE ... reincarca shadere" << std::endl;

	//run
	lab::glut::run();

	return 0;
}