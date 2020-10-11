#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Plane.h"

struct Frustum {
	Plane planes[6];

	
	inline Frustum() {
		for (int i = 0; i < 6; i++) {
			planes[i] = Plane();
		}
	}

	inline Frustum(Plane left_, Plane right_, Plane top_, Plane bottom_, Plane near_, Plane far_) {
		planes[0] = left_;
		planes[1] = right_;
		planes[2] = top_;
		planes[3] = bottom_;
		planes[4] = near_;
		planes[5] = far_;
	}
	
	// check to see if the point is inside all of the frustums
	inline bool IsPointInsideFrustum(const glm::vec3 pos_) {
		for (int i = 0; i < 6; i++) {
			// if the point is outside of any of the planes, return false
			if (glm::dot(planes[i].normal, pos_) + planes[i].d <= 0) {
				return false;
			}
		}
		return true;
	}

	inline void NormalizeAllPlanes() {
		float mag;
		for (int i = 0; i < 6; i++) {
			mag = sqrt((planes[i].normal.x * planes[i].normal.x) + (planes[i].normal.y * planes[i].normal.y) + (planes[i].normal.z * planes[i].normal.z));
			planes[i].normal /= mag;
			planes[i].d /= mag;
		}
	}

	inline void PrintAllPlanes() {
		std::cout << "FRUSTUM PLANES: " << std::endl;
		for (int i = 0; i < 6; i++) {
			planes[i].PrintPlane();
		}
	}

	inline void ExtractPlanes(glm::mat4 m_) {
		// glm::mat4 says it uses column-major order for its matrices
		// left plane
		planes[0].normal.x = m_[0][3] + m_[0][0];
		planes[0].normal.y = m_[1][3] + m_[1][0];
		planes[0].normal.z = m_[2][3] + m_[2][0];
		planes[0].d = m_[3][3] + m_[3][0];

		// right plane
		planes[1].normal.x = m_[0][3] - m_[0][0];
		planes[1].normal.y = m_[1][3] - m_[1][0];
		planes[1].normal.z = m_[2][3] - m_[2][0];
		planes[1].d = m_[3][3] - m_[3][0];

		// top plane
		planes[2].normal.x = m_[0][3] - m_[0][1];
		planes[2].normal.y = m_[1][3] - m_[1][1];
		planes[2].normal.z = m_[2][3] - m_[2][1];
		planes[2].d = m_[3][3] - m_[3][1];

		// bottom plane
		planes[3].normal.x = m_[0][3] + m_[0][1];
		planes[3].normal.y = m_[1][3] + m_[1][1];
		planes[3].normal.z = m_[2][3] + m_[2][1];
		planes[3].d = m_[3][3] + m_[3][1];

		// near plane
		planes[4].normal.x = m_[0][3] + m_[0][2];
		planes[4].normal.y = m_[1][3] + m_[1][2];
		planes[4].normal.z = m_[2][3] + m_[2][2];
		planes[4].d = m_[3][3] + m_[3][2];

		// far plane
		planes[5].normal.x = m_[0][3] - m_[0][2];
		planes[5].normal.y = m_[1][3] - m_[1][2];
		planes[5].normal.z = m_[2][3] - m_[2][2];
		planes[5].d = m_[3][3] - m_[3][2];
	}

	inline void TestPrintMatrix(const glm::mat4& m_) {
		std::cout << "Matrix: " << std::endl;
		std::cout << "[ " << m_[0].x << " | " << m_[1].x << " | " << m_[2].x << " | " << m_[3].x << " ]" << std::endl;
		std::cout << "[ " << m_[0].y << " | " << m_[1].y << " | " << m_[2].y << " | " << m_[3].y << " ]" << std::endl;
		std::cout << "[ " << m_[0].z << " | " << m_[1].z << " | " << m_[2].z << " | " << m_[3].z << " ]" << std::endl;
		std::cout << "[ " << m_[0].w << " | " << m_[1].w << " | " << m_[2].w << " | " << m_[3].w << " ]" << std::endl << std::endl;
	}
};

#endif
