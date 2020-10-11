#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : currentMaterial(Material()) {
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200); 
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);

	glm::vec3 minBoxVertex = glm::vec3();
	glm::vec3 maxBoxVertex = glm::vec3();

}

LoadOBJModel::~LoadOBJModel() {
	OnDestroy();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_) {
	std::ifstream in(objFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + objFilePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	bool firstVertex = true;
	while (std::getline(in, line)) {
		// VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;

			// BoundingBox min and max verts
			if (firstVertex) {
				minBoxVertex = glm::vec3(x, y, z);
				maxBoxVertex = glm::vec3(x, y, z);
				firstVertex = false;
			}

			if (x < minBoxVertex.x) {
				minBoxVertex.x = x;
			} 
			else if (x > maxBoxVertex.x) {
				maxBoxVertex.x = x;
			}

			if (y < minBoxVertex.y) {
				minBoxVertex.y = y;
			}
			else if (y > maxBoxVertex.y) {
				maxBoxVertex.y = y;
			}

			if (z < minBoxVertex.z) {
				minBoxVertex.z = z;
			}
			else if (z > maxBoxVertex.z) {
				maxBoxVertex.z = z;
			}

			vertices.push_back(glm::vec3(x, y, z));
		}

		// NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		// TEXTURE COORDINATE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		// FACE DATA
		
		else if (line.substr(0, 2) == "f ") {
			std::string data = line.substr(2);
			int currentEndPos = 0;
			while ((currentEndPos = data.find(' ')) != std::string::npos) {
				std::string chunk = data.substr(0, currentEndPos);
				int subEndPos = 0;

				for (int i = 0; i < 3; i++) {
					int pushBack = 0;
					if ((subEndPos = chunk.find('/')) != std::string::npos) {

						pushBack = std::stoi(chunk.substr(0, subEndPos));

						chunk.erase(0, subEndPos + 1);
					}
					else {
						pushBack = std::stoi(chunk);
					}

					pushBack--;

					switch (i) {
					default:
					case 0:
						indices.push_back(pushBack);
						break;
					case 1:
						textureIndices.push_back(pushBack);
						break;
					case 2:
						normalIndices.push_back(pushBack);
						break;
					}
				}

				data.erase(0, currentEndPos + 1);
			}
		}


		else if(line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	box.minVert = minBoxVertex;
	box.maxVert = maxBoxVertex;
	PostProcessing();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& matFilePath_) {
	LoadMaterialLibrary(matFilePath_);
	LoadModel(objFilePath_);
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes() {
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;
	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	currentMaterial = Material();

}

void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}