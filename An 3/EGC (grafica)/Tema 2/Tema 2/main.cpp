
#include "lab_blackbox.hpp"
#include "lab_camera.hpp"


//time
#include <ctime>


#define  KEY_ESCAPE		27
#define  KEY_SPACEBAR   32

class Laborator5
	: public lab::glut::WindowListener
{

	private:
		lab::BlackBox BLACKBOX;

		bool keyState[256];
		bool specialKeyState[256];

		// Objects
		lab::Mesh *TREX, *cola1, *cola2;
		lab::Mesh *cameraTarget;
		std::vector<lab::Mesh*> obiecte = vector<lab::Mesh*>();
		bool thirdPersonCamera;
		bool alwaysDrawTarget;

		// Projection matrix
		bool isPerspectiveProjection, coliziune = false, peobiect = false, sepoatesari = false, endGame = false, subobiect = false, cola1Taken = false, cola2Taken = false;
		glm::mat4 projectionMatrix, projectionMatrixFPS;
		glm::vec3 aux;
		float FoV;
		float zNear, zFar;
		float aspectRatio;
		float orthoLeft, orthoRight, orthoTop, orthoBottom;
		int jump = 0;
		float wallHeight = -15.0f, mover = 0.1f, finalpoz;
		int serotestecamera = 0, rotatiecamera = 1, trexsem = 0, catecola = 0;

		// Camera
		lab::Camera camera, cameraFPS;

	public:

		void ajustCoords(lab::Mesh* mesh, float x, float y, float z) {
			mesh->p2.x += x;
			mesh->p2.y += y;
			mesh->p2.z += z;
		}

		Laborator5()
		{
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/wall.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/cube.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/plate.obj"));
			obiecte.push_back(BLACKBOX.loadMesh("resurse/platefinal.obj"));
			TREX = BLACKBOX.loadMesh("resurse/trex.obj");
			cola1 = BLACKBOX.loadMesh("resurse/cola.obj");
			cola2 = BLACKBOX.loadMesh("resurse/cola.obj");
			
			cameraTarget = BLACKBOX.loadMesh("resurse/sphere.obj");

			// init camera
			camera.set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			cameraFPS.set(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			cameraFPS.rotateFPS_OY(-45);

			// initializa all key states to not pressed
			memset(keyState, 0, 256);
			memset(specialKeyState, 0, 256);

			// helper variables for third person camera
			thirdPersonCamera = false;
			alwaysDrawTarget = false;

			// Initialize default projection values
			zNear = 0.1f;
			zFar = 500.0f;
			FoV = 60.0f;
			aspectRatio = 1920 / 1080.0f;
			orthoLeft = -25;
			orthoRight = 25;
			orthoBottom = -25;
			orthoTop = 25;

			// value may be used for updating the projection when reshaping the window
			isPerspectiveProjection = true;

			projectionMatrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
			projectionMatrixFPS = glm::perspective(FoV, 4.0f/3.0f, zNear, zFar);
		}

		~Laborator5()
		{
			
		}

		void computePerspectiveProjection()
		{
			projectionMatrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
		}

		void computeOrthograhicProjection()
		{
			//projectionMatrix = glm::mat4(1);
		}

		void initcola() {
			cola1Taken = false;
			cola2Taken = false;
		}

		bool hasCollision(lab::Mesh* obiect) {
			if (camera.getTargetPosition()[0] + 2 >= obiect->p1.x && camera.getTargetPosition()[0] - 2 <= obiect->p2.x &&
				camera.getTargetPosition()[1] + 2 >= obiect->p1.y && camera.getTargetPosition()[1] - 2 <= obiect->p2.y &&
				camera.getTargetPosition()[2] + 2 >= obiect->p1.z && camera.getTargetPosition()[2] - 2 <= obiect->p2.z)
				return true;
			return false;
		}

		void notifyBeginFrame() { };

		void treatInput()
		{
			float frameTime = BLACKBOX.getFrameTimeSeconds();
			float moveSpeed = frameTime * 20;

			float rotateSpeedOX = frameTime * 40;
			float rotateSpeedOY = frameTime * 40;
			float rotateSpeedOZ = frameTime * 40;

			if (keyState['a']) {
				if (endGame == false) {
					coliziune = false;
					for (int i = 0; i < obiecte.size(); i++) {
						if (hasCollision(obiecte.at(i))) {
							coliziune = true;
						}
					}
					if ((!coliziune || peobiect) && serotestecamera == 0) {
						camera.translateRight(-moveSpeed);
						cameraFPS.translateForward(moveSpeed);
					}
				}
			}
			if (keyState['d']) {
				if (endGame == false) {
					coliziune = false;
					for (int i = 0; i < obiecte.size(); i++) {
						if (hasCollision(obiecte.at(i))) {
							coliziune = true;
						}
					}
					if ((!coliziune || peobiect) && serotestecamera == 0) {
						camera.translateRight(moveSpeed);
						cameraFPS.translateForward(-moveSpeed);
					}
				}
			}
			if (keyState[KEY_SPACEBAR]) {
				if (endGame == false) {
					if (jump == 0 && sepoatesari) {
						jump = 230;
						sepoatesari = false;
					}
				}
			}

			if (specialKeyState[GLUT_KEY_LEFT]) {
				if (endGame == false) {
					if (serotestecamera == 0) {
						sepoatesari = false;
						serotestecamera = 900;
						rotatiecamera = 0;
					}
				}
			}
			if (specialKeyState[GLUT_KEY_RIGHT]) {
				if (endGame == false) {
					if (serotestecamera == 0) {
						sepoatesari = false;
						serotestecamera = 900;
						rotatiecamera = 1;
					}
				}
			}


			if (keyState['=']) { FoV += 0.01; computePerspectiveProjection(); }
			if (keyState['-']) { FoV -= 0.01; computePerspectiveProjection(); }

		}

		// A key was pressed
		void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y)
		{
			keyState[key_pressed] = 1;

			if (key_pressed == KEY_ESCAPE)
			{
				lab::glut::close();
			}

			if (key_pressed == 'p')
			{
				projectionMatrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
			}

			// Reset Camera
			if (keyState['c'])
			{
				endGame = false;
				camera.set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
				cameraFPS.set(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
				cameraFPS.rotateFPS_OY(-45);
				initcola();
			}

		}

		// When a key was released
		void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y)
		{
			keyState[key_released] = 0;
		}

		// Special key pressed like the navigation arrows or function keys F1, F2, ...
		void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y)
		{
			specialKeyState[key_pressed] = 1;

			switch (key_pressed)
			{
			case GLUT_KEY_F1: {
				lab::glut::enterFullscreen();
				break;
			}

			case GLUT_KEY_F2: {
				lab::glut::exitFullscreen();
				break;
			}

			case GLUT_KEY_F5: {
				BLACKBOX.LoadShader();
				break;
			}

			default:
				break;
			}
		}

		// Called when a special key was released
		void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y)
		{
			specialKeyState[key_released] = 0;
		}

		// Called every frame to draw
		void notifyDisplayFrame()
		{
			// Treat continuous input
			treatInput();

			// Clear Color Buffer with the specified color
			glClearColor(0.8, 0.8, 0.8, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			BLACKBOX.notifyDisplay();

			unsigned int width = lab::glut::getInitialWindowInformation().width;
			unsigned int height = lab::glut::getInitialWindowInformation().height;

			glViewport(0, 0, width, height);

			// Send view matrix to the GPU
			BLACKBOX.setViewMatrix(camera.getViewMatrix());
			
			// Send projection matrix to the GPU
			BLACKBOX.setProjectionMatrix(projectionMatrix);

			glm::mat4 objectModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-5, -15, -5));
			BLACKBOX.setModelMatrix(objectModelMatrix);
			BLACKBOX.drawMesh(obiecte.at(0));
			obiecte.at(0)->p1.x = -5; obiecte.at(0)->p1.y = -15; obiecte.at(0)->p1.z = -5;
			obiecte.at(0)->p2.x = 5; obiecte.at(0)->p2.y = -5; obiecte.at(0)->p2.z = 5;
			
			glm::mat4 objectModelMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(5, -15, -5));
			BLACKBOX.setModelMatrix(objectModelMatrix1);
			BLACKBOX.drawMesh(obiecte.at(1));
			obiecte.at(1)->p1.x = 5; obiecte.at(1)->p1.y = -15; obiecte.at(1)->p1.z = -5;
			obiecte.at(1)->p2.x = 15; obiecte.at(1)->p2.y = -5; obiecte.at(1)->p2.z = 5;

			if (std::abs(wallHeight + 1.0f) < 0.1f) {
				mover = -0.01f;
			}
			else if (std::abs(wallHeight + 15.0f) < 0.1f) {
				mover = 0.01f;
			}
			wallHeight += mover;
			glm::mat4 objectModelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, wallHeight, -5));
			BLACKBOX.setModelMatrix(objectModelMatrix2);
			BLACKBOX.drawMesh(obiecte.at(2));
			obiecte.at(2)->p1.x = -15; obiecte.at(2)->p1.y = wallHeight; obiecte.at(2)->p1.z = -5;
			obiecte.at(2)->p2.x = -13; obiecte.at(2)->p2.y = wallHeight + 10; obiecte.at(2)->p2.z = 5;

			glm::mat4 objectModelMatrix3 = glm::translate(glm::mat4(1.0f), glm::vec3(-35, -15, -5));
			BLACKBOX.setModelMatrix(objectModelMatrix3);
			BLACKBOX.drawMesh(obiecte.at(3));
			obiecte.at(3)->p1.x = -35; obiecte.at(3)->p1.y = -15; obiecte.at(3)->p1.z = -5;
			obiecte.at(3)->p2.x = -25; obiecte.at(3)->p2.y = -5; obiecte.at(3)->p2.z = 5;

			glm::mat4 objectModelMatrix4 = glm::translate(glm::mat4(1.0f), glm::vec3(-45, -5, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix4);
			BLACKBOX.drawMesh(obiecte.at(4));
			obiecte.at(4)->p1.x = -45; obiecte.at(4)->p1.y = -5; obiecte.at(4)->p1.z = 5;
			obiecte.at(4)->p2.x = -35; obiecte.at(4)->p2.y = 5; obiecte.at(4)->p2.z = 15;

			//drum drept///////
			glm::mat4 objectModelMatrix5 = glm::translate(glm::mat4(1.0f), glm::vec3(-25, 5, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix5);
			BLACKBOX.drawMesh(obiecte.at(5));
			obiecte.at(5)->p1.x = -25; obiecte.at(5)->p1.y = 5; obiecte.at(5)->p1.z = 5;
			obiecte.at(5)->p2.x = -15; obiecte.at(5)->p2.y = 15; obiecte.at(5)->p2.z = 15;

			glm::mat4 objectModelMatrix6 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, 5, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix6);
			BLACKBOX.drawMesh(obiecte.at(6));
			obiecte.at(6)->p1.x = -15; obiecte.at(6)->p1.y = 5; obiecte.at(6)->p1.z = 5;
			obiecte.at(6)->p2.x = -5; obiecte.at(6)->p2.y = 15; obiecte.at(6)->p2.z = 15;

			glm::mat4 objectModelMatrix7 = glm::translate(glm::mat4(1.0f), glm::vec3(-5, 5, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix7);
			BLACKBOX.drawMesh(obiecte.at(7));
			obiecte.at(7)->p1.x = -5; obiecte.at(7)->p1.y = 5; obiecte.at(7)->p1.z = 5;
			obiecte.at(7)->p2.x = 5; obiecte.at(7)->p2.y = 15; obiecte.at(7)->p2.z = 15;

			glm::mat4 objectModelMatrix8 = glm::translate(glm::mat4(1.0f), glm::vec3(5, 5, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix8);
			BLACKBOX.drawMesh(obiecte.at(8));
			obiecte.at(8)->p1.x = 5; obiecte.at(8)->p1.y = 5; obiecte.at(8)->p1.z = 5;
			obiecte.at(8)->p2.x = 15; obiecte.at(8)->p2.y = 15; obiecte.at(8)->p2.z = 15;

			glm::mat4 objectModelMatrix9 = glm::translate(glm::mat4(1.0f), glm::vec3(15, 15, 5));
			BLACKBOX.setModelMatrix(objectModelMatrix9);
			BLACKBOX.drawMesh(obiecte.at(9));
			obiecte.at(9)->p1.x = 15; obiecte.at(9)->p1.y = 15; obiecte.at(9)->p1.z = 5;
			obiecte.at(9)->p2.x = 25; obiecte.at(9)->p2.y = 25; obiecte.at(9)->p2.z = 15;

			//al doilea drum drept////
			glm::mat4 objectModelMatrix10 = glm::translate(glm::mat4(1.0f), glm::vec3(15, 15, -25));
			BLACKBOX.setModelMatrix(objectModelMatrix10);
			BLACKBOX.drawMesh(obiecte.at(10));
			obiecte.at(10)->p1.x = 15; obiecte.at(10)->p1.y = 15; obiecte.at(10)->p1.z = -25;
			obiecte.at(10)->p2.x = 25; obiecte.at(10)->p2.y = 25; obiecte.at(10)->p2.z = -15;

			glm::mat4 objectModelMatrix11 = glm::translate(glm::mat4(1.0f), glm::vec3(15, 15, -35));
			BLACKBOX.setModelMatrix(objectModelMatrix11);
			BLACKBOX.drawMesh(obiecte.at(11));
			obiecte.at(11)->p1.x = 15; obiecte.at(11)->p1.y = 15; obiecte.at(11)->p1.z = -35;
			obiecte.at(11)->p2.x = 25; obiecte.at(11)->p2.y = 25; obiecte.at(11)->p2.z = -25;

			glm::mat4 objectModelMatrix12 = glm::translate(glm::mat4(1.0f), glm::vec3(15, 15, -45));
			BLACKBOX.setModelMatrix(objectModelMatrix12);
			BLACKBOX.drawMesh(obiecte.at(12));
			obiecte.at(12)->p1.x = 15; obiecte.at(12)->p1.y = 15; obiecte.at(12)->p1.z = -45;
			obiecte.at(12)->p2.x = 25; obiecte.at(12)->p2.y = 25; obiecte.at(12)->p2.z = -35;

			glm::mat4 objectModelMatrix13 = glm::translate(glm::mat4(1.0f), glm::vec3(wallHeight, 5, -45));
			BLACKBOX.setModelMatrix(objectModelMatrix13);
			BLACKBOX.drawMesh(obiecte.at(13));
			obiecte.at(13)->p1.x = wallHeight; obiecte.at(13)->p1.y = 5; obiecte.at(13)->p1.z = -45;
			obiecte.at(13)->p2.x = wallHeight + 10; obiecte.at(13)->p2.y = 7; obiecte.at(13)->p2.z = -35;

			if (endGame == false) {
				glm::mat4 objectModelMatrix14 = glm::translate(glm::mat4(1.0f), glm::vec3(-(16 + wallHeight) - 30, 20, -45));
				BLACKBOX.setModelMatrix(objectModelMatrix14);
				BLACKBOX.drawMesh(obiecte.at(14));
				obiecte.at(14)->p1.x = -(16 + wallHeight) - 30; obiecte.at(14)->p1.y = 20; obiecte.at(14)->p1.z = -45;
				obiecte.at(14)->p2.x = -(16 + wallHeight) - 20; obiecte.at(14)->p2.y = 22; obiecte.at(14)->p2.z = -35;
				finalpoz = wallHeight;
			}
			else {
				glm::mat4 objectModelMatrix14 = glm::translate(glm::mat4(1.0f), glm::vec3(-(16 + finalpoz) - 30, 20, -45));
				BLACKBOX.setModelMatrix(objectModelMatrix14);
				BLACKBOX.drawMesh(obiecte.at(14));
				obiecte.at(14)->p1.x = -(16 + finalpoz) - 30; obiecte.at(14)->p1.y = 20; obiecte.at(14)->p1.z = -45;
				obiecte.at(14)->p2.x = -(16 + finalpoz) - 20; obiecte.at(14)->p2.y = 22; obiecte.at(14)->p2.z = -35;
			}

			if (!cola1Taken) {
				glm::mat4 colaMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, 15, -2));
				colaMatrix1 = glm::scale(colaMatrix1, glm::vec3(0.3f));
				BLACKBOX.setModelMatrix(colaMatrix1);
				BLACKBOX.drawMesh(cola1);
				cola1->p1.x = -15; cola1->p1.y = 15; cola1->p1.z = -2;
				cola1->p2.x = -13; cola1->p2.y = 17; cola1->p2.z = 2;
			}
			if (!cola2Taken) {
				glm::mat4 colaMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, 15, -42));
				colaMatrix2 = glm::scale(colaMatrix2, glm::vec3(0.3f));
				BLACKBOX.setModelMatrix(colaMatrix2);
				BLACKBOX.drawMesh(cola2);
				cola2->p1.x = -15; cola2->p1.y = 15; cola2->p1.z = -42;
				cola2->p2.x = -13; cola2->p2.y = 17; cola2->p2.z = -38;
			}

			glm::vec3 targetPosition = camera.getTargetPosition();
			glm::mat4 targetModelMatrix = glm::translate(glm::mat4(1.0f), targetPosition);
			targetModelMatrix = glm::scale(targetModelMatrix, glm::vec3(0.1f));
			BLACKBOX.setModelMatrix(targetModelMatrix);
			BLACKBOX.drawMesh(cameraTarget);
				
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glm::mat4 targetModelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(wallHeight * 2 + 7, 15, 9));
			targetModelMatrix2 = glm::scale(targetModelMatrix2, glm::vec3(0.3f));
			if(trexsem == 0)
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float)-90, glm::vec3(0, 1, 0));
			else 
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) 90, glm::vec3(0, 1, 0));
			if (std::abs(wallHeight + 15.0f) <= 0.1f && trexsem == 0) {
				trexsem = 1;
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) -90., glm::vec3(0, 1, 0));
			}
			else if (std::abs(wallHeight + 1.0f) <= 0.1f && trexsem == 1) {
				trexsem = 0;
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) 180, glm::vec3(0, 1, 0));
			}
			BLACKBOX.setModelMatrix(targetModelMatrix2);
			BLACKBOX.drawMesh(TREX);
			TREX->p1.x = wallHeight * 2 + 2; TREX->p1.y = 15; TREX->p1.z = 7;
			TREX->p2.x = wallHeight * 2 + 12; TREX->p2.y = 20; TREX->p2.z = 15;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


			glViewport(width - 400, 0, width, 400);
			BLACKBOX.setViewMatrix(cameraFPS.getViewMatrix());
			BLACKBOX.setProjectionMatrix(projectionMatrixFPS);
			BLACKBOX.setModelMatrix(objectModelMatrix);
			BLACKBOX.drawMesh(obiecte.at(0));
			BLACKBOX.setModelMatrix(objectModelMatrix1);
			BLACKBOX.drawMesh(obiecte.at(1));
			BLACKBOX.setModelMatrix(objectModelMatrix2);
			BLACKBOX.drawMesh(obiecte.at(2));
			BLACKBOX.setModelMatrix(objectModelMatrix3);
			BLACKBOX.drawMesh(obiecte.at(3));
			BLACKBOX.setModelMatrix(objectModelMatrix4);
			BLACKBOX.drawMesh(obiecte.at(4));
			BLACKBOX.setModelMatrix(objectModelMatrix5);
			BLACKBOX.drawMesh(obiecte.at(5));
			BLACKBOX.setModelMatrix(objectModelMatrix6);
			BLACKBOX.drawMesh(obiecte.at(6));
			BLACKBOX.setModelMatrix(objectModelMatrix7);
			BLACKBOX.drawMesh(obiecte.at(7));
			BLACKBOX.setModelMatrix(objectModelMatrix8);
			BLACKBOX.drawMesh(obiecte.at(8));
			BLACKBOX.setModelMatrix(objectModelMatrix9);
			BLACKBOX.drawMesh(obiecte.at(9));
			BLACKBOX.setModelMatrix(objectModelMatrix10);
			BLACKBOX.drawMesh(obiecte.at(10));
			BLACKBOX.setModelMatrix(objectModelMatrix11);
			BLACKBOX.drawMesh(obiecte.at(11));
			BLACKBOX.setModelMatrix(objectModelMatrix12);
			BLACKBOX.drawMesh(obiecte.at(12));
			BLACKBOX.setModelMatrix(objectModelMatrix13);
			BLACKBOX.drawMesh(obiecte.at(13));
			if (endGame == false) {
				glm::mat4 objectModelMatrix14 = glm::translate(glm::mat4(1.0f), glm::vec3(-(16 + wallHeight) - 30, 20, -45));
				BLACKBOX.setModelMatrix(objectModelMatrix14);
				BLACKBOX.drawMesh(obiecte.at(14));
			}
			else {
				glm::mat4 objectModelMatrix14 = glm::translate(glm::mat4(1.0f), glm::vec3(-(16 + finalpoz) - 30, 20, -45));
				BLACKBOX.setModelMatrix(objectModelMatrix14);
				BLACKBOX.drawMesh(obiecte.at(14));
			}
			if (!cola1Taken) {
				glm::mat4 colaMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, 15, -2));
				colaMatrix1 = glm::scale(colaMatrix1, glm::vec3(0.3f));
				BLACKBOX.setModelMatrix(colaMatrix1);
				BLACKBOX.drawMesh(cola1);
			}
			if (!cola2Taken) {
				glm::mat4 colaMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(-15, 15, -42));
				colaMatrix2 = glm::scale(colaMatrix2, glm::vec3(0.3f));
				BLACKBOX.setModelMatrix(colaMatrix2);
				BLACKBOX.drawMesh(cola2);
			}
			targetModelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(wallHeight * 2 + 7, 15, 9));
			targetModelMatrix2 = glm::scale(targetModelMatrix2, glm::vec3(0.3f));
			if (trexsem == 0)
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) - 90, glm::vec3(0, 1, 0));
			else
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) 90, glm::vec3(0, 1, 0));
			if (std::abs(wallHeight + 15.0f) <= 0.1f && trexsem == 0) {
				trexsem = 1;
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) - 90., glm::vec3(0, 1, 0));
			}
			else if (std::abs(wallHeight + 1.0f) <= 0.1f && trexsem == 1) {
				trexsem = 0;
				targetModelMatrix2 = glm::rotate(targetModelMatrix2, (glm::mediump_float) 180, glm::vec3(0, 1, 0));
			}
			BLACKBOX.setModelMatrix(targetModelMatrix2);
			BLACKBOX.drawMesh(TREX);
		}

		// Called when the frame ended
		void notifyEndFrame() {
			if (endGame == false) {
				if (serotestecamera > 0) {
					if (rotatiecamera == 1) {
						camera.rotateTPS_OY(-0.1f);
						cameraFPS.rotateFPS_OY(-0.1f);
						serotestecamera -= 0.1f;
					}
					else if (rotatiecamera == 0) {
						camera.rotateTPS_OY(0.1f);
						cameraFPS.rotateFPS_OY(0.1f);
						serotestecamera -= 0.1f;
					}
					if (serotestecamera == 1)
						sepoatesari = true;
				}
				else {
					coliziune = false;
					peobiect = false;
					subobiect = false;
					if (camera.getTargetPosition()[1] <= -50) {
						camera.set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
						cameraFPS.set(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
						cameraFPS.rotateFPS_OY(-45);
						initcola();
					}
					if (hasCollision(cola1)) {
						cola1Taken = true;
						catecola++;
						std::cout << "Can of soda obtained\n";
					}
					if (hasCollision(cola2)) {
						cola2Taken = true;
						catecola++;
						std::cout << "Can of soda obtained\n";
					}
					if (hasCollision(TREX)) {
						camera.set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
						cameraFPS.set(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
						cameraFPS.rotateFPS_OY(-45);
						initcola();
					}
					if (hasCollision(obiecte.at(14)) && camera.getTargetPosition()[1] >= obiecte.at(14)->p2.y) {
						endGame = true;
					}
					if (hasCollision(obiecte.at(2)) && camera.getTargetPosition()[1] >= obiecte.at(2)->p2.y) {
						camera.translateUpword(0.01f);
						cameraFPS.translateUpword(0.01f);
						sepoatesari = true;
					}
					for (int i = 0; i < obiecte.size(); i++) {
						if (hasCollision(obiecte.at(i))) {
							coliziune = true;
							if (camera.getTargetPosition()[1] <= obiecte.at(i)->p1.y) {
								subobiect = true;
								jump = 0;
							}
							if (camera.getTargetPosition()[1] >= obiecte.at(i)->p2.y)
								peobiect = true;
							break;
						}
					}
					if (!peobiect && jump == 0) {
						camera.translateUpword(-0.1f);
						cameraFPS.translateUpword(-0.1f);
						sepoatesari = false;
					}
					else {
						if (jump == 0)
							sepoatesari = true;
						if (jump > 0) {
							camera.translateUpword(0.1f);
							cameraFPS.translateUpword(0.1f);
							--jump;
						}
					}
				}
			}
		}

		void notifyReshape(int width, int height, int previos_width, int previous_height)
		{
			//blackbox needs to know
			BLACKBOX.notifyReshape(width, height);
			aspectRatio = (float)width / height;

		}

		// Mouse drag, mouse button pressed 
		void notifyMouseDrag(int mouse_x, int mouse_y) { }

		// Mouse move without pressing any button
		void notifyMouseMove(int mouse_x, int mouse_y) { }

		// Mouse button click
		void notifyMouseClick(int button, int state, int mouse_x, int mouse_y) { }

		// Mouse scrolling
		void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y) { }
};

int main()
{
	// Initialize GLUT: window + input + OpenGL context
	lab::glut::WindowInfo window(std::string("EGC Laborator 5 - Camera and Projections"), GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 80, 0, 0, true);
	lab::glut::ContextInfo context(3, 3, false);
	lab::glut::FramebufferInfo framebuffer(true, true, false, false);
	lab::glut::init(window, context, framebuffer);

	// Initialize GLEW + load OpenGL extensions 
	glewExperimental = true;
	glewInit();
	std::cout << "[GLEW] : initializare" << std::endl;

	// Create a new instance of Lab and listen for OpenGL callback
	// Must be created after GLEW because we need OpenGL extensions to be loaded

	Laborator5 *lab5 = new Laborator5();
	lab::glut::setListener(lab5);

	// Enter loop
	lab::glut::run();

	return 0;
}