#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	glm::vec3 position; // Camera position in world space
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f); // Camera orientation (direction it is facing)
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up vector for the camera
	glm::mat4 cameraMatrix; // Camera matrix for transformations

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	int width, height;
	float baseSpeed = 0.003f; // Movement speed of the camera
	float currentSpeed = baseSpeed; // Current speed, can be modified by holding shift
	float sensitivity = 50.0f; // Mouse sensitivity for camera rotation

	Camera(int w, int h, glm::vec3 pos);

	void Matrix(Shader& shader, const char* uniform);
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane, float width, float height);
	void Input(GLFWwindow* window);
};