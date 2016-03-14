//-------------------------------------------------------------------------------------------------
// Descriere: header camera
//
// Autor: Lucian Petrescu
// Data: 14 oct 2013
//-------------------------------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include <math.h>

#pragma once
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"


// Rotates a Point/Vector around the world OY (0, 1, 0) with a specific angle(radians)
// This just implements the rotation matrix around the world UP vector that we learned in the previous lab
// For rotating a vector/point around an axis use glm::rotate()
inline glm::vec3 RotateOY(const glm::vec3 Point, float radians)
{
	glm::vec3 R;
	R.x = Point.x * cos(radians) - Point.z * sin(radians);
	R.y = Point.y;
	R.z = Point.x * sin(radians) + Point.z * cos(radians);
	return R;
}

namespace lab
{
	class Camera
	{
	public:
		Camera()
		{
			position = glm::vec3(0, 0, 50);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 50;
		}

		Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
		{
			set(position, center, up);
		}

		~Camera()
		{ }

		void set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void moveForwardKeepOY(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			position += distance * dir;
		}

		void translateForward(float distance)
		{
			position += distance * forward;
		}

		void rotateFPS_OX(float angle)
		{
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, right);
			forward = glm::vec3((glm::vec4(forward, 1) * rot));
			right = glm::vec3((glm::vec4(right, 1) * rot));
			up = glm::cross(right, forward);
		}

		void rotateFPS_OY(float angle)
		{
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, up);
			forward = glm::vec3((glm::vec4(forward, 1) * rot));
			right = glm::vec3((glm::vec4(right, 1) * rot));
			up = glm::cross(right, forward);
			//std::cout << forward.x << " " << forward.y << " " << forward.z << "\n";
		}

		glm::mat4 getViewMatrix()
		{
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 getTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

		glm::vec3 getPosition()
		{
			return position;
		}

		glm::vec3 getForward()
		{
			return forward;
		}

	private:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}