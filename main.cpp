
//####SunEarthMoon####//
//Step 0 : Include files and Definitions
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Utils.h"
#include "Sphere.h"
#include<stack>
#include<iostream>
#include<vector>
#include "Stars.h"
//#include "Gravity.h"


float zoomFeature = 1;
float zoomSensitivity = 0.1f;
float moveSensitivity = 0.5f;

//
std::vector<Star>stars;
std::vector<Planet>planets;


Star sun = Star(3, 0.3f, "8k_sun.jpg", glm::vec3(0.0f, 0.0f, 0.0f));
Planet mercury = Planet(4, 1.2f, 4.2f, 3.0f,0.8f);
Planet venus = Planet(4, 1.3f, 5.7f, 4.0f,0.7f);
Planet earth = Planet(5, 1.4f, 6.9f, 5.0f,0.6f);
Planet mars = Planet(3, 1.5f, 7.9f, 6.0f,0.5f);
Planet jupyter = Planet(10, 1.5f, 9.5f, 9.0f,0.4f);
Planet saturn = Planet(8, 1.5f, 11.7f, 10.5f,0.3f);
Planet uranus = Planet(7, 1.6f, 12.5f, 11.8f,0.2f);
Planet neptune = Planet(6, 1.7f, 13.5f, 13.0f,0.1f);

GLuint planet_textures[8];


void installLights(glm::mat4 vMatrix);


#define numVAOs 1
#define numVBOs 5
//using namespace std;



//window
//int width, height;

//int addStar_;

double xpos, ypos;

//button
int normalView = 1;
int onHoverView = 2;



float cameraX, cameraY, cameraZ;
Sphere mySphere(48);

int renderingProgram,backgroundProgram;
//GLuint renderingProgramUI;


GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Variable used in display
GLuint mvLoc, projLoc,vLoc, sunTexture, moonTexture, earthTexture,menuButtonTex,skyBackgroundTexture;
GLuint planetTexture;

int width, height;
int button = 1;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat,oMat;
//L
glm::mat4 invTrMat;
glm::vec3 currentLightPos,lightPosV;

//L
//Location for shader uniform variable
GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mAmbLoc, mDiffLoc, mSpecLoc, mShiLoc,buttonLoc;
glm::vec3 initialLightLoc = glm::vec3(0.0f, 0.0f, -0.0f);
float lightPos[3];
//L
//sun light properties
float globalAmbient[4] = { 0.8f,0.8f,0.8f,1.0f };
float lightAmbient[4] = { 0.1f,0.1f,0.1f,1.0f };
float lightDiffuse[4] = { 0.6f,0.4f,0.4f,1.0f };
float lightSpecular[4] = { 0.6f,0.4f,0.4f,1.0f };

//Earth material Property

float previous, now, radius, dt;



//Called from init
void setupVertices(void)
{
	//Uncomment For Adding sample Button
	float cubePositions[108] =
	{
		 -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		 -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		  1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};
	

	float cubeTextureCoord[72] = {
			 1.00f, 0.66f, 1.00f, 0.33f, 0.75f, 0.33f,
			 // back face lower right
			0.75f, 0.33f, 0.75f, 0.66f, 1.00f, 0.66f,
					// back face upper left
			0.75f, 0.33f, 0.50f, 0.33f, 0.75f, 0.66f,
						   // right face lower right
			0.50f, 0.33f, 0.50f, 0.66f, 0.75f, 0.66f,
								  // right face upper left
			0.50f, 0.33f, 0.25f, 0.33f, 0.50f, 0.66f,
										 // front face lower right
			0.25f, 0.33f, 0.25f, 0.66f, 0.50f, 0.66f,
												// front face upper left
			0.25f, 0.33f, 0.00f, 0.33f, 0.25f, 0.66f,
													   // left face lower right
			 0.00f, 0.33f, 0.00f, 0.66f, 0.25f, 0.66f,
															  // left face upper left
			0.25f, 0.33f, 0.50f, 0.33f, 0.50f, 0.00f,
																	 // bottom face upper right
			0.50f, 0.00f, 0.25f, 0.00f, 0.25f, 0.33f,
																			// bottom face lower left
		 0.25f, 1.00f, 0.50f, 1.00f, 0.50f, 0.66f,
																				   // top face upper right
		0.50f, 0.66f, 0.25f, 0.66f, 0.25f, 1.00f
																						  // top face lower left
};
/*
	float menuButton[72] =
	{
		//0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
		//1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,
		0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
		1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,

		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,


		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	};

	*/




	std::vector<int> ind = mySphere.getIndices();
	std::vector<glm::vec3> vert = mySphere.getVertices();
	std::vector<glm::vec2> tex = mySphere.getTexCoords();
	std::vector<glm::vec3> norm = mySphere.getNormals();




	std::vector<float>pvalues;
	std::vector<float>tvalues;
	std::vector<float>nvalues;

	int numIndices = mySphere.getNumIndices();

	for (int i = 0; i < numIndices; i++)
	{
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);

		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}



	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	//Sphere vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	//tex Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);


	//Uncomment for sample Button
	//cube
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions) , cubePositions, GL_STATIC_DRAW);

	//cube Texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTextureCoord) , cubeTextureCoord, GL_STATIC_DRAW);
}

