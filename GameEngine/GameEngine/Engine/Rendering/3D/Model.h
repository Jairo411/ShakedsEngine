#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"

class Model {
public:
	Model(const std::string& objFilePath_, const std::string& matFilePath_, GLuint shaderProgram_);
	// ^^^^ this gives you the option of including the angle, rotation, and scale in the parameters, or gives a default value
	// also, these parameters must be last in order!
	// also, when using the function, you must change all of the parameters if you want to change one of the last ones
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(int index_) const;

	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;

private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();

	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;

	BoundingBox box;
};
#endif;