#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), 
	modelLoc(0), viewLoc(0), projLoc(0) {

	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh() {
	subMesh.vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_) {// tell opengl it's time to draw
	glUniform1i(matDiffuseMapLoc, 0);


	// print out material attributes
	/*if (printOnce) {
		subMesh.material.Print();
		printOnce = false;
	}*/
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	
	
	// **********************************************************
	
	glUniform3f(viewPositionLoc,
		camera_->GetPosition().x,
		camera_->GetPosition().y,
		camera_->GetPosition().z);
	glUniform3f(lightPosLoc,
		camera_->GetLightSources()[0]->GetPosition().x,
		camera_->GetLightSources()[0]->GetPosition().y,
		camera_->GetLightSources()[0]->GetPosition().z);
	glUniform1f(lightAmbientLoc, 
		camera_->GetLightSources()[0]->GetAmbientValue());
	glUniform1f(lightDiffuseLoc,
		camera_->GetLightSources()[0]->GetDiffuseValue());
	glUniform3f(lightColourLoc,
		camera_->GetLightSources()[0]->GetLightColour().x,
		camera_->GetLightSources()[0]->GetLightColour().y,
		camera_->GetLightSources()[0]->GetLightColour().z);
	
	// COMPLETE!
	glUniform1f(matShininessLoc,
		subMesh.material.shininess);
	glUniform1f(matTransparencyLoc,
		subMesh.material.transparency);
	glUniform3f(matAmbientLoc,
		subMesh.material.ambient.x,
		subMesh.material.ambient.y,
		subMesh.material.ambient.z);
	glUniform3f(matDiffuseLoc,
		subMesh.material.diffuse.x,
		subMesh.material.diffuse.y,
		subMesh.material.diffuse.z);
	glUniform3f(matSpecularLoc,
		subMesh.material.specular.x,
		subMesh.material.specular.y,
		subMesh.material.specular.z);
	
	// **********************************************************

	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() { // generate and fill in vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); // opens the door
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	// POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	
	// COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0); // close the door - makes sure that nothing else can mess around with the VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	//textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");


	// should I add these to the fragment shader?
	// for example should I include: uniform vec3 lightPos
	//                               uniform float ambient       etc..

	viewPositionLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.position");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambientValue");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");

	// COMPLETE!: 

	// don't need this I believe
	matDiffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");

	matShininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	matTransparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecularLoc = glGetUniformLocation(shaderProgram, "material.specular");
}