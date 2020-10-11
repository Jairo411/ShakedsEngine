#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


#include <iostream>

struct Material {
	inline Material() : diffuseMap(0), shininess(0.0f), transparency(0.0f),
		ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3()) {

	}

	GLuint diffuseMap;

	float shininess;    // Ns
	float transparency; // d

	glm::vec3 ambient;  // Ka
	glm::vec3 diffuse;  // Kd
	glm::vec3 specular; // Ks

	std::string name;

	inline void Print() {
		std::cout << "name: " << name << std::endl;
		std::cout << "diffuseMap: " << diffuseMap << std::endl;
		std::cout << "shininess: " << shininess << std::endl;
		std::cout << "transparency : " << transparency << std::endl;
		std::cout << "ambient: " << ambient.x << " " << ambient.y << " " << ambient.z << std::endl;
		std::cout << "diffuse: " << diffuse.x << " " << diffuse.y << " " << diffuse.z << std::endl;
		std::cout << "specular: " << specular.x << " " << specular.y << " " << specular.z << std::endl << std::endl;
	}
};

class MaterialHandler
{
public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator = (const MaterialHandler&) = delete;
	MaterialHandler& operator = (MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();
	void AddMaterial(Material mat_);
	const Material GetMaterial(const std::string& matName_);
	void OnDestroy();

private:
	MaterialHandler();
	~MaterialHandler();

	static std::unique_ptr<MaterialHandler> materialInstance;
	friend std::default_delete<MaterialHandler>;

	static std::vector<Material> materials;
};
#endif
