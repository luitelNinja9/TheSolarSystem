#include<cmath>
#include<vector>
#include<glm/glm.hpp>

#ifndef SPHERE
#define SPHERE

class Sphere
{
private:
	int numVertices;
	int numIndices;
	std::vector<int>indices;
	std::vector<glm::vec3>vertices;
	std::vector<glm::vec2>texCoords;
	std::vector<glm::vec3>normals;
	void init(int);
	float toRadians(float degrees);


public:
	Sphere(int prec = 48);
	int getNumVertices();
	int getNumIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<int> getIndices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();




};










#endif // !SPHERE

