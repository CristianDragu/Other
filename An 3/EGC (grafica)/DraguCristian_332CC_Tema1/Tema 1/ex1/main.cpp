//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: Dragu Cristian
// Data: today
//-------------------------------------------------------------------------------------------------

#include "..\\dependente\glew\glew.h"
#include "..\\dependente\glm\glm.hpp"
#include "..\\dependente\glm\gtc\type_ptr.hpp"
#include "..\\dependente\glm\gtc\matrix_transform.hpp"

#include "..\\lab_blackbox.hpp"

#include "..\\lab_glut.hpp"

#include <ctime>

#include <iostream>

class Lab : public lab::glut::WindowListener{

	class Rectangles {
		
	public:

		std::pair<float, float> p0;
		std::pair<float, float> p1;

		Rectangles() {
			p0 = std::pair<float, float>(0, 0);
			p1 = std::pair<float, float>(0, 0);
		}

		Rectangles(std::pair<float, float> p0, std::pair<float, float> p1) {
			this->p0 = p0;
			this->p1 = p1;
		}
	};

	class Color {
		
	public:
			float r, g, b;

			Color(float r, float g, float b) {
				this->r = r;
				this->g = g;
				this->b = b;
			}

			Color() {
				r = 1;
				g = 1;
				b = 0;
			}
	};

private:
	lab::BlackBox BLACKBOX;

	lab::Mesh *sursa;
	lab::Mesh *obiect1;
	lab::Mesh *obiect3;
	lab::Mesh *raza[20];
	lab::Mesh *oglinda;
	lab::Mesh *obiecte[10];
	std::vector<Rectangles> dreptunghiuri;
	glm::mat3 transformation[21];
	Color culoareRaza[20];
	Color culoareObiecte[10];
	GLubyte pick_col[3];
	
	std::pair<float, float> varf;
	float xsursa, ysursa, xbaza, ybaza, rotatie, lungimeRaza;
	int sem = 0, end = 0;
	unsigned int width, height, numarRaze;
	
public:

