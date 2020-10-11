#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../FX/LightSource.h"
#include "../Math/Frustum.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	~Camera();

	void OnDestroy();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::vec2 GetClippingPlanes() const;
	Frustum GetFrustum() const;
	// Light Sources
	void AddLightSource(LightSource* lightSource_);
	std::vector<LightSource*> GetLightSources();
	
	// Mouse Movement & Scrolling
	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseScroll(int y_);

	
	

private:
	void UpdateCameraVectors();

	// Frustum
	void UpdateFrustum();
	Frustum frustum;

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightSources;
};
#endif