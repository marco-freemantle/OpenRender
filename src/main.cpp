#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/Shader.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"

// Force the use of the high-performance GPU on systems with dual graphics
extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // For NVIDIA
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Initialise GLFW and set OpenGL version/profile hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // Create and initialise VAO, VBO and EBO
    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Load and compile shaders
    Shader shaderProgram("../assets/shaders/default.vert", "../assets/shaders/default.frag");
    shaderProgram.Activate(); 

    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Check for Esc key press
        processInput(window);

        // Clear the screen with a specific color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the object
        shaderProgram.Activate();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Execute the draw call
 
        // Swap buffers (Double Buffering) and poll for window events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
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