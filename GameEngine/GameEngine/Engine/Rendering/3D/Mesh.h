#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include <string>
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour; // use vec4 if you want to change the alpha
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	Material material;	
};

class Mesh {
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4> instances_); // tell opengl it's time to draw

private:
	void GenerateBuffers(); // generate and fill in vao and vbo
	SubMesh subMesh;
	bool printOnce = true;
	GLuint VAO, VBO; // VAO separates data, VBO holds data
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	//GLuint textureLoc;
	GLuint viewPositionLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc;
	GLuint matDiffuseMapLoc, matShininessLoc, matTransparencyLoc, matAmbientLoc, matDiffuseLoc, matSpecularLoc;
};
#endif

