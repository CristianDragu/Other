//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//incarcator de meshe
#include "lab_mesh_loader.hpp"
//incarcator de shadere
#include "lab_shader_loader.hpp"
//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"
//time, min
#include <ctime>
#include <algorithm>

#define CREATE_MODE 0
#define EDIT_MODE 1
#define BEZIER 0
#define HERMITE 1
#define BSPLINE 2
#define NURBS 3
#define SPLINE 4

class Laborator : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 model_matrix, view_matrix, projection_matrix;								//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int program_shader;														//id-ul de opengl al obiectului de tip program shader
	lab::Mesh* mesh;

	//informatii suprafata generate
	glm::vec3 control_p1, control_p2, control_p3, control_p4;
	std::vector<glm::vec4> control_p;
	unsigned int num_puncte_generate, num_instante, nr_points, mode = EDIT_MODE, tipCurba = BEZIER, rotate = 0;
	float max_translate, max_rotate;
	int pointClicked = -1;

//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		program_shader = lab::loadShader("shadere\\vertex.glsl","shadere\\geometry.glsl", "shadere\\fragment.glsl");
		
		//matrici de modelare si vizualizare
		model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(glm::vec3(0,10,75), glm::vec3(0,10,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//creaza mesha
		num_puncte_generate = 10;
		num_instante = 5;
		max_translate = 80.0f;
		nr_points = 0;
		max_rotate = glm::radians(360.0f);
		mesh = NULL;
		mesh = generateMesh();
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shader
		glDeleteProgram(program_shader);

		//distruge mesh incarcat
		delete mesh;
	}


	//--------------------------------------------------------------------------------------------
	//functie de constructie mesha generata-------------------------------------------------------
	lab::Mesh* generateMesh(){
		//distruge daca exista
		if (mesh) delete mesh;

		//defineste punctele de control
		control_p1 = glm::vec3(-40, -25, 10);	
		control_p2 = glm::vec3(-25,	15,	10);		
		control_p3 = glm::vec3(-15,	30,	10);		
		control_p4 = glm::vec3(-40,	55,	10);

		control_p.push_back(glm::vec4(control_p1.x, control_p1.y, control_p1.z, 1));
		control_p.push_back(glm::vec4(control_p2.x, control_p2.y, control_p2.z, 1));
		control_p.push_back(glm::vec4(control_p3.x, control_p3.y, control_p3.z, 1));
		control_p.push_back(glm::vec4(control_p4.x, control_p4.y, control_p4.z, 1));
		nr_points = 4;

		//date mesh
		std::vector<lab::VertexFormat> vertices;
		vertices.push_back(lab::VertexFormat(-40, -25, 10));
		vertices.push_back(lab::VertexFormat(-40, 55, 10));
		std::vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);

		//obiecte OpenGL mesh
		unsigned int vbo, ibo, vao;
		glGenVertexArrays(1 , &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,sizeof(lab::VertexFormat)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);
		return new lab::Mesh(vbo, ibo, vao, indices.size());
	}
	
	float distance(glm::vec4 p, int x, int y) {
		return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	}

	float get_X(float x) {
		return (x - 160.0) / 6.0 + (-40);
	}
	
	float get_Y(float y) {
		return (y - 18) / (-6) + 55;
	}

	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){
		
		//pe tot ecranul
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//foloseste shaderul
		glUseProgram(program_shader);
				
		//trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(program_shader,"view_matrix"),1,false,glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(program_shader,"projection_matrix"),1,false,glm::value_ptr(projection_matrix));
		if(nr_points > 0)
			glUniform4fv(glGetUniformLocation(program_shader,"control_p"),control_p.size(), glm::value_ptr(control_p[0]));
		glUniform1i(glGetUniformLocation(program_shader, "nr_control_p"), nr_points);
		glUniform1i(glGetUniformLocation(program_shader, "tipCurba"), tipCurba);
		glUniform1i(glGetUniformLocation(program_shader,"num_puncte_generate"),num_puncte_generate);
		glUniform1i(glGetUniformLocation(program_shader,"num_instante"),num_instante);
		glUniform1f(glGetUniformLocation(program_shader,"max_translate"),max_translate);
		glUniform1f(glGetUniformLocation(program_shader,"max_rotate"),max_rotate);
		glUniform1i(glGetUniformLocation(program_shader, "rotate"), rotate);
		
		mesh->drawInstanced(num_instante);
	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){
	}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height) {
		//reshape
		if (height == 0) height = 1;
		glViewport(0, 0, width, height);
		float aspect = (float)width / (float)height;
		projection_matrix = glm::perspective(75.0f, aspect, 0.1f, 10000.0f);
	}

	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
		if(key_pressed == 32) {
			//SPACE reincarca shaderul si recalculeaza locatiile (offseti/pointeri)
			glDeleteProgram(program_shader);
			program_shader = lab::loadShader("shadere\\vertex.glsl", "shadere\\geometry.glsl", "shadere\\fragment.glsl");
		}
		if(key_pressed == '1'){
			if(num_puncte_generate <50) num_puncte_generate++;
			std::cout<<"Numarul de puncte generate = "<<num_puncte_generate <<std::endl;
		}
		if(key_pressed == '2'){
			if (num_puncte_generate >4) num_puncte_generate--;
			std::cout<<"Numarul de puncte generate = "<<num_puncte_generate <<std::endl;
		}
		if(key_pressed == '3'){
			if (num_instante < 50) num_instante++;
			std::cout << "Numarul de instante = " << num_instante << std::endl;
		}
		if(key_pressed == '4'){
			if (num_instante > 2) num_instante--;
			std::cout << "Numarul de instante = " << num_instante << std::endl;
		}
		if (key_pressed == 'q') {
			std::cout << "CHANGED TO CREATE MODE\n";
			mode = CREATE_MODE;
		}
		if (key_pressed == 'w') {
			std::cout << "CHANGED TO EDIT MODE\n";
			mode = EDIT_MODE;
		}
		if (key_pressed == 'b') {
			tipCurba = BEZIER;
		}
		if (key_pressed == 'h') {
			tipCurba = HERMITE;
		}
		if (key_pressed == 's') {
			tipCurba = SPLINE;
		}
		if (key_pressed == 'S') {
			tipCurba = BSPLINE;
		}
		if (key_pressed == 'n') {
			tipCurba = NURBS;
		}
		if (key_pressed == 'r') {
			rotate = (rotate + 1) % 2;
			std::cout << "Rotatie == " << rotate << std::endl;
		}
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){ }
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y){
		if (pointClicked != -1) {
			control_p.at(pointClicked).x = get_X(mouse_x);
			control_p.at(pointClicked).y = get_Y(mouse_y);
		}
	}
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y){	}
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y) {

		if (button == 0 && state == 0 && mode == EDIT_MODE) {
			for (int i = 0; i < control_p.size(); i++) {
				if (distance(control_p.at(i), get_X(mouse_x), get_Y(mouse_y)) < 5.0) {
					pointClicked = i;
					break;
				}
			}
		}

		if (button == 0 && state == 1 && mode == EDIT_MODE) {
			std::cout << "Am dat drumul la butonul de drag\n";
			pointClicked = -1;
		}

		if (button == 0 && state == 1 && mode == CREATE_MODE) {
			control_p.push_back(glm::vec4(get_X(mouse_x), get_Y(mouse_y), 10, 1));
			nr_points++;
			std::cout << "Point added\n";
		}

		if(button == 2 && state == 1 && mode == CREATE_MODE){
			std::cout << "rip date\n";
			control_p.clear();
			nr_points = 0;
		}
	}
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ std::cout<<"Mouse scroll"<<std::endl;}

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("lab shadere 2 - suprafete de baleiere"),800,600,100,100,true);
	lab::glut::ContextInfo context(3,3,false);
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
	std::cout<<"Taste:"<<std::endl<<"\tESC ... iesire"<<std::endl<<"\tSPACE ... reincarca shadere"<<std::endl;
	std::cout<<"\t1 ... creste numar puncte generate"<<std::endl<<"\t2 ... scade numar puncte generate"<<std::endl;
	std::cout<<"\t3 ... creste numar instante"<<std::endl<<"\t4 ... scade numar instante"<<std::endl;


	//run
	lab::glut::run();

	return 0;
}