#ifndef MAIN_H
#define MAIN_H  1

/* headers required for main.c */
#include "../include/glew/glew.h"
#include "../include/glfw/glfw3.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

/* function declaration */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};
bool loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
std::string loadShaderSource(const std::string& filepath);
GLuint compileShader(GLenum type, const char* source);

#endif  /* MAIN_H */