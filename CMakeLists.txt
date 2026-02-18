cmake_minimum_required(VERSION 3.20)
project(OpenRender)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include GLFW. This will build GLFW as a library from its source folder.
# add_subdirectory runs the CMakeLists.txt inside external/glfw and makes the 'glfw' target available.
add_subdirectory(external/glfw)

# Define the main executable for the project.
# We include:
# - main.cpp, which contains our program logic
# - glad.c, which provides the implementation of the GLAD OpenGL loader
# Since glad.c is compiled directly into our executable, we don't need to link a separate GLAD library.
add_executable(OpenRender
    src/main.cpp
    src/stb.cpp
    src/Renderer/Shader.cpp
    src/Renderer/VBO.cpp
    src/Renderer/VAO.cpp
    src/Renderer/EBO.cpp
    src/Renderer/Texture.cpp
    external/glad/src/glad.c
)

# Tell the compiler where to find header files.
# glad/include contains glad.h, which declares all OpenGL functions.
# The compiler needs this so it knows the function signatures when compiling main.cpp and glad.c.
target_include_directories(OpenRender PRIVATE
    external/glad/include
    external/stb
    include
)

# Link the libraries needed for the program.
# - glfw: the library built from the GLFW sources
# - opengl32: the Windows OpenGL system library
# We don’t link GLAD because its code is already part of the executable.
target_link_libraries(OpenRender
    glfw
    opengl32
)
