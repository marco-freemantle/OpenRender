#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Shader.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include "Meshes/Cube.h"

// Force the use of the high-performance GPU on systems with dual graphics
extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // For NVIDIA
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // Initialise GLFW and set OpenGL version/profile hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenRender", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Enable VSync and lock FPS to your monitor's refresh rate
    glfwSwapInterval(1);
    // Register the resize callback to adjust the viewport dynamically
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD to manage OpenGL function pointers (must happen before calling any GL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    // Create shaders
    Shader shaderProgram("../assets/shaders/default.vert", "../assets/shaders/default.frag");

    // Create meshes
    Mesh cube1 = CreateCube();

    // Create textures
    Texture brick("../assets/textures/brick.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);

    // Create materials
    Material brickMaterial(&shaderProgram, &brick);
    Material redMaterial(&shaderProgram, nullptr, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    // Camera setup
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
    glEnable(GL_DEPTH_TEST);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Check for Esc key press
        processInput(window);

        // Clear the screen with a specific color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers

        camera.Input(window); // Handle camera input (movement and rotation)
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f, SCR_WIDTH, SCR_HEIGHT); // Update the camera matrix with the current parameters

        camera.Matrix(shaderProgram, "camMatrix"); // Send the camera matrix to the shader
        
        cube1.Draw(&brickMaterial);

        // Swap buffers (Double Buffering) and poll for window events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    cube1.Delete();
    brick.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    static bool wireframeMode = false;
    static bool rKeyPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (!rKeyPressed)
        {
            rKeyPressed = true;
            wireframeMode = !wireframeMode;
            
            if (wireframeMode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            
        }
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
    {
        rKeyPressed = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Adjust the rendering viewport whenever the window is resized
    glViewport(0, 0, width, height);
}