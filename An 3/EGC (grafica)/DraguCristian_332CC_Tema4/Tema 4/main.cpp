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
//texturi
#include "lab_texture_loader.hpp"
//time
#include <ctime>

#include "lab_camera.hpp"



class Laborator : public lab::glut::WindowListener
{
	//variabile
private:
	glm::mat4 model_matrix_bamboo, model_matrix_earth, model_matrix_cube, model_matrix_plane, model_matrix_display, model_matrix_menu;				//matrici modelare pentru cele 3 obiecte
	glm::mat4 view_matrix, projection_matrix;																					//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int gl_program_shader;																								//id-ul de opengl al obiectului de tip program shader
	unsigned int screen_width, screen_height;

	//meshe
	unsigned int earth_vbo, earth_ibo, earth_vao, earth_num_indices;
	unsigned int bamboo_vbo, bamboo_ibo, bamboo_vao, bamboo_num_indices;				//containere opengl pentru vertecsi, indecsi si stare
	unsigned int cube_vbo, cube_ibo, cube_vao, cube_num_indices;
	unsigned int plane_vbo, plane_ibo, plane_vao, plane_num_indices;
	unsigned int display_vbo, display_ibo, display_vao, display_num_indices;
	unsigned int text_vbo, text_ibo, text_vao, text_num_indices;
	unsigned int menu_vbo, menu_ibo, menu_vao, menu_num_indices;
	unsigned int menu_text_vbo, menu_text_ibo, menu_text_vao, menu_text_num_indices;

	//texturi
	unsigned int earth_texture, bamboo_texture_color, bamboo_texture_alpha, cube_texture, display_texture, text_texture, plane_texture, menu_texture, menu_text_texture;

	// Camera
	lab::Camera camera;
	glm::mat4 projectionMatrix;
	float FoV;
	float zNear, zFar;
	float aspectRatio;
	unsigned char *data;
	std::vector<lab::VertexFormat> vertices;
	std::vector<unsigned int> indices;
	std::vector<lab::VertexFormat> vertices_menu;
	std::vector<unsigned int> indices_menu;
	float position = -45.0f;
	int mode = 0; // 0 = welcome screen mode, 1 = type mode
	bool move = false;

	// Buffer for input
	char keyState[256];
	char specialKeyState[256];

	unsigned int frameTime;
	unsigned int previousTime;

