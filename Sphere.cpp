#include<cmath>
#include<vector>
#include<iostream>
#include<glm/glm.hpp>
#include "Sphere.h"
using namespace std;



Sphere::Sphere(int prec)
{
	init(prec);
}

float Sphere::toRadians(float degrees)
{
	return (degrees * 2.0f * 3.14159f) / 360.0f;
}

void Sphere::init(int prec)
{
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;

	for (int i = 0; i < numVertices; i++)
	{
		vertices.push_back(glm::vec3());
	}
	for (int i = 0; i < numVertices; i++)
	{
		texCoords.push_back(glm::vec2());
	}
	for (int i = 0; i < numVertices; i++)
	{
		normals.push_back(glm::vec3());
	}
	for (int i = 0; i < numIndices; i++)
	{
		indices.push_back(0);
	}
	//calculate Triangle verices

	for (int i = 0; i <= prec; i++)
	{
		for (int j = 0; j <= prec; j++)
		{
			float y = float(cos(toRadians(180.0f - i * 180.0f / prec)));
			float x = -float(cos(toRadians(j * 360.0f / prec))) * float(abs(cos(asin(y))));
			float z = float(sin(toRadians(j * 360.0f / prec))) * float(abs(cos(asin(y))));

			int ij = i * (prec + 1) + j;
			vertices[ij] = glm::vec3(x, y, z);
			texCoords[ij] = glm::vec2((float(j) / prec), (float(i) / prec));
			normals[ij] = glm::vec3(x, y, z);
		}
	}

	//calculate triangle indices
	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			int ij0 = 6 * (i * prec + j) + 0;
			int ij1 = 6 * (i * prec + j) + 1;
			int ij2 = 6 * (i * prec + j) + 2;
			int ij3 = 6 * (i * prec + j) + 3;
			int ij4 = 6 * (i * prec + j) + 4;
			int ij5 = 6 * (i * prec + j) + 5;
			indices[ij0] = i * (prec + 1) + j;
			indices[ij1] = i * (prec + 1) + j + 1;
			indices[ij2] = (i + 1) * (prec + 1) + j;
			indices[ij3] = i * (prec + 1) + j + 1;
			indices[ij4] = (i + 1) * (prec + 1) + j + 1;
			indices[ij5] = (i + 1) * (prec + 1) + j;
		}
	}

}

//accessors
int Sphere::getNumVertices() { return numVertices; }
int Sphere::getNumIndices() { return numIndices; }
std::vector<int> Sphere::getIndices() { return indices; }
std::vector<glm::vec3> Sphere::getVertices() { return vertices; }
std::vector<glm::vec2> Sphere::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Sphere::getNormals() { return normals; }