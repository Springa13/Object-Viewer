# Construction of a 3D Object Viewer Using OpenGL

## Challenges:
- Initialising a C++ OpenGL project
- Using external libraries
- CMake construction and utilisation
- OpenGL programming (shaders, etc.)

## Initialising a C++ OpenGL Project

The goal of the project was to be able to familiarise myself with OpenGL, specifically the default configuration of OpenGL using C++ as the programming language. It was also intended that the project be attempted without the use of IDEs that simplify the process of compilation, specifically with regards to how external libraries are included in the project. Because of this, Visual Studio was not used, and instead VS Code was used without any extensions outside of the usual C++ linting tools. 

The resulting program was an OpenGL program that can load a .obj file and display it inside a window. The object can be rotated through the arrow keys to inspect it. Although the objects material is not yet shown, it is intended that the program can be a base for additions such as working with assimp to load materials on to an object, and also for the eventual development of a digital twin interface that receives external input from another source and rotates the object (with material) in accordance to a specific frame of reference.

The first step was to create the necessary environment and directory system to be able to run the program. The project directory was assembled in the following way:
```bash
├── src
│   ├── main.cpp
├── include
│   ├── glew/glew.h
│   ├── glfw/glfw.h
│   ├── glm/...
├── lib
│   ├── glew32.lib
│   ├── glfw3.lib
│   ├── OpenGL32.lib
├── models
│   ├── model.obj
├── shaders
│   ├── vertex_shaders.glsl
│   ├── fragment_shaders.glsl
├── build
└── CMakeLists.txt
```
Using this project structure, it was expected that it would simplify the process of differentiating my tasks and the overall build of the program.

           

## Using External Libraries

The second task that was undertaken was to gather the external libraries required for the program and structure them in a way that they could be compiled into the binary. The libraries used in the program were GLEW, GLFW, and GLM. 

### GLEW

GLEW is the OpenGL Extension Wrangler which is an extension loading library. It provides mechanisms to determine which OpenGL extensions are supported on the target platform. To use this library in my project I required the single header file glew.h which was placed in the include folder and the glew32.lib file which was placed in the lib folder.

In my main.cpp file, all that had to be included for GLEW to work was to include it at the top of the program and initialise it. I achieved this through the following code:
```c++
#include  "../include/glew/glew.h"
...
int main() {
	...
	// below window creation
	if  (glewInit()  !=  GLEW_OK)  {
		std::cerr <<  "Failed to initialize GLEW"  <<  std::endl;
		return  -1;
	}
	...
}
```

### GLFW

GLFW (Graphics Library Framework) is the most important library used in the program which provides a simple API for creating windows, contexts and surfaces, receiving inputs and events.

Similar to GLEW, GLFW requires both the glfw3.h header file and the glfw3.lib library to be able to run the program. In main.cpp, GLFW was used as follows:
```c++
#include  "../include/glfw/glfw3.h"
int main() {
	if  (!glfwInit())  {
		std::cerr <<  "Failed to initialize GLFW"  <<  std::endl;
		return  -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,  GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow*  window  =  glfwCreateWindow(800,  600,  "Load OBJ",  nullptr,  nullptr);
	if  (!window)  {
		std::cerr <<  "Failed to create GLFW window"  <<  std::endl;
		glfwTerminate();
		return  -1;
	}
	glfwMakeContextCurrent(window);
}
```  

### GLM

GLM is a header only mathematics library for OpenGL. In the program, the base glm.hpp, matrix_transform.hpp, and the type_ptr.hpp header files were included. The code utilising these utilities is shown below:
```c++
#include  "../include/glm/glm.hpp"
#include  "../include/glm/gtc/matrix_transform.hpp"
#include  "../include/glm/gtc/type_ptr.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};
...
bool loadOBJ() {
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texCoords;
	...
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
}
...
int main() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	...
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
``` 

## CMake Construction and Utilisation

