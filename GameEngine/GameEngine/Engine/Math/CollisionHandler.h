#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include "../Core/OctSpatialPartition.h"

//TODO: make singleton template class (not necessary for marks though)
class CollisionHandler {
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator = (const CollisionHandler&) = delete;
	CollisionHandler& operator = (CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();
	void OnDestroy();
	void OnCreate(float worldSize_);
	void AddObject(GameObject* go_);
	void MouseUpdate(glm::vec2 mousePosition_, int buttonType_);

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionHandlerInstance;
	friend std::default_delete<CollisionHandler>;

	static std::vector<GameObject*> prevCollisions;

	static OctSpatialPartition* scenePartition;
};
#endif
