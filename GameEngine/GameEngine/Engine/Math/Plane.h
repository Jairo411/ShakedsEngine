#ifndef PLANE_H
#define PLANE_H
#include <glm/glm.hpp>
#include <iostream>

// plane inherits from vec4
// plane normalizes itself
class Plane : glm::vec4
{
public:
	glm::vec3 normal;
	float d; // distance from origin

	inline Plane() {
		normal = glm::vec3(0.0f, 1.0f, 0.0f);
		d = 0.0f;
		NormalizePlane();
	}
	
	inline Plane(glm::vec4 vec4_) {
		normal = glm::vec3(vec4_.x, vec4_.y, vec4_.z);
		d = vec4_.w;
		NormalizePlane();
	}
	
	inline Plane(glm::vec3 normal_, float d_) {
		normal = normal_;
		d = d_;
		NormalizePlane();
	}
	
	inline ~Plane() {

	}

	inline void NormalizePlane() {
		normal = glm::normalize(normal);
	}

	inline void PrintPlane() {
		std::cout << "(" << normal.x << ", " << normal.y << ", " << normal.z << ", " << d << ")" << std::endl;
	}
};
#endif