The build system for the project is CMake. CMake is a cross-platform tool to build applications via compiler independent instructions. CMake is the primary build system used for many C++ programs so it is a valuable tool to learn for almost every C++ project. To use CMake, a CMakeLists.txt file is created with instructions that can then be used by cmake to produce a Makefile compatible with the system it is running on, this is the advantage of using CMake and not writing a Makefile directly. Once the Makefile is created, make is used to build the binaries which can then be executed directly. The CMakeLists.txt created for the project is shown in Appendix B.

## OpenGL Programming

With OpenGL programming being very unfamiliar as well as C++ in general also being unfamiliar, approaching the coding of the program was very difficult. While I have prior knowledge of C, some concepts in C++ are different enough to make reading the code and knowing what higher-level abstractions are available to me a time-consuming task.

To begin breaking down the process of developing the program, an overview of the primary functions of the program. In total there are 4 functions used within the program.
- main
- loadObj
- loadShaderSource
- compileShader

To demonstrate the codes function, a line-by-line analysis of each of the functions will be conducted beginning with the main function

### main

First within the main function is the initialisation of the window using glfw. The code below demonstrates this:
```c++
const int width = 1400;
const int height = 800;

if (!glfwInit()) {
	std::cerr << "Failed to initialize GLFW" << std::endl;
	return -1;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window = glfwCreateWindow(width, height, "Object Viewer", nullptr, nullptr);
if (!window) {
	std::cerr << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
}
glfwMakeContextCurrent(window);
```
The width and height of the window is set using constants for a 1400x800 window. After this we check if glfw is initialised and is working using an if statement. If it is initialised the code progresses to where we set up some parameters through glfwWindowHint(). The major and minor OpenGL versions are set to 3.3 and the OpenGL profile is the core OpenGL distribution. 
After this the window is created and saved to the 'window' variable. We define the width, height and title of the window. We then check if the window has been created or not using another if statement. To show the created window, we then use glfwMakeContextCurrent(window) to set the OpenGL context of the specified window current on the calling thread.

Next, GLEW is initialised and is checked through an if statement if it is working.
```c++
if (glewInit() != GLEW_OK) {
	std::cerr << "Failed to initialize GLEW" << std::endl;
	return -1;
}
```
After the window has been initialised, it is necessary to initialise the shaders for the program. This is done using the code below:
```c++
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
```
First, the vertex and fragment shader string content are loaded through the use of the loadShaderSource function. These shaders are then passed into the compileShader function to build GL compliant shaders stored in GLuint format. After this, the shader program is created using the glCreateProgram() function and the vertex shader and fragment shaders are attached to this program, and linked to the GL context using the glAttachShader and glLinkProgram functions. After the shaders have been attached to the program, they can be deleted using the glDeleteShader function.

Once the shaders have been loaded, the object needs to be loaded. The format of the object is of the type .obj. To be able to properly use this object data within OpenGL, I was required to know two things, the format and meaning of the data within .obj files, as well as the format in which objects are displayed in OpenGL. For now, all we need to know is that the data required from the .obj files are the vertices and the indices.
```c++
std::vector<Vertex> vertices;
std::vector<unsigned int> indices;

if (!loadOBJ("models/model.obj", vertices, indices)) {
	return -1;
}
```
As shown in the above code, the vertices and indices are stored in their own variables, of which we acquire using the function loadOBJ, which will be explained later.

After loading the object file, it is time to set up three objects:
- VAO (Vertex Array Object)
- VBO (Vertex Buffer Object)
- EBO (Element Buffer Object)

VAO - The VAO stores the vertex attribute configuration and which VBO to use it with.

VBO - Used to store large amounts of vertices in GPU memory, this gives the vertex shader almost instant access to the vertices, making it extremely fast.

EBO - Used to store indices which helps OpenGL decide what vertices to draw. It allows reuse of vertices to decrease the size of VBOs and for faster compilation.
```c++
GLuint VAO, VBO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
```
To use the VAO, VBO, and EBO, the variables are created and the vertex arrays and buffers are created using glGenVertexArrays and glGenBuffers. All that is required to use the VAO is to use the glBindVertexArray to initialise the VAO, while the VBO and EBO require two steps. First the buffer is binded using glBindBuffer and the correct flag, and then the data within the buffer is set, for the VBO, vertices are selected, and for the EBO, the indices are selected.

