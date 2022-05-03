#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include"ErrorCheck.h"
#include<glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragementSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragementshader);
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const ;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniformMat4(const std::string& name, glm::mat4 &mat);
};

