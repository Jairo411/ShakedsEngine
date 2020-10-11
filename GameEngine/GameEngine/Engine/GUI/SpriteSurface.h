#ifndef SPRITESURFACE_HEADER
#define SPRITESURFACE_HEADER
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<vector>
#include<string>
#include "../Camera/Camera.h"


class Texturehandler;
struct Vertex {
	glm::vec2 position;
	glm::vec2 textureCoordinates;
};

class SpriteSurface
{
public:
	SpriteSurface(std::string name_,float scale_,float angle_, glm::vec4 tint_);
	~SpriteSurface();
	void Draw(Camera* camera_, std::vector<glm::vec2> postion_);
	int getWidth();
	int getHeight();
	glm::vec2 minVert();
private:
	void GenerateBuffers();
	float width, height, angle;
	GLuint shaderProgram;
	GLuint VAO, VBO; // VAO separates data, VBO holds data 
	GLuint textureID;
	GLuint modelLoc,projLoc, tintColour,textureLoc;
	std::string name;
	glm::vec2 scale;
	std::vector<Vertex> spriteSufaceVertex;
};
#endif 