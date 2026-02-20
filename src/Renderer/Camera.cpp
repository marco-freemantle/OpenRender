#include "Renderer/Camera.h"

Camera::Camera(int w, int h, glm::vec3 pos)
{
	Camera::width = w;
	Camera::height = h;
	Camera::position = pos;
	Camera::cameraMatrix = glm::mat4(1.0f);
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane, float width, float height)
{
	glm::mat4 view = glm::mat4(1.0f); // Initialise view matrix to identity
	glm::mat4 projection = glm::mat4(1.0f); // Initialise projection matrix to identity 

	Camera::width = width;
	Camera::height = height;

	// ===========================================================================
	// Model-View-Projection (MVP) Matrix Summary:
	// 
	// Model Matrix:
	//   - Transforms an object from its local (model) space into world space.
	//   - Applies position, rotation, and scale to place the object in the world.
	//
	// View Matrix:
	//   - Transforms from world space into view (camera) space.
	//   - Represents the camera's position and orientation in the scene.
	//   - Typically built using glm::lookAt(cameraPos, target, upVector).
	//
	// Projection Matrix:
	//   - Transforms from view space into clip space.
	//   - Defines the camera's lens (e.g. field of view, aspect ratio, near/far planes).
	//   - Usually created with glm::perspective(...) or glm::ortho(...).
	//
	// Final vertex transformation:
	//   gl_Position = projection * view * model * vec4(vertex, 1.0);
	//
	// ===========================================================================

	// Position = camera position in world space. Position + orientation = point the camera is looking at. Up = up vector for the camera
	view = glm::lookAt(position, position + orientation, up); // Create view matrix using camera position and orientation
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane); // Create projection matrix with perspective projection

	cameraMatrix = projection * view; // Combine projection and view matrices to form the camera matrix
}

void Camera::Input(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += currentSpeed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += currentSpeed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += currentSpeed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += currentSpeed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += currentSpeed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += currentSpeed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		currentSpeed += 0.0005f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		currentSpeed = baseSpeed;
	}


	// Handle mouse inputs //
	// Hides the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Normalises and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	// Calculates upcoming vertical change in the orientation
	glm::vec3 neworientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

	// Decides whether or not the next vertical orientation is legal or not
	if (abs(glm::angle(neworientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		orientation = neworientation;
	}

	// Rotates the orientation left and right
	orientation = glm::rotate(orientation, glm::radians(-rotY), up);

	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
	glfwSetCursorPos(window, (width / 2), (height / 2));
}