#include "Camera.h"
#include "..//Core/CoreEngine.h" // ONLY INCLUDE FILES IN THE CPP IF THAT HEADER ALSO INCLUDES THIS ONE
// AVOIDS CIRCULAR DEPENDANCY

Camera::Camera() : position(glm::vec3()), fieldOfView(45.0f), 
	forward(glm::vec3(0.0f, 0.0f, 1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), worldUp(up), 
	nearPlane(2.0f), farPlane(50.0f), yaw(-90.0f), pitch(0.0f) {

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetWindowSize().x / 
		CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 
		0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera() {
	OnDestroy();
}

void Camera::OnDestroy()
{
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// not sure if I need to do this for pointers, or if clear() handles pointer deletion
	for (int i = 0; i < lightSources.size(); i++) {
		delete lightSources[i];
		lightSources[i] = nullptr;
	}
	lightSources.clear();
}

void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_) {
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const {
	return glm::lookAt(position, position + forward, up);
}

// might want to implement a function that updates camera projection
// if you change the window size you need to update the perspective and orthographic matrices as they are dependant on the window size
glm::mat4 Camera::GetPerspective() const {
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const {
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const {
	return glm::vec2(nearPlane, farPlane);
}

Frustum Camera::GetFrustum() const {
	return frustum;
}

void Camera::AddLightSource(LightSource* lightSource_)
{
	lightSources.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightSources()
{
	return lightSources;
}

void Camera::UpdateCameraVectors() {
	// Forward Vector
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw )) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	// Right Vector
	right = glm::normalize(glm::cross(forward, worldUp));

	// Up Vector
	up = glm::normalize(glm::cross(right, forward));

	UpdateFrustum();
}

// normalizes the planes at the end!
void Camera::UpdateFrustum() {
	// This is the fun part!
	// COMPLETE might want to change field of view to a vec2 (for x and y components)
	// my normals will be pointing inwards!
	// d only will change for near and far plane, defaults to 0
	
	// Attempt1 = UNSUCCSESFUL
	/*
	// Top plane
	frustum.planes[0].normal = glm::rotate(forward, 90.0f - (fieldOfView / 2.0f), right);

	// Bottom plane
	frustum.planes[1].normal = glm::rotate(forward, -90.0f + (fieldOfView / 2.0f), right);

	// Left plane
	frustum.planes[2].normal = glm::rotate(forward, -90.0f + (fieldOfView / 2.0f), up);

	// Right plane
	frustum.planes[3].normal = glm::rotate(forward, 90.0f - (fieldOfView / 2.0f	), up);

	// Near plane
	frustum.planes[4].normal = forward;
	frustum.planes[4].d = -nearPlane;

	// Far plane
	frustum.planes[5].normal = glm::rotate(forward, 180.0f, up);
	frustum.planes[5].d = -farPlane;

	frustum.NormalizeAllPlanes();
	*/

	// Attempt2 = SUCCESSFUL
	//frustum.TestPrintMatrix(GetView());

	// get the planes into world space
	//frustum.ExtractPlanes(GetPerspective() * GetView());

	//frustum.NormalizeAllPlanes();
	//frustum.PrintAllPlanes();
	//frustum.TestPrintMatrix(GetPerspective());

}

// Mouse Movement & Scrolling
void Camera::ProcessMouseMovement(glm::vec2 offset_) {
	// Mouse Sensitivity - Should make this dynamic later
	offset_ *= 0.15f;

	yaw += offset_.x;
	pitch -= offset_.y;

	// clamp the pitch and yaw rotationsd
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(int y_) {
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_)* (forward * 2.0f); // hardcoding zoom sensitivity
	}
	UpdateCameraVectors();
}