//Step 4 : Init(Definition)  :: Application Specific initialization
//Buffers are created in init or at start of the program
//In OpenGL buffer is contained in Vertex Buffer Object(VBO)
//VAOs are vertex array objects helping to manipulate buffers in complex scenes
//OpenGL requires atleast one VAO to be created
//Create matrices that donot change in init:perspective matrix
void init(GLFWwindow* window)
{
	//Create thr program and save it in a global variable
	renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
	backgroundProgram = createShaderProgram("vertShaderBackground.glsl", "fragShaderBackground.glsl");

	//renderingProgramUI = createShaderProgram("vertShaderB.glsl", "fragShaderB.glsl");
	cameraX = 0.0f; cameraY = -0.5f; cameraZ = 8.0f;
	setupVertices();

	sunTexture = loadTexture("textures/8k_sun.jpg");
	moonTexture = loadTexture("textures/8k_moon.jpg");
	earthTexture = loadTexture("textures/2k_earth_daymap.jpg");

	planet_textures[0] = loadTexture("textures/2k_mercury.jpg");
	planet_textures[1] = loadTexture("textures/2k_venus_atmosphere.jpg");
	planet_textures[2] = loadTexture("textures/2k_earth_daymap.jpg");
	planet_textures[3] = loadTexture("textures/2k_mars.jpg");
	planet_textures[4] = loadTexture("textures/2k_jupiter.jpg");
	planet_textures[5] = loadTexture("textures/2k_saturn.jpg");
	planet_textures[6] = loadTexture("textures/2k_uranus.jpg");
	planet_textures[7] = loadTexture("textures/2k_neptune.jpg");

	//skyBackgroundTexture = loadCubeMap("textures/2k_stars_milky_way");
	skyBackgroundTexture = loadTexture("textures/8k_stars_milky_way.jpg");
	// folder containing the skybox textures
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);


	//planetTexture = loadTexture("2k_earth_daymap.jpg");
	//menuButtonTex = loadTexture("Menu.png");


	//Stars to draw
	stars.push_back(sun);

	//Planets to draw
	planets.push_back(mercury);
	planets.push_back(venus);
	planets.push_back(earth);
	planets.push_back(mars);
	planets.push_back(jupyter);
	planets.push_back(saturn);
	planets.push_back(uranus);
	planets.push_back(neptune);

}


