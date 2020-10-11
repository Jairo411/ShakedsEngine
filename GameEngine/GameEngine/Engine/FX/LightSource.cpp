#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 lightColour_) {
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	lightColour = lightColour_;
}

LightSource::~LightSource() {

}

// Getters
glm::vec3 LightSource::GetPosition() const {
	return position;
}

float LightSource::GetAmbientValue() const {
	return ambientValue;
}

float LightSource::GetDiffuseValue() const {
	return diffuseValue;
}

glm::vec3 LightSource::GetLightColour() const {
	return lightColour;
}

// Setters
void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::LightSource::SetAmbientValue(float ambientValue_) {
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(float diffuseValue_) {
	diffuseValue = diffuseValue_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_) {
	lightColour = lightColour_;
}