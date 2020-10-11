#ifndef SHADERHANDLER_H
#define SHADERHANLDER_H

#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include "..//Core/Debug.h"

class ShaderHandler {
public:
	// disabling the functions of the copy and move constructor
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator = (const ShaderHandler&) = delete;
	ShaderHandler& operator = (ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();
	void CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFilePath_, const std::string& fragmentShaderFilePath_);
	GLuint GetShader(const std::string& shaderName_);
	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();
	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;

	std::string ReadShader(const std::string& filePath_);
	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_);

	static std::map<std::string, GLuint> programs;

};
#endif