void display(GLFWwindow* window, double currentTime)
{
	
	//Clear also the depth buffer , Place color in the color buffer, Clear the buffer and Place "clear color" in the buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Send data from OpenGl application to uniform variable
//1.Acquire a reference to  uniform variable
	

	glUseProgram(backgroundProgram);
	mvLoc = glGetUniformLocation(backgroundProgram, "mv_matrix");
	projLoc = glGetUniformLocation(backgroundProgram, "proj_matrix");


	//
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cameraX, cameraY, cameraZ));
	// build the MODEL-VIEW matrix
	mvMat = vMat * mMat;

	glfwGetFramebufferSize(window, &width, &height);
	aspect = float(width) / float(height);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);//1.0472f = 60 degrees


	


	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));



	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);



	// make the cube map the active texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyBackgroundTexture);
	// disable depth testing, and then draw the cube map
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	
	glDisable(GL_DEPTH_TEST);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glEnable(GL_DEPTH_TEST);

	
	//Loads the program containing two compiled shaders into OpenGL pipeline stages(GPU)




	glUseProgram(renderingProgram);


	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	GLuint nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

	//Build Perspective matrix
	//glfwGetFramebufferSize(window, &width, &height);
	//aspect = float(width) / float(height);
	//pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);//1.0472f = 60 degrees
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//Build view,model and model-view matrix
	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, cameraZ - 2.00f));
	//vMat *= glm::translate(glm::mat4(1.0f), glm::vec3(cameraX +1.8f,cameraY +1.0f, cameraZ-2.00f));


	//oMat = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(oMat));

	//delete
	//vMat = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f,0.0f,100.0f);

	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(1742.50f,1080.0f-55.0f, 0.0f));
	//vMat *= glm::scale(glm::mat4(1.0f), glm::vec3(137.50f, 30.0f, 1.0f));
	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(1.7f, 1.05f, -2.0f));
	//vMat *= glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.065f, 0.03f));

	//invTrMat = glm::transpose(glm::inverse(vMat));

	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vMat));
	//L
	//glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));



	/*
	//Uncomment to add Sample clickable button
	//Buttons
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//Menu Button
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, menuButtonTex);

	//button = normalView;
	buttonLoc = glGetUniformLocation(renderingProgram, "button");
	glProgramUniform1i(renderingProgram, buttonLoc, button);


	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, planetTexture);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);



	glDrawArrays(GL_TRIANGLES, 0, 36);

	*/


	//Build view,model and model-view matrix
	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));


	//L
	//Light Position
	currentLightPos = glm::vec3(initialLightLoc.x, initialLightLoc.y, initialLightLoc.z);
	installLights(vMat);



	//sun.stackVariable
	//calculateMotionParameters();
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	//button = 0;
	//buttonLoc = glGetUniformLocation(renderingProgram, "button");
	//glProgramUniform1i(renderingProgram, buttonLoc, button);

	//stars_copy = stars;
	//calculateMotionParameters(stars,stars_copy);

	for (int i = 0; i < stars.size(); i++)
	{//The sun

		stars[i].stackVariable.push(vMat);
		stars[i].stackVariable.push(stars[i].stackVariable.top());
		stars[i].stackVariable.top() *= glm::translate(glm::mat4(1.0f), stars[i].positionVec() * zoomFeature);
		stars[i].stackVariable.push(stars[i].stackVariable.top());
		stars[i].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * stars[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*2.0f, zoomFeature * 2.0f, zoomFeature * 2.0f));
		stars[i].stackVariable.top() *= glm::scale(glm::mat4(1.0f), stars[i].scaleVec() * zoomFeature);

		//L
		invTrMat = glm::transpose(glm::inverse(stars[i].stackVariable.top()));
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));


		//Uncomment to see the lower surface
		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[i].stackVariable.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sunTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		//glBindTexture(GL_TEXTURE_2D, 0);
		stars[i].stackVariable.pop();
		//}
	}



	//Planets
	float r = 0.9f;

	///*
	for (int i = 0; i < planets.size(); ++i)
	{

		stars[0].stackVariable.push(stars[0].stackVariable.top());
		stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * planets[i].getRevolutionSpeed()) * 2.0f * planets[i].getDistance1() * zoomFeature,
			0.0f, cos(float(currentTime) * planets[i].getRevolutionSpeed()) * 2.0f * planets[i].getDistance2() * zoomFeature));
		stars[0].stackVariable.push(stars[0].stackVariable.top());
		stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * planets[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * planets[i].getScale(), zoomFeature * planets[i].getScale(), zoomFeature * planets[i].getScale()));

		//L
		invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
		//L
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planet_textures[i]);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		stars[0].stackVariable.pop();
		stars[0].stackVariable.pop();
		r = r - 0.1f;
	}
	//*/


	/*



	//The  Earth
		stars[0].stackVariable.push(stars[0].stackVariable.top());
		stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * 0.5f) * 6.0f *zoomFeature,
		0.0f , cos(float(currentTime) * 0.5f) * 6.0f *zoomFeature));
		stars[0].stackVariable.push(stars[0].stackVariable.top());
		stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime), glm::vec3(0.0f, 1.0f, 0.0f));
		stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*0.2f, zoomFeature*0.2f, zoomFeature*0.2f));

	//L
	invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
	//L
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//L
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
	stars[0].stackVariable.pop();

	//The Cube Moon
	stars[0].stackVariable.push(stars[0].stackVariable.top());
	stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * 2.0f) * 0.5f * zoomFeature, 0.5f * zoomFeature, cos(float(currentTime) * 2.0f) * 0.5f * zoomFeature));
	stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*0.05f, zoomFeature*0.05f, zoomFeature * 0.05f));

	//L
	invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//L
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, moonTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
	stars[0].stackVariable.pop();	stars[0].stackVariable.pop();	stars[0].stackVariable.pop();	stars[0].stackVariable.pop();
	*/
	for (int i = 1; i < stars.size(); ++i)
	{
		stars[i].stackVariable.pop();
		stars[i].stackVariable.pop();
	}



	//button = normalView;
	//glProgramUniform1i(renderingProgram, buttonLoc, button);




	
	



}


