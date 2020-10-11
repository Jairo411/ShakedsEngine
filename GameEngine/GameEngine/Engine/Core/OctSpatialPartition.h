#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

#define CHILDREN_NUMBER 8
#define SPATIAL_PARTITIONING_DEPTH_LEVEL 3

enum class OctChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};

class OctNode {
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void OnDestroy();
	void Octify(int depth_);
	OctNode* GetParent() const;
	OctNode* GetChild(OctChildren childPosition_) const;
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;

private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;

	// since it's a cube all the sides will be the same
	float size; 
	static int childNum;
};

// TODO: EVENTUALLY WE NEED TO REMOVE GAME OBJECTS AND HAVE THE ABILITY TO MOVE THEM FROM ONE NODE TO ANOTHER 
class OctSpatialPartition
{
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void OnDestroy();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);

private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};
#endif

