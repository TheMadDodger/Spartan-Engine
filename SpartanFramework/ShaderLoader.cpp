#include "stdafx.h"
#include "ShaderLoader.h"
#include "BinaryContainer.h"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

Material *ShaderLoader::LoadContent(const std::string &file)
{
	unsigned int programID = glCreateProgram();

	std::string vertexShaderPath = file + "_vs.shader";
	std::string fragmentShaderPath = file + "_fs.shader";

	std::string vs = Utilities::BinaryContainer::ReadCompleteFile(vertexShaderPath.data());
	vs.pop_back();
	vs += '\0';
	std::string fs = Utilities::BinaryContainer::ReadCompleteFile(fragmentShaderPath.data());
	fs.pop_back();
	fs += '\0';

	unsigned int vsID, fsID;
	if (!GetCompiledShader(vsID, GL_VERTEX_SHADER, vs))
	{
		glDeleteProgram(programID);
		return nullptr;
	}
	if (!GetCompiledShader(fsID, GL_FRAGMENT_SHADER, fs))
	{
		glDeleteProgram(programID);
		return nullptr;
	}

	glAttachShader(programID, vsID);
	glAttachShader(programID, fsID);

	glLinkProgram(programID);
	glValidateProgram(programID);

	Material *pMat = new Material(file);
	pMat->m_ShaderProgramID = programID;

	glDeleteShader(vsID);
	glDeleteShader(fsID);
	return pMat;
}

bool ShaderLoader::GetCompiledShader(unsigned int &shaderID, unsigned int shader_type, const std::string & file)
{
	shaderID = glCreateShader(shader_type);

	const char *path = file.c_str();
	glShaderSource(shaderID, 1, &path, nullptr);
	glCompileShader(shaderID);

	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		GLchar *strInfoLog = new GLchar[length + 1];
		glGetShaderInfoLog(shaderID, length, &length, strInfoLog);

		std::string errorMessage = "Error compiling shader " + file + "\n";
		errorMessage += std::string(strInfoLog);
		Utilities::Debug::LogError(errorMessage);

		delete[] strInfoLog;
		return false;
	}

	return true;
}
