#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	Shader() {};
	~Shader();

	void Bind() const;
	void Unbind() const;

	void MakeShader(const std::string& filepath);

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformVec3(const std::string& name, const glm::vec3& vec3);
	void SetUniformVec3(const std::string& name, const float& x, const float& y, const float& z);
	void SetUniformVec4(const std::string& name, const glm::vec4& vec4);

	unsigned int GetRendererID() const;

private:
	unsigned int m_RendererID;
	std::string m_Filepath;

	std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& name);

	ShaderSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};