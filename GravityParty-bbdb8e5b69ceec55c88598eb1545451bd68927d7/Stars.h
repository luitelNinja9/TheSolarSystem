#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<stack>

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


#endif