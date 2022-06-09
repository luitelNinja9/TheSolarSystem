#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<stack>
#include<vector>

#ifndef STARS
#define STARS

using namespace std;

class Star
{
private:

	float scale;
	const char* textureString;
	float angularSpeed;



public:
	stack<glm::mat4> stackVariable;
	float mass;
	

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration; 

	Star(int scale_, float angularSpeed_,const char* texString_,glm::vec3 position_, glm::vec3 velocity_ = glm::vec3(0.0f));
	const char* getTextureString();
	const float getScale();
	const float getAngularSpeed();
	glm::mat4 translateMatrix();
	glm::vec3 positionVec();
	glm::vec3 scaleVec();
	glm::vec3 accelerationVec();
	glm::vec3 velocityVec();
	
}; 
class Sattelite
{
private:

	float scale;
	float angularSpeed;
	float revolutionSpeed;

	//a and b for ellipse
	float distance1;
	float distance2;



public:
	stack<glm::mat4> stackVariable;


	Sattelite(int scale_, float angularSpeed_, float distance1_, float distance2_, float revolution_);
	const float getScale();
	const float getAngularSpeed();
	const float getRevolutionSpeed();
	const float getDistance1();
	const float getDistance2();
	glm::vec3 scaleVec();
};


class Planet
{
private:

	float scale;
	float angularSpeed;
	float revolutionSpeed;

	//a and b for ellipse
	float distance1;
	float distance2;
	int sattelite;


public:
	stack<glm::mat4> stackVariable;
	vector<Sattelite> sats;


	Planet(int scale_, float angularSpeed_, float distance1_, float distance2_, float revolution_,vector <Sattelite> sats_,
		int Sattelite = 0);
	const float getScale();
	const float getAngularSpeed();
	const float getRevolutionSpeed();
	const float getDistance1();
	const float getDistance2();
	const int withSattelite();
	glm::vec3 scaleVec();
}; 



#endif 