//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//incarcator de meshe
#include "lab_mesh_loader.hpp"

//geometrie: drawSolidCube, drawWireTeapot...
#include "lab_geometry.hpp"

//incarcator de shadere
#include "lab_shader_loader.hpp"

//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"

//time
#include <ctime>

#include "lab_camera.hpp"

class Laborator : public lab::glut::WindowListener{

	class Puncte {
	public:
		float x, z;
		Puncte() {
			this->x = 0.0f;
			this->z = 0.0f;
		}
		Puncte(float x, float z) {
			this->x = x;
			this->z = z;
		}
	};

	class Unda {
	public:
		int eCirculara;
		float amplitudine, lungimeUnda, s;
		glm::vec2 directie;

		Unda() {
			eCirculara = 0;
			amplitudine = 0.0f;
			lungimeUnda = 0.0f;
			s = 0.0f;
			directie = glm::vec2(0.0f, 0.0f);
		}

		Unda(int eCirculara, float amplitudine, float lungimeUnda, float s, glm::vec2 directie) {
			this->eCirculara = eCirculara;
			this->amplitudine = amplitudine;
			this->lungimeUnda = lungimeUnda;
			this->s = s;
			this->directie = directie;
		}
	};

private:
	glm::mat4 model_matrix, view_matrix, projection_matrix;										//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int gl_program_shader_gouraud;														//id obiect shader gouraud

	unsigned int mesh_vbo_model, mesh_ibo_model, mesh_vao_model, mesh_num_indices_model;		//containere opengl pentru vertecsi, indecsi si stare pentru modelul incarcat

	unsigned int mesh_vbo_sphere, mesh_ibo_sphere, mesh_vao_sphere, mesh_num_indices_sphere;	//containere opengl pentru vertecsi, indecsi si stare pentru sfera ce va fi pusa la pozitia luminii

	unsigned int mesh_vbo_ground, mesh_ibo_ground, mesh_vao_ground, mesh_num_indices_ground;	//containere opengl pentru vertecsi, indecsi si stare pentru sol

	glm::vec3 light_position;
	glm::vec3 eye_position;
	unsigned int material_shininess;
	float material_kd;
	float material_ks;
	clock_t end_time;
	Unda sinusoida[3];
	lab::Camera camera;
	int notifier = 0;

//metode
public:

	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader_gouraud = lab::loadShader("shadere\\shader_gouraud_vertex.glsl", "shadere\\shader_gouraud_fragment.glsl");
		
		//incarca un mesh
		//lab::loadObj("resurse\\sphere.obj",mesh_vao_model, mesh_vbo_model, mesh_ibo_model, mesh_num_indices_model);	

		//incarca o sfera
		lab::loadObj("resurse\\sphere.obj",mesh_vao_sphere, mesh_vbo_sphere, mesh_ibo_sphere, mesh_num_indices_sphere);	

		//incarca un plan
		lab::loadObj("resurse\\plane1.obj",mesh_vao_ground, mesh_vbo_ground, mesh_ibo_ground, mesh_num_indices_ground);	

		//lumina & material
		light_position = glm::vec3(10,30,25);
		material_shininess = 30;
		material_kd = 0.5;
		material_ks = 0.5;

		sinusoida[0] = Unda(0, 0.5f, 10.0f, 3.0f, glm::vec2(1.0f, 1.0f));
		sinusoida[1] = Unda(0, 2.0f, 20.0f, 3.0f, glm::vec2(0.0f, 1.0f));
		sinusoida[2] = Unda(1, 1.0f, 20.0f, 3.0f, glm::vec2(50.0f, 50.0f));
		
		glUseProgram(gl_program_shader_gouraud);

