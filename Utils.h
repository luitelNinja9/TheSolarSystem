#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

#ifndef UTILS
#define UTILS


string readShaderSource(const char* filePath);
GLuint createShaderProgram();
GLuint createShaderProgram(const char* vsPath, const char* fsPath);
void printShaderLog(GLuint shader);
GLuint loadTexture(const char* texImagePath);




#endif 
