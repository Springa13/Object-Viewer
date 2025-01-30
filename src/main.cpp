#include "main.h"

int main() {
    const int width = 1400;
    const int height = 800;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Load OBJ", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    const std::string vertexShaderSource = loadShaderSource("shaders/vertex_shader.glsl");
    const std::string fragmentShaderSource = loadShaderSource("shaders/fragment_shader.glsl");

    // Compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load OBJ file
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    if (!loadOBJ("models/model.obj", vertices, indices)) {
        return -1;
    }

    // Create buffers and arrays
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // TexCoords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    float angleY = glm::radians(0.0);
    float angleZ = glm::radians(0.0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        float moveSpeed = (viewport[2] + viewport[3]) / 800;
        
        if (glfwGetKey(window, GLFW_KEY_UP) == (GLFW_PRESS || GLFW_REPEAT)) {
            angleZ = angleZ + glm::radians(moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == (GLFW_PRESS || GLFW_REPEAT)) {
            angleZ = angleZ + glm::radians(-moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == (GLFW_PRESS || GLFW_REPEAT)) {
            angleY = angleY + glm::radians(moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == (GLFW_PRESS || GLFW_REPEAT)) {
            angleY = angleY + glm::radians(-moveSpeed);
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);

        // Update the projection matrix to account for the new aspect ratio
        float aspectRatio = static_cast<float>(width) / height;
        
        // Set transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f));  
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    
        model = glm::rotate(model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


// Function to load .obj file
bool loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texCoords;
    std::vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            temp_positions.push_back(position);
        } else if (prefix == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            temp_texCoords.push_back(texCoord);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        } else if (prefix == "f") {
            unsigned int posIndex[3], texIndex[3], normIndex[3];
            char slash;

            for (int i = 0; i < 3; i++) {
                iss >> posIndex[i] >> slash >> texIndex[i] >> slash >> normIndex[i];
                vertexIndices.push_back(posIndex[i]);
                texCoordIndices.push_back(texIndex[i]);
                normalIndices.push_back(normIndex[i]);
            }
        }
    }

    // Process loaded data into vertices and indices
    for (size_t i = 0; i < vertexIndices.size(); i++) {
        Vertex vertex;
        vertex.position = temp_positions[vertexIndices[i] - 1];
        vertex.texCoords = temp_texCoords[texCoordIndices[i] - 1];
        vertex.normal = temp_normals[normalIndices[i] - 1];
        vertices.push_back(vertex);
        indices.push_back(i);
    }

    return true;
}

// Function to read shader source code from a file
std::string loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to compile shader
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }
    return shader;
}