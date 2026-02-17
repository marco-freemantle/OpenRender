#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Force the use of the high-performance GPU on systems with dual graphics
extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // For NVIDIA
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// GLSL Vertex Shader: Processes each vertex's position. 
// "layout (location = 0)" matches the index we'll use in our VAO later.
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// GLSL Fragment Shader: Determines the color of the pixels (fragments).
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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

    // Create and compile the Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders into a single Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete individual shaders once linked; they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // Create Vertex Array Object
    glGenBuffers(1, &VBO);      // Create Vertex Buffer Object
    glGenBuffers(1, &EBO);      // Create Element Buffer Object

    // Bind the VAO first to "record" the following configurations
    glBindVertexArray(VAO);

    // Bind and fill the VBO with our vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and fill the EBO with our index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define how OpenGL should interpret the vertex data (the "Vertex Attribute")
    // Index 0, 3 values (vec3), Floats, Don't Normalise, Stride (12 bytes), Offset (0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable the attribute at location 0

    // Unbind VBO (safe to do after glVertexAttribPointer) and then VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    // Draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Check for Esc key press
        processInput(window);

        // Clear the screen with a specific color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the object
        glUseProgram(shaderProgram); // Use our compiled shaders
        glBindVertexArray(VAO);      // Re-bind the VAO (restores all VBO/attribute state)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Execute the draw call
 
        // Swap buffers (Double Buffering) and poll for window events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

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