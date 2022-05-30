#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/soil2.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string readShaderSource(const char* filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";

	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint createShaderProgram()
{
	//1.Load codes for vertex and fragment shaders from files
	string vshaderSourceStr = readShaderSource("vertShader.glsl");
	string fshaderSourceStr = readShaderSource("fragShader.glsl");

	//Convert to character string because glShaderSource() fn is incompatible with string and it has also things to do with NULL at end of tha function
	const char* vshaderSource = vshaderSourceStr.c_str();
	const char* fshaderSource = fshaderSourceStr.c_str();

	//2.Create unique ints refering to shaders after creating empty shader objects
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);


	//3.Load GLSL codes from string to empty shader objects
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);

	//4.Compile Shaders
	glCompileShader(vShader);
	glCompileShader(fShader);

	//5.Create a program , save the integer that points to it ,attach the shaders to program , link to ensure they are compatible
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}

GLuint createShaderProgram(const char* vsPath, const char* fsPath)
{
	//1.Load codes for vertex and fragment shaders from files
	string vshaderSourceStr = readShaderSource(vsPath);
	string fshaderSourceStr = readShaderSource(fsPath);

	//Convert to character string because glShaderSource() fn is incompatible with string and it has also things to do with NULL at end of tha function
	const char* vshaderSource = vshaderSourceStr.c_str();
	const char* fshaderSource = fshaderSourceStr.c_str();

	//2.Create unique ints refering to shaders after creating empty shader objects
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);


	//3.Load GLSL codes from string to empty shader objects
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);

	//4.Compile Shaders
	glCompileShader(vShader);
	glCompileShader(fShader);

	//5.Create a program , save the integer that points to it ,attach the shaders to program , link to ensure they are compatible
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}


void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;

	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Program Info Log:" << log << endl;
		free(log);
	}

}

GLuint loadTexture(const char* texImagePath)
{
	GLuint textureID;
	textureID = SOIL_load_OGL_texture(texImagePath,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//if anisotropic filtering
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}


	return textureID;
}









