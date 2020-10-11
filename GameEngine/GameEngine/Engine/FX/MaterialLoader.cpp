#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {

}

// LOAD THE MAT FILE - 'tab' before variables in mat file : try : '\t'
void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	Material m = Material();
	std::string matName = "";
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
			//std::cout << m.name << std::endl;

		}
		else if (line.substr(0, 4) == "\tNs ") {
			std::istringstream v(line.substr(4));
			float Ns;
			v >> Ns;
			m.shininess = Ns;
			//std::cout << "shininess: " << m.shininess << std::endl;
		}
		else if (line.substr(0, 3) == "\td ") {
			std::istringstream v(line.substr(3));
			float d;
			v >> d;
			m.transparency = d;
			//std::cout << "transparency: " << m.transparency << std::endl;
		}
		else if (line.substr(0, 4) == "\tKa ") {
			std::istringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
			//std::cout << "ambient: " << m.ambient.x << " " << m.ambient.y << " " << m.ambient.z << std::endl;

		}
		else if (line.substr(0, 4) == "\tKd ") {
			std::istringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
			//std::cout << "diffuse: " << m.diffuse.x << " " << m.diffuse.y << " " << m.diffuse.z << std::endl;
		}
		else if (line.substr(0, 4) == "\tKs ") {
			std::istringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
			//std::cout << "specular: " << m.specular.x << " " << m.specular.y << " " << m.specular.z << std::endl;
		}
		
		// COMPLETE! Could still add more info though: 
		// Ni, Tr, Tf, illum2, Ke

	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}