	//metode
public:

	
	void welcomeText() {

		vertices.push_back(lab::VertexFormat(0, 10, 5, 0, 0, 1, 0.5, 0.125));    // T
		vertices.push_back(lab::VertexFormat(10, 10, 5, 0, 0, 1, 0.625, 0.125));
		vertices.push_back(lab::VertexFormat(10, 20, 5, 0, 0, 1, 0.625, 0.25));
		vertices.push_back(lab::VertexFormat(0, 20, 5, 0, 0, 1, 0.5, 0.25));

		vertices.push_back(lab::VertexFormat(7, 10, 5, 0, 0, 1, 0.625, 0.375));  // E
		vertices.push_back(lab::VertexFormat(17, 10, 5, 0, 0, 1, 0.75, 0.375));
		vertices.push_back(lab::VertexFormat(17, 20, 5, 0, 0, 1, 0.75, 0.5));
		vertices.push_back(lab::VertexFormat(7, 20, 5, 0, 0, 1, 0.625, 0.5));

		vertices.push_back(lab::VertexFormat(14, 10, 5, 0, 0, 1, 0.625, 0.25));  // M
		vertices.push_back(lab::VertexFormat(24, 10, 5, 0, 0, 1, 0.75, 0.25));
		vertices.push_back(lab::VertexFormat(24, 20, 5, 0, 0, 1, 0.75, 0.375));
		vertices.push_back(lab::VertexFormat(14, 20, 5, 0, 0, 1, 0.625, 0.375));

		vertices.push_back(lab::VertexFormat(21, 10, 5, 0, 0, 1, 0.125, 0.375));  // A
		vertices.push_back(lab::VertexFormat(31, 10, 5, 0, 0, 1, 0.25, 0.375));
		vertices.push_back(lab::VertexFormat(31, 20, 5, 0, 0, 1, 0.25, 0.5));
		vertices.push_back(lab::VertexFormat(21, 20, 5, 0, 0, 1, 0.125, 0.5));

		vertices.push_back(lab::VertexFormat(28, 10, 5, 0, 0, 1, 0.0, 0.875));  // blank
		vertices.push_back(lab::VertexFormat(38, 10, 5, 0, 0, 1, 0.125, 1.0));
		vertices.push_back(lab::VertexFormat(38, 20, 5, 0, 0, 1, 0.125, 1.0));
		vertices.push_back(lab::VertexFormat(28, 20, 5, 0, 0, 1, 0.0, 0.875));

		vertices.push_back(lab::VertexFormat(35, 10, 5, 0, 0, 1, 0.5, 0.625));  // 4
		vertices.push_back(lab::VertexFormat(45, 10, 5, 0, 0, 1, 0.625, 0.625));
		vertices.push_back(lab::VertexFormat(45, 20, 5, 0, 0, 1, 0.625, 0.75));
		vertices.push_back(lab::VertexFormat(35, 20, 5, 0, 0, 1, 0.5, 0.75));

		indices.push_back(0); indices.push_back(1); indices.push_back(2); indices.push_back(0); indices.push_back(2); indices.push_back(3);
		indices.push_back(4); indices.push_back(5); indices.push_back(6); indices.push_back(4); indices.push_back(6); indices.push_back(7);
		indices.push_back(8); indices.push_back(9); indices.push_back(10); indices.push_back(8); indices.push_back(10); indices.push_back(11);
		indices.push_back(12); indices.push_back(13); indices.push_back(14); indices.push_back(12); indices.push_back(14); indices.push_back(15);
		indices.push_back(16); indices.push_back(17); indices.push_back(18); indices.push_back(16); indices.push_back(18); indices.push_back(19);
		indices.push_back(20); indices.push_back(21); indices.push_back(22); indices.push_back(20); indices.push_back(22); indices.push_back(23);

		vertices_menu.push_back(lab::VertexFormat(-50, 10, 20, 0, 0, 1, 0.625, 0.25));  // M
		vertices_menu.push_back(lab::VertexFormat(-40, 10, 20, 0, 0, 1, 0.75, 0.25));
		vertices_menu.push_back(lab::VertexFormat(-40, 20, 20, 0, 0, 1, 0.75, 0.375));
		vertices_menu.push_back(lab::VertexFormat(-50, 20, 20, 0, 0, 1, 0.625, 0.375));

		vertices_menu.push_back(lab::VertexFormat(-43, 10, 20, 0, 0, 1, 0.625, 0.375));  // E
		vertices_menu.push_back(lab::VertexFormat(-33, 10, 20, 0, 0, 1, 0.75, 0.375));
		vertices_menu.push_back(lab::VertexFormat(-33, 20, 20, 0, 0, 1, 0.75, 0.5));
		vertices_menu.push_back(lab::VertexFormat(-43, 20, 20, 0, 0, 1, 0.625, 0.5));

		vertices_menu.push_back(lab::VertexFormat(-36, 10, 20, 0, 0, 1, 0.75, 0.25));  // N
		vertices_menu.push_back(lab::VertexFormat(-26, 10, 20, 0, 0, 1, 0.875, 0.25));
		vertices_menu.push_back(lab::VertexFormat(-26, 20, 20, 0, 0, 1, 0.875, 0.375));
		vertices_menu.push_back(lab::VertexFormat(-36, 20, 20, 0, 0, 1, 0.75, 0.375));

		vertices_menu.push_back(lab::VertexFormat(-29, 10, 20, 0, 0, 1, 0.625, 0.125));  // U
		vertices_menu.push_back(lab::VertexFormat(-19, 10, 20, 0, 0, 1, 0.75, 0.125));
		vertices_menu.push_back(lab::VertexFormat(-19, 20, 20, 0, 0, 1, 0.75, 0.25));
		vertices_menu.push_back(lab::VertexFormat(-29, 20, 20, 0, 0, 1, 0.625, 0.25));

		indices_menu.push_back(0); indices_menu.push_back(1); indices_menu.push_back(2); indices_menu.push_back(0); indices_menu.push_back(2); indices_menu.push_back(3);
		indices_menu.push_back(4); indices_menu.push_back(5); indices_menu.push_back(6); indices_menu.push_back(4); indices_menu.push_back(6); indices_menu.push_back(7);
		indices_menu.push_back(8); indices_menu.push_back(9); indices_menu.push_back(10); indices_menu.push_back(8); indices_menu.push_back(10); indices_menu.push_back(11);
		indices_menu.push_back(12); indices_menu.push_back(13); indices_menu.push_back(14); indices_menu.push_back(12); indices_menu.push_back(14); indices_menu.push_back(15);
	}