Next, we have to tell OpenGL how to interpret the vertex data. We have to do this for the position attribute, the normal attribute and the textcoords attributes because these are the attributes that are found within the Vertex struct that we used to store the vertices in. For each attribute we use the glVertexAttribPointer function to specify which  attribute we want to configure, the size of the vertex attribute, the type of data, whether the data should be normalised, the stride (distance to next attribute), and the offset of where the attribute data begins. Each attribute array is enabled using glEnableVertexAttribArray.
```c++
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
```
After the initialisations for the OpenGL program, it is time to begin the program rendering loop. First angleY and angleZ are initialised for use within the loop, before the loop is entered until the window is closed by the user, a function by from GLFW named glfwWindowShouldClose.

Upon entering the render loop, we clear both the colour and depth buffers as a means of good practice for each frame, we then specify the shader program to be used, the previously created shaderProgram. From their, we grab information about the viewport from the GL function glGetIntegerv, passing the GL_VIEWPORT flag and saving the results to the viewport variable. Using width and height data found at the 3rd and 4th index of the viewport array, the movement speed is set according to a custom algorithm.

Next, arrow key presses are determined using the glfwGetKey function, and either angleZ or angleY are manipulated by increasing or decreasing its current position using moveSpeed as a means to adjust them.

After this, we get the current width and height of the viewport and we specify the updated aspect ratio. This is useful for the next key actions in the program, the transformations. The transformations used are the model, view, and projection, a commonly used series of matrix transformations to a model defined in vertex space, transforming it into clip space, also known as [MVP](https://jsantell.com/model-view-projection/). 

To define the model, a 4x4 identity matrix is used, which defines the objects place as the basic initialised version without any transformations. For the view, a translation in the z-axis of -0.5 which sets the object 0.5 units away from the camera (the camera cannot be moved but is initialised in the same position as the object). For the projection, a perspective projection matrix is used to simulate a realistic depth effect. The fov, aspect ratio, and clipping distances are passed to the perspective matrix. I use the calculated aspect ratio based on the size of the current window so I can maintain the same projection if the window size is manipulated by the user.

After initialising the MVP matrices, the model matrix is transformed using the rotate function, which rotates the model in the Y and Z axis according to the current arrow key presses. 

We then obtain the uniform GPU locations from the shader before sending the created matrices to the shader through the glUniformMatrix4fv() function. Finally the VAO is binded to the program to let OpenGL know what vertex data to use, the indexed geometry is then drawn, and the buffers are swapped (OpenGL uses two buffers, the front buffer is currently displayed and the back buffer is where the new frame is drawn), before calling glfwPollEvents which captures user input and processes window events.
```c++
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
```
After the rendering loop logic, upon the window being closes, the VAO, VBO, EBO and the window are deleted and terminated, stopping the program securely.
```c++
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteBuffers(1, &EBO);

glfwDestroyWindow(window);
glfwTerminate();
return 0;
```

### loadObj
loadObj is the function that loads the .obj file into vertices and indices. It takes a path to the file as a string and it uses the reference to the vertices and indices variables created in the main function. 
```c++
bool  loadOBJ(const  std::string&  path,  std::vector<Vertex>&  vertices,  std::vector<unsigned  int>&  indices)
```
A vertex is made made up of a position, normal, and texCoords (texture coordinates), as defined in the header file. We create the vectors to store these values as well as the corresponding indices. We open the file stream, and for each line parse the file through the use of how the .obj file is structured with "v", "vt", "vn", and "f" prefixes.
```c++
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
```
After this, the temporary positions, normals, texCoords and indices are pushed into the vertices and indices variables and the function exits with a true flag.
```c++
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
```

### loadShaderSource
The loadShaderSource function takes a shader filepath in the form of a string, opens the filestream and saves a shader into a buffer. This is used to load both the vertex and fragment shaders into the program.
```c++
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
```

### compileShader
The compileShader function takes an enumerable that indicates the type of shader to compile and a source (the shader string loaded using loadShaderSource). 
```c++
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
```

```