		glUniform1i(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[0].eCirculara"), sinusoida[0].eCirculara);
		glUniform1i(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[1].eCirculara"), sinusoida[1].eCirculara);
		glUniform1i(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[2].eCirculara"), sinusoida[2].eCirculara);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[0].amplitudine"), sinusoida[0].amplitudine);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[1].amplitudine"), sinusoida[1].amplitudine);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[2].amplitudine"), sinusoida[2].amplitudine);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[0].lungimeUnda"), sinusoida[0].lungimeUnda);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[1].lungimeUnda"), sinusoida[1].lungimeUnda);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[2].lungimeUnda"), sinusoida[2].lungimeUnda);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[0].s"), sinusoida[0].s);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[1].s"), sinusoida[1].s);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[2].s"), sinusoida[2].s);
		glUniform2f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[0].directie"), sinusoida[0].directie[0], sinusoida[0].directie[1]);
		glUniform2f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[1].directie"), sinusoida[1].directie[0], sinusoida[1].directie[1]);
		glUniform2f(glGetUniformLocation(gl_program_shader_gouraud, "sinusoida[2].directie"), sinusoida[2].directie[0], sinusoida[2].directie[1]);

		camera.set(glm::vec3(50, 10, 80), glm::vec3(50, 0, 50), glm::vec3(0, 1, 0));

		//matrici de modelare si vizualizare
		model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(camera.getPosition(), glm::vec3(50, 0, 10), glm::vec3(0, 1, 0));
		projection_matrix = glm::perspective(90.0f, (float)800 / (float)600, 0.1f, 10000.0f);
		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shader
		glDeleteProgram(gl_program_shader_gouraud);

		//distruge mesh incarcat
		glDeleteBuffers(1,&mesh_vbo_model);
		glDeleteBuffers(1,&mesh_ibo_model);
		glDeleteVertexArrays(1,&mesh_vao_model);

		//distruge sfera
		glDeleteBuffers(1,&mesh_vbo_sphere);
		glDeleteBuffers(1,&mesh_ibo_sphere);
		glDeleteVertexArrays(1,&mesh_vao_sphere);

		//distruge solul
		glDeleteBuffers(1,&mesh_vbo_ground);
		glDeleteBuffers(1,&mesh_ibo_ground);
		glDeleteVertexArrays(1,&mesh_vao_ground);
	}

	glm::vec2 diferentaVectori(glm::vec2 v1, glm::vec2 v2) {
		return glm::vec2(std::abs(v1.x - v2.x), std::abs(v1.y - v2.y));
	}

	double diffclock(clock_t clock1, clock_t clock2)
	{
		double diffticks = clock1 - clock2;
		double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
		return diffms;
	}

	double timp(clock_t clock1) {
		return ((double)clock1) / (CLOCKS_PER_SEC);
	}

	void notifyBeginFrame(){

	}

	void notifyDisplayFrame(){
		//bufferele din framebuffer sunt aduse la valorile initiale (setate de clear color si cleardepth)
		//adica se sterge ecranul si se pune culoare (si alte propietati) initiala
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//foloseste shaderul
		glUseProgram(gl_program_shader_gouraud);
		
		view_matrix = camera.getViewMatrix();
		
		end_time = clock();

		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_gouraud, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_gouraud, "view_matrix"), 1, false, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_gouraud, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
		glUniform3f(glGetUniformLocation(gl_program_shader_gouraud, "light_position"), light_position.x, light_position.y, light_position.z);
		glUniform3f(glGetUniformLocation(gl_program_shader_gouraud, "eye_position"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		glUniform1i(glGetUniformLocation(gl_program_shader_gouraud, "material_shininess"), material_shininess);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "material_kd"), material_kd);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "material_ks"), material_ks);
		glUniform1f(glGetUniformLocation(gl_program_shader_gouraud, "end_time"), (float)timp(end_time));

		//desenare obiect
		//glBindVertexArray(mesh_vao_model);
		//glDrawElements(GL_TRIANGLES, mesh_num_indices_model, GL_UNSIGNED_INT, 0);	

		//pune o sfera la pozitia luminii
		glm::mat4 matrice_translatie = glm::translate(model_matrix, glm::vec3(light_position.x,light_position.y,light_position.z));
		glm::mat4 matrice_scalare = glm::scale(model_matrix, glm::vec3(0.1,0.1,0.1));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_gouraud, "model_matrix"),1,false,glm::value_ptr(matrice_translatie * matrice_scalare));
		
		glBindVertexArray(mesh_vao_sphere);
		glDrawElements(GL_TRIANGLES, mesh_num_indices_sphere, GL_UNSIGNED_INT, 0);

		//pune si un sol
		matrice_translatie = glm::translate(model_matrix, glm::vec3(0,-10,-20));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_gouraud, "model_matrix"),1,false,glm::value_ptr(matrice_translatie));

		glBindVertexArray(mesh_vao_ground);
		glDrawElements(GL_TRIANGLES, mesh_num_indices_ground, GL_UNSIGNED_INT, 0);
	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		glViewport(0,0,width,height);
		projection_matrix = glm::perspective(90.0f, (float)width/(float)height,0.1f, 10000.0f);
	}


	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
		if(key_pressed == 32) {	//SPACE
			//reincarca shader
			glDeleteProgram(gl_program_shader_gouraud);
			gl_program_shader_gouraud = lab::loadShader("shadere\\shader_gouraud_vertex.glsl", "shadere\\shader_gouraud_fragment.glsl");
		}
		if(key_pressed == 'q'){
			static bool wire =true;
			wire=!wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire?GL_LINE:GL_FILL));
		}

		if (key_pressed == 'w') {
			light_position.z -= 1.0f;
		}
		if (key_pressed == 's') {
			light_position.z += 1.0f;
		}
		if (key_pressed == 'a') {
			light_position.x -= 1.0f;
		}
		if (key_pressed == 'd') {
			light_position.x += 1.0f;
		}

		if (key_pressed == '[') {
			std::cout << ++notifier << "\n";
			camera.rotateFPS_OX(-2.0f);
		}
		if (key_pressed == ']') {
			std::cout << --notifier << "\n";
			camera.rotateFPS_OX(2.0f);
		}

	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
		if (key_pressed == GLUT_KEY_LEFT) {
			camera.rotateFPS_OY(-2.0f);
		}
		if (key_pressed == GLUT_KEY_RIGHT) {
			camera.rotateFPS_OY(2.0f);
		}
		if (key_pressed == GLUT_KEY_UP) {
			camera.translateForward(1.0f);
		}
		if (key_pressed == GLUT_KEY_DOWN) {
			camera.translateForward(-1.0f);
		}
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
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ std::cout<<"Mouse scroll"<<std::endl;}

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("EGC - lab 6 - iluminare Gouraud"),800,600,100,100,true);
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
	std::cout<<"Taste:"<<std::endl<<"\tESC ... iesire"<<std::endl<<"\tSPACE ... reincarca shadere"<<std::endl<<"\tw ... toggle wireframe"<<std::endl;

	//run
	lab::glut::run();

	return 0;
}