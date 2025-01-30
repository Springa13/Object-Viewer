# Construction of a 3D Object Viewer Using OpenGL

## Challenges:
- Initialising a C++ OpenGL project
- Using external libraries
- CMake construction and utilisation
- OpenGL programming (shaders, etc.)

## Initialising a C++ OpenGL Project

The goal of the project was to be able to familiarise myself with OpenGL, specifically the default configuration of OpenGL using C++ as the programming language. It was also intended that the project be attempted without the use of IDEs that simplify the process of compilation, specifically with regards to how external libraries are included in the project. Because of this, Visual Studio was not used, and instead VS Code was used without any extensions outside of the usual C++ linting tools. 

The resulting program was an OpenGL program that can load a .obj file and display it inside a window. The object can be rotated through the arrow keys to inspect it. Although the objects material is not yet shown, it is intended that the program can be a base for additions such as working with assimp to load materials on to an object, and also for the eventual development of a digital twin interface that receives external input from another source and rotates the object (with material) in accordance to a specific frame of reference.