	Laborator()
	{
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5, 0.5, 0.5, 1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)

									//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");

		//ecran
		lab::loadObj("resurse\\ecran.obj", cube_vao, cube_vbo, cube_ibo, cube_num_indices);
		cube_texture = lab::loadTextureBMP("resurse\\ecran_texture1.bmp");
		model_matrix_cube = glm::translate(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), glm::vec3(0, -10, -40));

		//display
		lab::loadObj("resurse\\display.obj", display_vao, display_vbo, display_ibo, display_num_indices);
		lab::loadObj("resurse\\display.obj", menu_vao, menu_vbo, menu_ibo, menu_num_indices);
		model_matrix_display = glm::translate(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), glm::vec3(0, -10, -43.9));
		model_matrix_menu = glm::translate(glm::mat4(1.0f), glm::vec3(camera.getPosition()[0] + 10.0f, camera.getPosition()[1] - 10.0f, camera.getPosition()[2] - 50.0f));

		//plane
		lab::loadObj("resurse\\plan.obj", plane_vao, plane_vbo, plane_ibo, plane_num_indices);
		plane_texture = lab::loadTextureBMP("resurse\\plan_texture.bmp");
		model_matrix_plane = glm::translate(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), glm::vec3(0, -20, 0));

		//font
		text_texture = lab::loadTextureBMP("resurse\\fontBig.bmp");
		menu_text_texture = lab::loadTextureBMP("resurse\\fontBig.bmp");

		//matrici de modelare si vizualizare
		view_matrix = glm::lookAt(glm::vec3(0, 0, 40), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		// init camera
		camera.set(glm::vec3(0, 0, 80), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		memset(keyState, 0, 256);
		memset(specialKeyState, 0, 256);

		// Initialize default projection values
		zNear = 0.1f;
		zFar = 500.0f;
		FoV = 60.0f;
		aspectRatio = 800 / 600.0f;

		previousTime = 0;

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		welcomeText();
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator() {
		//distruge shader
		glDeleteProgram(gl_program_shader);

		glDeleteBuffers(1, &cube_vbo);	glDeleteBuffers(1, &cube_ibo);	glDeleteVertexArrays(1, &cube_vao);
		glDeleteBuffers(1, &plane_vbo);	glDeleteBuffers(1, &plane_ibo);	glDeleteVertexArrays(1, &plane_vao);
		glDeleteBuffers(1, &display_vbo);	glDeleteBuffers(1, &display_ibo);	glDeleteVertexArrays(1, &display_vao);
	}

	void computePerspectiveProjection()
	{
		projectionMatrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
	}


	// ----------------------------------------------------------------------------
	// functie manuala
	// ----------------------------------------------------------------------------
	unsigned int createManualTexture(unsigned int width, unsigned int height)
	{
		// TODO
		// CREATE random texture for cube / checkerboard
		data = new unsigned char[width * height * 3];
		int nr = 0;
		for (int i = 0; i < 3 * width * height; i += 6) {
			if (i % width == 0)
				nr++;
			if (nr % 2 == 0) {
				data[i] = 0;
				data[i + 1] = 0;
				data[i + 2] = 0;
				data[i + 3] = 255;
				data[i + 4] = 255;
				data[i + 5] = 255;
			}
			else {
				data[i] = 255;
				data[i + 1] = 255;
				data[i + 2] = 255;
				data[i + 3] = 0;
				data[i + 4] = 0;
				data[i + 5] = 0;
			}
		}
		// create new OpenGL texture
		unsigned int gl_texture_object;
		glGenTextures(1, &gl_texture_object);
		glBindTexture(GL_TEXTURE_2D, gl_texture_object);

		// TODO
		// set filtering parameters and texture wrap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// TODO set anisotropy level
		float maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

		// TODO create texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		// TODO create mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		//returneaza obiectul textura
		return gl_texture_object;
	}

	void calculateBuffers() {

		glDeleteBuffers(1, &text_vbo);	
		glDeleteBuffers(1, &text_ibo);	
		glDeleteVertexArrays(1, &text_vao);

		unsigned int gl_vertex_array_object, gl_vertex_buffer_object, gl_index_buffer_object;

		//vertex array object -> un obiect ce reprezinta un container pentru starea de desenare
		glGenVertexArrays(1, &gl_vertex_array_object);
		glBindVertexArray(gl_vertex_array_object);

		//vertex buffer object -> un obiect in care tinem vertecsii
		glGenBuffers(1, &gl_vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(lab::VertexFormat), &vertices[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
		glGenBuffers(1, &gl_index_buffer_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);						//trimite pozitii pe pipe 0
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float) * 3));		//trimite normale pe pipe 1
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float) * 3));	//trimite texcoords pe pipe 2

		text_vao = gl_vertex_array_object;
		text_vbo = gl_vertex_buffer_object;
		text_ibo = gl_index_buffer_object;
		text_num_indices = indices.size();
	}

	void calculateBuffers2() {

		glDeleteBuffers(1, &menu_text_vbo);
		glDeleteBuffers(1, &menu_text_ibo);
		glDeleteVertexArrays(1, &menu_text_vao);

		unsigned int gl_vertex_array_object, gl_vertex_buffer_object, gl_index_buffer_object;

		//vertex array object -> un obiect ce reprezinta un container pentru starea de desenare
		glGenVertexArrays(1, &gl_vertex_array_object);
		glBindVertexArray(gl_vertex_array_object);

		//vertex buffer object -> un obiect in care tinem vertecsii
		glGenBuffers(1, &gl_vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, vertices_menu.size()*sizeof(lab::VertexFormat), &vertices_menu[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
		glGenBuffers(1, &gl_index_buffer_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_menu.size()*sizeof(unsigned int), &indices_menu[0], GL_STATIC_DRAW);

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);						//trimite pozitii pe pipe 0
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float) * 3));		//trimite normale pe pipe 1
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float) * 3));	//trimite texcoords pe pipe 2

		menu_text_vao = gl_vertex_array_object;
		menu_text_vbo = gl_vertex_buffer_object;
		menu_text_ibo = gl_index_buffer_object;
		menu_text_num_indices = indices_menu.size();
	}

	void checkPosition(int i) {
		if (vertices.at(i + 1).position_x <= -51) {
			vertices.at(i).position_x = 51;
			vertices.at(i + 1).position_x = 61;
			vertices.at(i + 2).position_x = 61;
			vertices.at(i + 3).position_x = 51;
		}
	}

	void repositionText() {
		for (int i = 0; i < vertices.size(); i += 4) {
			vertices.at(i).position_x -= 0.01;
			vertices.at(i + 1).position_x -= 0.01;
			vertices.at(i + 2).position_x -= 0.01;
			vertices.at(i + 3).position_x -= 0.01;
			checkPosition(i);
		}
	}

	// Called every frame to draw
	void treatInput()
	{
		unsigned int time = glutGet(GLUT_ELAPSED_TIME);
		frameTime = time - previousTime;
		previousTime = time;

		float moveSpeed = frameTime / 20.0f;
		float rotateSpeed = frameTime / 20.0f;

		// Camera Translation
		if (keyState['W']) { camera.translateForward(moveSpeed); }
		if (keyState['A']) { camera.translateRight(-moveSpeed); }
		if (keyState['S']) { camera.translateForward(-moveSpeed); }
		if (keyState['D']) { camera.translateRight(moveSpeed); }
		if (keyState['E']) { camera.translateUpword(moveSpeed); }
		if (keyState['Q']) { camera.translateUpword(-moveSpeed); }

		// Camera Rotate FPS
		if (specialKeyState[GLUT_KEY_LEFT]) { camera.rotateFPS_OY(rotateSpeed); }
		if (specialKeyState[GLUT_KEY_RIGHT]) { camera.rotateFPS_OY(-rotateSpeed); }

		if (specialKeyState[GLUT_KEY_UP]) { camera.rotateFPS_OX(rotateSpeed); }
		if (specialKeyState[GLUT_KEY_DOWN]) { camera.rotateFPS_OX(-rotateSpeed); }
	}

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame() {
		treatInput();
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(gl_program_shader);

		//trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "view_matrix"), 1, false, glm::value_ptr(camera.getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));

		unsigned int hasAlpha = glGetUniformLocation(gl_program_shader, "has_alpha");
		unsigned int locatie = glGetUniformLocation(gl_program_shader, "textura1");

		if (vertices.size() > 0) {
			calculateBuffers();
			//display
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix_display));
			glUniform1i(hasAlpha, 1);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, text_texture);
			locatie = glGetUniformLocation(gl_program_shader, "textura1");
			glUniform1i(locatie, 1);

			glActiveTexture(GL_TEXTURE0 + 2);
			glBindTexture(GL_TEXTURE_2D, text_texture);
			locatie = glGetUniformLocation(gl_program_shader, "textura2");
			glUniform1i(locatie, 2);

			glBindVertexArray(text_vao);
			glDrawElements(GL_TRIANGLES, text_num_indices, GL_UNSIGNED_INT, 0);
		}

		//cube----------------------------
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix_cube));
		glUniform1i(hasAlpha, 0);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, cube_texture);
		locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, 1);

		glBindVertexArray(cube_vao);
		glDrawElements(GL_TRIANGLES, cube_num_indices, GL_UNSIGNED_INT, 0);

		//plane
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix_plane));
		glUniform1i(hasAlpha, 0);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, plane_texture);
		locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, 1);

		glBindVertexArray(plane_vao);
		glDrawElements(GL_TRIANGLES, plane_num_indices, GL_UNSIGNED_INT, 0);

		calculateBuffers2();
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix_menu));
		glUniform1i(hasAlpha, 1);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, menu_texture);
		locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, 1);

		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, menu_text_texture);
		locatie = glGetUniformLocation(gl_program_shader, "textura2");
		glUniform1i(locatie, 2);

		glBindVertexArray(menu_text_vao);
		glDrawElements(GL_TRIANGLES, menu_text_num_indices, GL_UNSIGNED_INT, 0);

		if (mode == 0 || move == true)
			repositionText();
	}

	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame() {}

	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height) {
		//reshape
		if (height == 0) height = 1;
		float aspect = (float)width / (float)height;
		projection_matrix = glm::perspective(75.0f, aspect, 0.1f, 10000.0f);
	}

	void addLetterToVectors(int k, int f, float y) {
		int pos = position;
		if (vertices.size() > 0)
			pos = vertices.back().position_x + 7.0f;
		vertices.push_back(lab::VertexFormat(pos,		10, 5, 0, 0, 1, (k - f) * 0.125,	 y));
		std::cout << (k - f) * 0.125 << " " << y << "\n";
		vertices.push_back(lab::VertexFormat(pos + 10, 10, 5, 0, 0, 1, (k - f + 1) * 0.125, y));
		vertices.push_back(lab::VertexFormat(pos + 10, 20, 5, 0, 0, 1, (k - f + 1) * 0.125, y + 0.125));
		vertices.push_back(lab::VertexFormat(pos,		20, 5, 0, 0, 1, (k - f) * 0.125,	 y + 0.125));
		int last = 0;
		if (indices.size() > 0)
			last = indices.back() + 1;
		indices.push_back(last); indices.push_back(last + 1); indices.push_back(last + 2); indices.push_back(last); indices.push_back(last + 2); indices.push_back(last + 3);
		position += 7.0f;
	}

	void addLetter(int k) {
		//std::cout << k << "\n";
		if (k >= 104 && k <= 111) {
			addLetterToVectors(k, 104, 0.25);
		}
		if (k >= 112 && k <= 119) {
			addLetterToVectors(k, 112, 0.125);
		}
		if (k >= 97 && k <= 103) {
			addLetterToVectors(k + 1, 97, 0.375);
		}
		if (k >= 120 && k <= 122) {
			addLetterToVectors(k, 120, 0.0);
		}
		if (k >= 48 && k <= 55) {
			addLetterToVectors(k, 48, 0.625);
		}
		if (k >= 56 && k <= 57) {
			addLetterToVectors(k, 56, 0.5);
		}
	}

	void deleteLetter() {
		if (vertices.size() > 0) {
			for (int i = 0; i < 4; i++) {
				vertices.pop_back();
			}
			for (int i = 0; i < 6; i++) {
				indices.pop_back();
			}
			position -= 7;
		}
	}

	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y)
	{
		keyState[key_pressed] = 1;
		if (key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
		if (key_pressed == 32) {
			glDeleteProgram(gl_program_shader);
			gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
		}
		if (key_pressed == '`') {
			static bool wire = true;
			wire = !wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire ? GL_LINE : GL_FILL));
		}
		if ((int)key_pressed == 13) {
			mode = (mode + 1) % 2;
			vertices.clear();
			indices.clear();
			glDeleteBuffers(1, &text_vbo);	glDeleteBuffers(1, &text_ibo);	glDeleteVertexArrays(1, &text_vao);
			if (mode == 0) {
				welcomeText();
			}
			else {
				position = -45.0f;
			}
		}
		if ((((int)key_pressed >= 97 && (int)key_pressed <= 122) || ((int)key_pressed >= 48 && (int)key_pressed <= 57)) && position < 46.0f && mode == 1)
			addLetter((int)key_pressed);
		if ((int)key_pressed == 8 && mode == 1) {
			deleteLetter();
		}
		
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y) {
		keyState[key_released] = 0;
	}

	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y) {
		specialKeyState[key_pressed] = 1;
		if (key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if (key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
		if (key_pressed == GLUT_KEY_CTRL_L && mode == 1) move = !move;
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y) {
		specialKeyState[key_released] = 0;
	}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y) { }
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y) { }
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y) { }
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y) { }

};

int main()
{
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("lab EGC 8 - texturi"), 800, 600, 100, 100, true);
	lab::glut::ContextInfo context(3, 3, false);
	lab::glut::FramebufferInfo framebuffer(true, true, true, true);
	lab::glut::init(window, context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout << "GLEW:initializare" << std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Laborator mylab;
	lab::glut::setListener(&mylab);

	//taste
	std::cout << "Taste:" << std::endl << "\tESC ... iesire" << std::endl << "\tSPACE ... reincarca shadere" << std::endl << "\tw ... toggle wireframe" << std::endl;

	//run
	lab::glut::run();

	return 0;
}