#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Core/Debug.h"
#include "../../FX/MaterialLoader.h"
#include <sstream>
#include "../../Math/BoundingBox.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath_);
	void LoadModel(const std::string& objFilePath_, const std::string& matFilePath_);
	std::vector<Vertex> GetVerts();
	std::vector<int> GetIndices();
	std::vector<SubMesh> GetSubMeshes();
	BoundingBox GetBoundingBox();

	void OnDestroy();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<int> indices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	Material currentMaterial;

	BoundingBox box;

	// BoundingBox Info
	glm::vec3 minBoxVertex;
	glm::vec3 maxBoxVertex;
};
#endif

