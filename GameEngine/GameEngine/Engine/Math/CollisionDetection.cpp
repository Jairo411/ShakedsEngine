#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/

CollisionDetection::~CollisionDetection() {

}

Ray CollisionDetection::ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_) {
	glm::vec4 rayStart_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, 
							(mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f,
							-1.0f,
							1.0f);
	glm::vec4 rayEnd_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f,
						(mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f,
						0.0f,
						1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	// when converting from vec4 to vec3, you want to make sure to divide by w
	glm::vec4 rayStart_World = inverse * rayStart_NDC;
	rayStart_World /= rayStart_World.w;
	
	glm::vec4 rayEnd_World = inverse * rayEnd_NDC;
	rayEnd_World /= rayEnd_World.w;

	glm::vec3 rayDir_World(rayEnd_World - rayStart_World);
	// always make sure to normalize directions
	rayDir_World = glm::normalize(rayDir_World);

	return Ray(glm::vec3(rayStart_World), rayDir_World);
}

bool CollisionDetection::RayOBBIntersection(Ray* ray_, BoundingBox* box_) {
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x; // near plane
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y; // far plane

	glm::vec3 oBBPosition_World(box_->transform[3].x, box_->transform[3].y, box_->transform[3].z);
	glm::vec3 delta = oBBPosition_World - ray_->origin;

	// x-axis
	glm::vec3 xAxis(box_->transform[0].x, box_->transform[0].y, box_->transform[0].z);
	float e = glm::dot(xAxis, delta);
	float f = glm::dot(ray_->direction, xAxis);

	if (fabs(f) > 0.001f) {
		float t1 = (e + box_->minVert.x) / f;
		float t2 = (e + box_->maxVert.x) / f;

		if (t1 > t2) {
			float tmp = t1;
			t1 = t2;
			t2 = tmp;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e + box_->minVert.x > 0.0f || -e + box_->maxVert.x < 0.0f) {
			return false;
		}
	}
	
	// y-axis
	glm::vec3 yAxis(box_->transform[1].x, box_->transform[1].y, box_->transform[1].z);
	e = glm::dot(yAxis, delta);
	f = glm::dot(ray_->direction, yAxis);

	if (fabs(f) > 0.001f) {
		float t1 = (e + box_->minVert.y) / f;
		float t2 = (e + box_->maxVert.y) / f;

		if (t1 > t2) {
			float tmp = t1;
			t1 = t2;
			t2 = tmp;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e + box_->minVert.y > 0.0f || -e + box_->maxVert.y < 0.0f) {
			return false;
		}
	}
	// z-axis
	glm::vec3 zAxis(box_->transform[2].x, box_->transform[2].y, box_->transform[2].z);
	e = glm::dot(zAxis, delta);
	f = glm::dot(ray_->direction, zAxis);

	if (fabs(f) > 0.001f) {
		float t1 = (e + box_->minVert.z) / f;
		float t2 = (e + box_->maxVert.z) / f;

		if (t1 > t2) {
			float tmp = t1;
			t1 = t2;
			t2 = tmp;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e + box_->minVert.z > 0.0f || -e + box_->maxVert.z < 0.0f) {
			return false;
		}
	}

	// intersection has occured
	ray_->intersectionDistance = tMin;
	return true;
}