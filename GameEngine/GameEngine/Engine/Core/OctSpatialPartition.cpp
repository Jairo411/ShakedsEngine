#include "OctSpatialPartition.h"

// OctNode
int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_) : parent(nullptr), octBounds(nullptr), objectList(std::vector<GameObject*>()), children() {
	objectList.reserve(10);

	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode() {
	OnDestroy();
}

void OctNode::OnDestroy() {
	delete octBounds;
	octBounds = nullptr;

	// could also say !objectList.empty()
	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

	parent = nullptr;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_) {
	if (depth_ > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z), half, this);
		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z), half, this);
		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);
		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);

		// TODO: create rest of children 
		// COMPLETE!
		// REMEMBER MIN VERT IS THE BACK BOTTOM LEFT CORNER

		childNum += 8;

		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent() const {
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPosition_) const {
	return children[static_cast<int>(childPosition_)];
}

void OctNode::AddCollisionObject(GameObject* obj_) {
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const {
	return objectList.size();
}

bool OctNode::IsLeaf() const {
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const {
	return octBounds;
}

int OctNode::GetChildCount() const {
	return childNum;
}

// OctSpatialPartition

OctSpatialPartition::OctSpatialPartition(float worldSize_) {
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(SPATIAL_PARTITIONING_DEPTH_LEVEL);
	std::cout << "There are " << root->GetChildCount() << " total nodes." << std::endl;
	rayIntersectionList = std::vector<OctNode*>();
}

OctSpatialPartition::~OctSpatialPartition() {
	OnDestroy();
}

void OctSpatialPartition::OnDestroy() {
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj_) {
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray_) {
	for (auto cell : rayIntersectionList) {
		cell = nullptr;
	}
	rayIntersectionList.clear();

	rayIntersectionList.reserve(20);

	PrepareCollisionQuery(root, ray_);

	GameObject* result = nullptr;
	// initialize the shortest distance to a huge number (don't need to use a first time boolean check! :D)
	float shortestDistance = FLT_MAX;

	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			if (ray_.IsColliding(&obj->GetBoundingBox())) {
				if (ray_.intersectionDistance < shortestDistance) {
					result = obj;
					shortestDistance = ray_.intersectionDistance;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

void OctSpatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_) {
	// TODO: SHOULD BE COMPLETE
	// check if cell exists
	// 1: does cell_ intersect with obj_ bounding box?
	// if true, is the cell_ a leaf node?
		// if true, add the object to the cell, cout something
		// if not recurse through each child to find the leaf node then add the object
	if (cell_ != nullptr) {
		if (cell_->GetBoundingBox()->Intersects(&obj_->GetBoundingBox())) {
			if (cell_->IsLeaf()) {
				cell_->AddCollisionObject(obj_);
				std::cout << obj_->GetTag() << " has been added to a cell." << std::endl;
			}
			else {
				for (int i = 0; i < CHILDREN_NUMBER; i++) {
					AddObjectToCell(cell_->GetChild(static_cast<OctChildren>(i)), obj_);
				}
			}
		}
	}
}

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_) {
	// TODO: SHOULD BE COMPLETE
	// does this ray collide with the cell_->boundingbox
	// if true, check to see if it's a leaf node
		// if true, add the cells to the rayintersectionlist
		// if not, go through each child and call this recursively
	if (cell_ != nullptr) {
		if (ray_.IsColliding(cell_->GetBoundingBox())) {
			if (cell_->IsLeaf()) {
				rayIntersectionList.push_back(cell_);
			}
			else {
				for (int i = 0; i < CHILDREN_NUMBER; i++) {
					PrepareCollisionQuery(cell_->GetChild(static_cast<OctChildren>(i)), ray_);
				}
			}
		}
	}
}