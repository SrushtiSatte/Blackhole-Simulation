cmake_minimum_required(VERSION 3.15)
project(BlackHole3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLUT (FreeGLUT from vcpkg)
find_package(GLUT REQUIRED)

# Find GLM
find_package(glm CONFIG REQUIRED)

add_executable(BlackHole3D
    src/main.cpp
)

target_link_libraries(BlackHole3D
    OpenGL::GL
    GLUT::GLUT
    glm::glm
)