	Lab(){

		width = lab::glut::getInitialWindowInformation().width;
		height = lab::glut::getInitialWindowInformation().height;

		sursa = myLoadCircle_as_Mesh(250, 400, 15, 100);
		raza[0] = myLoadSquare_as_Mesh(250, 397, 6);
		oglinda = myLoadTriangle_as_Mesh(width - 20, height - 30, 100);

		//obstacole
		obiecte[0] = myLoadRectangle_as_Mesh(650, 200, 100, 50);
		obiecte[1] = myLoadRectangle_as_Mesh(400, 150, 50, 100);
		obiecte[2] = myLoadRectangle_as_Mesh(10, 10, 50, 150);
		obiecte[3] = myLoadRectangle_as_Mesh(60, 10, 100, 50);
		obiecte[4] = myLoadRectangle_as_Mesh(160, 10, 40, 300);
		obiecte[5] = myLoadRectangle_as_Mesh(670, 350, 80, 40);
		obiecte[6] = myLoadRectangle_as_Mesh(300, 470, 50, 100);
		obiecte[7] = myLoadRectangle_as_Mesh(770, 10, 200, 50);
		obiecte[8] = myLoadRectangle_as_Mesh(920, 60, 50, 200);
		obiecte[9] = myLoadRectangle_as_Mesh(50, 470, 50, 100);

		//culori random date obstacolelor
		srand(time(NULL));
		for (int i = 0; i < 10; i++) {
			obiecte[i]->setColor((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);
		}

		xsursa = 250;
		xbaza = xsursa;
		ysursa = 400;
		ybaza = ysursa;
		varf = std::pair<float, float>(xsursa, ysursa);

		rotatie = 0;
		lungimeRaza = 6.0f;
		numarRaze = 1;

		culoareRaza[0] = Color(1, 1, 0);
		
		for (unsigned int i = 0; i < 21; i++) 
			transformation[i] = glm::mat3(1);
		
		sem = 0;
	}

	~Lab(){
		delete sursa;
		delete obiect3;
		delete obiect1;
	}

	struct MyVertexFormat{
		glm::vec2 pozitie;
		MyVertexFormat(){
			pozitie = glm::vec2(0, 0);
		}
		MyVertexFormat(float px, float py){
			pozitie = glm::vec2(px, py);
		}
		MyVertexFormat operator=(const MyVertexFormat &rhs){
			pozitie = rhs.pozitie;
			return (*this);
		}
	};

	lab::Mesh* myLoadRectangle_as_Mesh(float x, float y, float laturax, float laturay) {
		//definim containere pentru date
		std::vector<MyVertexFormat> vertecsi;
		std::vector<glm::uvec3> indecsi;

		//4 vertecsi (doar pozitii fara normale fara texcoords)
		vertecsi.push_back(MyVertexFormat(x, y));
		vertecsi.push_back(MyVertexFormat(x + laturax, y));
		vertecsi.push_back(MyVertexFormat(x + laturax, y + laturay));
		vertecsi.push_back(MyVertexFormat(x, y + laturay));

		dreptunghiuri.push_back(Rectangles(std::pair<float, float>(x, y), 
											std::pair<float, float>(x + laturax, y + laturay)));

		//2 triunghiuri pentru 1 fata
		indecsi.push_back(glm::uvec3(0, 1, 2));
		indecsi.push_back(glm::uvec3(2, 3, 0));

		//creaza vao
		unsigned int mesh_vao;
		glGenVertexArrays(1, &mesh_vao);
		glBindVertexArray(mesh_vao);

		//creeaza vbo
		unsigned int mesh_vbo;
		glGenBuffers(1, &mesh_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

		//creeaza ibo
		unsigned int mesh_ibo;
		glGenBuffers(1, &mesh_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

		//creez obiect de tip mesh
		lab::Mesh* mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

		// traducem la OpenGL cum sa foloseasca datele noastre
		BLACKBOX.bindMesh(mesh, sizeof(MyVertexFormat));

		//return
		return mesh;
	}

	lab::Mesh* myLoadSquare_as_Mesh(float x, float y, float latura){
		//definim containere pentru date
		std::vector<MyVertexFormat> vertecsi;
		std::vector<glm::uvec3> indecsi;

		//4 vertecsi (doar pozitii fara normale fara texcoords)
		vertecsi.push_back(MyVertexFormat(x, y));
		vertecsi.push_back(MyVertexFormat(x + latura, y));
		vertecsi.push_back(MyVertexFormat(x + latura, y + latura));
		vertecsi.push_back(MyVertexFormat(x , y + latura));
		
		//2 triunghiuri pentru 1 fata
		indecsi.push_back(glm::uvec3(0, 1, 2));	
		indecsi.push_back(glm::uvec3(2, 3, 0));

		//creaza vao
		unsigned int mesh_vao;
		glGenVertexArrays(1, &mesh_vao);
		glBindVertexArray(mesh_vao);

		//creeaza vbo
		unsigned int mesh_vbo;
		glGenBuffers(1, &mesh_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

		//creeaza ibo
		unsigned int mesh_ibo;
		glGenBuffers(1, &mesh_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

		//creez obiect de tip mesh
		lab::Mesh* mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

		// traducem la OpenGL cum sa foloseasca datele noastre
		BLACKBOX.bindMesh(mesh, sizeof(MyVertexFormat));

		//return
		return mesh;
	}

	lab::Mesh* myLoadTriangle_as_Mesh(float x, float y, float latura) {
		//definim containere pentru date
		std::vector<MyVertexFormat> vertecsi;
		std::vector<glm::uvec3> indecsi;

		//4 vertecsi (doar pozitii fara normale fara texcoords)
		vertecsi.push_back(MyVertexFormat(x, y));
		vertecsi.push_back(MyVertexFormat(x - latura, y));
		vertecsi.push_back(MyVertexFormat(x, y - latura));

		//2 triunghiuri pentru 1 fata
		indecsi.push_back(glm::uvec3(0, 1, 2));

		//creaza vao
		unsigned int mesh_vao;
		glGenVertexArrays(1, &mesh_vao);
		glBindVertexArray(mesh_vao);

		//creeaza vbo
		unsigned int mesh_vbo;
		glGenBuffers(1, &mesh_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

		//creeaza ibo
		unsigned int mesh_ibo;
		glGenBuffers(1, &mesh_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

		//creez obiect de tip mesh
		lab::Mesh* mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

		// traducem la OpenGL cum sa foloseasca datele noastre
		BLACKBOX.bindMesh(mesh, sizeof(MyVertexFormat));

		//return
		return mesh;
	}

	lab::Mesh* myLoadCircle_as_Mesh(float cx, float cy, float r, int num_segments)
	{
		std::vector<MyVertexFormat> vertecsi;
		std::vector<glm::uvec3> indecsi;

		float theta = 2 * 3.1415926 / float(num_segments);
		float c = cosf(theta);//precalculate the sine and cosine
		float s = sinf(theta);
		float t;

		float x = r;//we start at angle = 0 
		float y = 0;

		for (int ii = 0; ii < num_segments; ii++) {
			vertecsi.push_back(MyVertexFormat(x + cx, y + cy));
			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}

		for (int ii = 1; ii < num_segments - 1; ii++)
			indecsi.push_back(glm::uvec3(0, ii, ii + 1));

		//creaza vao
		unsigned int mesh_vao;
		glGenVertexArrays(1, &mesh_vao);
		glBindVertexArray(mesh_vao);

		//creeaza vbo
		unsigned int mesh_vbo;
		glGenBuffers(1, &mesh_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

		//creeaza ibo
		unsigned int mesh_ibo;
		glGenBuffers(1, &mesh_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

		//creez obiect de tip mesh
		lab::Mesh* mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

		// traducem la OpenGL cum sa foloseasca datele noastre
		BLACKBOX.bindMesh(mesh, sizeof(MyVertexFormat));

		//return
		return mesh;
	}

	//--------------------------------------------------------------------------------------------
	//functii de transformare --------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------
	glm::mat3 myIdentity(){
		return glm::transpose(glm::mat3(	//de ce? pt ca in memorie se scriu coloane dar in IDE le vezi ca randuri
			1, 0, 0,						//asa le vezi ca randuri si le scrii ca randuri!
			0, 1, 0,
			0, 0, 1
			));
	}
	glm::mat3 myTranslate(float tx, float ty) {
		return glm::transpose(glm::mat3(
			1, 0, tx,
			0, 1, ty,
			0, 0, 1
			));
	}
	glm::mat3 myRotate(float u) {
		return glm::transpose(glm::mat3(
			cos(u), -sin(u), 0,
			sin(u), cos(u), 0,
			0, 0, 1
			));
	}
	glm::mat3 myScale(float sx, float sy) {
		return glm::transpose(glm::mat3(
			sx, 0, 0,
			0, sy, 0,
			0, 0, 1
			));
	}

	void init_variabile() {
		if (numarRaze > 1)
			rotatie = 0;
		for (int i = 0; i < numarRaze; i++) {
			delete raza[i];
			transformation[i + 1] = myIdentity();
		}
		raza[0] = myLoadSquare_as_Mesh(250, 397, 6);
		transformation[1] = myIdentity();
		lungimeRaza = 6;
		numarRaze = 1;
		xbaza = xsursa;
		ybaza = ysursa;
		varf = std::pair<float, float>(xsursa, ysursa);
		culoareRaza[0] = Color();
		end = 0;
	}

	void cercTrigonometric() {
		if (rotatie > 2.0f * 3.14159)
			rotatie = rotatie - 2.0f * 3.14159;
		if (rotatie < 0)
			rotatie = 2.0f * 3.14159 + rotatie;
	}

	void nextRay() {
		raza[numarRaze++] = myLoadSquare_as_Mesh(varf.first, varf.second - 3, 6);
		xbaza = varf.first;
		ybaza = varf.second;
		lungimeRaza = 6;
		transformation[numarRaze] *= myTranslate(xbaza, ybaza)*myRotate(rotatie)*myTranslate(-xbaza, -ybaza);
		varf.first = std::cos(rotatie) * lungimeRaza + xbaza;
		varf.second = std::sin(rotatie) * lungimeRaza + ybaza;
	}

	void notifyBeginFrame(){}

	void notifyDisplayFrame(){
		glClear(GL_COLOR_BUFFER_BIT);
		BLACKBOX.notifyDisplay();

		width = lab::glut::getInitialWindowInformation().width;
		height = lab::glut::getInitialWindowInformation().height;

		//glScissor((1/100.0) * width, (1/60.0) * height, width - (3/100.0) * width, height - (1/20.0) * height);
		glScissor(10, 10, 960, 560);
		glEnable(GL_SCISSOR_TEST);
		glClearColor(0, 0, 0, 0);

		glClearColor(0.9, 0.9, 0.9, 0);

		sursa->setColor(1, 1, 0); // sursa
		BLACKBOX.setModelMatrix(transformation[0]);
		BLACKBOX.drawMesh(sursa, 1);

		//raze
		for (int i = numarRaze - 1; i >= 0; i--) {
			raza[i]->setColor(culoareRaza[i].r, culoareRaza[i].g, culoareRaza[i].b);
			BLACKBOX.setModelMatrix(transformation[i + 1]);
			BLACKBOX.drawMesh(raza[i], 1);
		}

		oglinda->setColor(0, 0, 0);
		BLACKBOX.setModelMatrix(transformation[0]);
		BLACKBOX.drawMesh(oglinda, 1);

		//obiecte
		for (int i = 0; i < 10; i++) {
			BLACKBOX.setModelMatrix(transformation[0]);
			BLACKBOX.drawMesh(obiecte[i], 1);
		}

	}

	void notifyEndFrame() {
		if(end == 0)
			if (varf.second < 570 && varf.second > 10 && varf.first < 970 && varf.first > 10 && numarRaze <= 20) {
				sem = 0;
				for (unsigned int i = 0; i < dreptunghiuri.size(); i++) {
					if (dreptunghiuri.at(i).p0.second <= varf.second && varf.second <= dreptunghiuri.at(i).p1.second && dreptunghiuri.at(i).p0.first <= varf.first && varf.first <= dreptunghiuri.at(i).p1.first)
						if(std::abs(varf.first - dreptunghiuri.at(i).p0.first) < 2 || std::abs(varf.first - dreptunghiuri.at(i).p1.first) < 2){
							if (numarRaze >= 20) {
								end = 1;
								break;
							}
							rotatie = 3.14159 - rotatie;
							cercTrigonometric();
							nextRay();
							glReadPixels(dreptunghiuri.at(i).p0.first, dreptunghiuri.at(i).p0.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pick_col[0]);
							culoareRaza[numarRaze - 1] = Color((culoareRaza[numarRaze - 2].r + pick_col[0] / 255.0f) / 2, (culoareRaza[numarRaze - 2].g + pick_col[1] / 255.0f) / 2, (culoareRaza[numarRaze - 2].b + pick_col[2] / 255.0f) / 2);
							sem = 1;
							break;
						}
						else if (std::abs(varf.second - dreptunghiuri.at(i).p0.second) < 3 || std::abs(varf.second - dreptunghiuri.at(i).p1.second) < 3) {
							if (numarRaze >= 20) {
								end = 1;
								break;
							}
							rotatie = 2.0f * 3.14159 - rotatie;
							cercTrigonometric();
							nextRay();
							glReadPixels(dreptunghiuri.at(i).p0.first, dreptunghiuri.at(i).p0.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pick_col[0]);
							culoareRaza[numarRaze - 1] = Color((culoareRaza[numarRaze - 2].r + pick_col[0] / 255.0f) / 2, (culoareRaza[numarRaze - 2].g + pick_col[1] / 255.0f) / 2, (culoareRaza[numarRaze - 2].b + pick_col[2] / 255.0f) / 2);
							sem = 1;
							break;
						}
				}
				if(sem == 0){
					transformation[numarRaze] *= myTranslate(xbaza, ybaza)*myScale(1.002f, 1.0f)*myTranslate(-xbaza, -ybaza);
					lungimeRaza = lungimeRaza * 1.002f;
					varf.first = std::cos(rotatie) * lungimeRaza + xbaza;
					varf.second = std::sin(rotatie) * lungimeRaza + ybaza;
					if (varf.first >= 880 && varf.second >= 470 && varf.second - 470 >= -varf.first + 880 + 100)
						end = 1;
				}
			}
			else {
				if ((varf.second >= 570 || varf.second <= 10) && (varf.first >= 10 || varf.first <= 970) && numarRaze < 20) {
					rotatie = 2.0f * 3.14159 - rotatie;
					cercTrigonometric();
					nextRay();
					culoareRaza[numarRaze - 1] = Color(culoareRaza[numarRaze - 2].r / 2, culoareRaza[numarRaze - 2].g / 2, culoareRaza[numarRaze - 2].b / 2);
				}
				else if ((varf.first <= 10 || varf.first >= 970) && (varf.second <= 570 || varf.second >= 10) && numarRaze < 20) {
					rotatie = 3.14159 - rotatie;
					cercTrigonometric();
					nextRay();
					culoareRaza[numarRaze - 1] = Color(culoareRaza[numarRaze - 2].r / 2, culoareRaza[numarRaze - 2].g / 2, culoareRaza[numarRaze - 2].b / 2);
				}
			}
	}

	void notifyReshape(int width, int height, int previos_width, int previous_height){
		BLACKBOX.notifyReshape(width,height);
	}

	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();
		if (key_pressed == '6') {
			transformation[1] *= myTranslate(xsursa, ysursa)*myScale(1.03f, 1.0f)*myTranslate(-xsursa, -ysursa);
		}
		if (key_pressed == 'w') {
			init_variabile();
			rotatie += 0.1;
			cercTrigonometric();
			transformation[1] *= myTranslate(xsursa, ysursa)*myRotate(rotatie)*myTranslate(-xsursa, -ysursa);
		}
		if (key_pressed == 's') {
			init_variabile();
			rotatie -= 0.1;
			cercTrigonometric();
			transformation[1] *= myTranslate(xsursa, ysursa)*myRotate(rotatie)*myTranslate(-xsursa, -ysursa);
		}
		
	}

	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
	}

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("Lab EGC 3 - transformari"),1000,600,300,50,true);
	lab::glut::ContextInfo context(3,3,false);
	lab::glut::FramebufferInfo framebuffer(true,true,false,false);
	lab::glut::init(window, context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//_DUPA_ GLEW ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Lab mylab;
	lab::glut::setListener(&mylab);

	lab::glut::run();

	return 0;
}