void installLights(glm::mat4 vMatrix)
{
	lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = lightPosV.x;
	lightPos[1] = lightPosV.y;
	lightPos[2] = lightPosV.z;

	//get Location
	// get the locations of the light and material fields in the shader
	globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
	ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
	diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
	specLoc = glGetUniformLocation(renderingProgram, "light.specular");
	posLoc = glGetUniformLocation(renderingProgram, "light.position");

	// set the uniform light and material values in the shader
	glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
	glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
	glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
	glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
	glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset > 0)
	{
		zoomFeature += zoomSensitivity;
	}
	else if (yoffset < 0)
	{
		zoomFeature -= zoomSensitivity;
	}

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS) ) cameraY += moveSensitivity;
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS) ) cameraY += moveSensitivity;
	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY -= moveSensitivity;
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY -= moveSensitivity;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraX += moveSensitivity;
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraX -= moveSensitivity;
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraZ -= moveSensitivity;
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraZ += moveSensitivity;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if ((xpos >= 1605 && xpos <= 1880) && (ypos >= 26 && ypos <= 85))
		button = onHoverView;
}





//Simple Function to add Star
//void addStar()
//{
//	stars.push_back(Star(3, 0.6f, "8k_sun.jpg", glm::vec3(cameraX, cameraY+0.5, cameraZ-8.0),glm::vec3(-0.0f,0.0f,-2.0f)));
//}


//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if ((xpos >= 1605 && xpos <= 1880) && (ypos >= 25 && ypos <= 85))
//	{
//		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) addStar();
//
//	}


//}

int main(void)
{
	//Step 1 : Init Graphics Library Framework
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	//Step 2 : Instantiate GLFWwindow
	//1.window hint to specify version(major and minor) from function
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//2.create window object from Class and function
	//GLFWwindow* window = glfwCreateWindow(1920, 1010, "SunEarthMoon!", NULL, NULL); //Last two parameters allow for Full screen and resource sharing
	//GLFWmonitor* monitor = glfwGetWindowMonitor(window);
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "SunEarthMoon", monitor, NULL);
																					//3.make window context current from function
	glfwMakeContextCurrent(window);

	//Step 3 : Initialize openGL Extension Wrangler(GLEW)
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	//Vertical synchronization
	glfwSwapInterval(1);

	//Step 4 :  Init(Call)
	init(window);
	//float xscale, yscale;




	glfwGetWindowSize(window, &width, &height);
	//Step 5 : display(Call) - glfws
	//1.Loop for closing window
	while (!glfwWindowShouldClose(window)) {
		//Mouse Scroll Zoom Feature
		glfwSetScrollCallback(window, scroll_callback);
		//Key Input
		glfwSetKeyCallback(window, key_callback);
		//Onclick button


		//window
		//glfwGetWindowSize(window, &width, &height);
		//glfwSetMouseButtonCallback(window, mouse_button_callback);
		//glfwSetCursorPosCallback(window, cursor_position_callback);


		//glfwGetCursorPos(window, &xpos, &ypos);
		//if ((xpos >= 1605 && xpos <= 1880) && (ypos >= 25 && ypos <= 85))
		//{
		//	button = onHoverView;
		//}
		//cout<<xpos<<',' << ypos<<endl;
		//displayText();
		//2.Display window
		display(window, glfwGetTime());//glfwGetTime returns elapsed time since GLFW was initialized
	//3.Swap buffers ,Vertical synchronization :: Paints the screen
		glfwSwapBuffers(window);
		//4.Poll events, Handles events like key Press
		glfwPollEvents();
	}

	//Step 6 : Destroy the window and terminate
	//1.Distroy window
	glfwDestroyWindow(window);
	//2.Terminate
	glfwTerminate();
	exit(EXIT_SUCCESS);
}