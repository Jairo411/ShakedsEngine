#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 lightColour_);
	~LightSource();

	// Getters
	glm::vec3 GetPosition() const;
	float GetAmbientValue() const;
	float GetDiffuseValue() const;
	glm::vec3 GetLightColour() const;

	// Setters
	void SetPosition(glm::vec3 position_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);
	void SetLightColour(glm::vec3 lightColour_);

private:
	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	glm::vec3 lightColour;
};

#endif

