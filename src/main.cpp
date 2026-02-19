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

// Force the use of the high-performance GPU on systems with dual graphics
extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // For NVIDIA
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

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

    // Create and initialise VAO, VBO and EBO
    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Load and compile shaders
    Shader shaderProgram("../assets/shaders/default.vert", "../assets/shaders/default.frag");
    shaderProgram.Activate(); 

    GLuint scaleLoc = glGetUniformLocation(shaderProgram.ID, "scale"); // Get the location of the "scale" uniform variable in the shader program

    //Texture
    Texture texture("../assets/textures/brick.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.BindTextureUnitToShader(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double previousTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Check for Esc key press
        processInput(window);

        // Clear the screen with a specific color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers

        shaderProgram.Activate();

        double currentTime = glfwGetTime();
        if (currentTime - previousTime >= 0.01) // Rotate every 10ms
        {
            rotation += 0.5f; // Rotate by 0.5 degrees
            if (rotation >= 360.0f)
                rotation -= 360.0f; // Keep rotation within [0, 360]
            previousTime = currentTime;
        }

        glm::mat4 model = glm::mat4(1.0f); 
        glm::mat4 view = glm::mat4(1.0f); 
        glm::mat4 projection = glm::mat4(1.0f); 

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around the Y-axis

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1f(scaleLoc, 1.0f); // Set the scale uniform
        texture.Bind();
        vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0); // Draw the object using the indices defined in the EBO
 
        // Swap buffers (Double Buffering) and poll for window events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    texture.Delete();
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