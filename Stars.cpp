#include "Stars.h"
#include<iostream>


using namespace std;



Star::Star(int scale_=1, float angularSpeed_=1.0f,const char* texString_="8k_sun.jpg", glm::vec3 position_ = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 velocity_)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		Star::scale = float(scale_)/2.0f;
	}
	else
	{
		Star::scale=float(scale_);
	}
	Star:: textureString = texString_;
	Star::position = position_;
	Star::angularSpeed = angularSpeed_;
	Star::mass = pow(scale,3);
	Star::velocity = velocity_;
	Star::acceleration = glm::vec3(0.0f,0.0f,0.0f);
}


const char* Star::getTextureString()
{
	return textureString;
}

const float Star::getScale()
{
	return scale;
}

const float Star::getAngularSpeed()
{
	return angularSpeed;
}

glm::mat4 Star::translateMatrix()
{
	return glm::translate(glm::mat4(1.0f), Star::position);
}
glm::vec3 Star::positionVec()
{
	return Star::position;
}

glm::vec3 Star::velocityVec()
{
	return Star::velocity;
}

glm::vec3 Star::accelerationVec()
{
	return Star::acceleration;
}

glm::vec3 Star::scaleVec()
{
	return glm::vec3(scale,scale,scale);
}


Planet::Planet(int scale_= 1, float angularSpeed_=1.0f,float distance_ = 0.0f)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		Planet::scale = float(scale_)/2.0f;
	}
	else
	{
		Planet::scale=float(scale_);
	}

	
	Planet::scale = scale / 5.0f;

	Planet::angularSpeed = angularSpeed_;
	Planet::distance = distance_;
}


const float Planet::getScale()
{
	return scale;
}

const float Planet::getAngularSpeed()
{
	return angularSpeed;
}


glm::vec3 Planet::scaleVec()
{
	return glm::vec3(scale,scale,scale);
}
const float Planet::getDistance()
{
	return Planet::distance;
}


