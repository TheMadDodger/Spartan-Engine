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
	Utilities::Debug::LogGLError(glGetError());

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
		Utilities::Debug::LogGLError(glGetError());
		return nullptr;
	}
	if (!GetCompiledShader(fsID, GL_FRAGMENT_SHADER, fs))
	{
		glDeleteProgram(programID);
		Utilities::Debug::LogGLError(glGetError());
		return nullptr;
	}

	glAttachShader(programID, vsID);
	Utilities::Debug::LogGLError(glGetError());
	glAttachShader(programID, fsID);
	Utilities::Debug::LogGLError(glGetError());

	glLinkProgram(programID);
	Utilities::Debug::LogGLError(glGetError());
	glValidateProgram(programID);
	Utilities::Debug::LogGLError(glGetError());

	Material *pMat = new Material(file);
	pMat->m_ShaderProgramID = programID;

	glDeleteShader(vsID);
	Utilities::Debug::LogGLError(glGetError());
	glDeleteShader(fsID);
	Utilities::Debug::LogGLError(glGetError());
	return pMat;
}

bool ShaderLoader::GetCompiledShader(unsigned int &shaderID, unsigned int shader_type, const std::string & file)
{
	shaderID = glCreateShader(shader_type);
	Utilities::Debug::LogGLError(glGetError());

	const char *path = file.c_str();
	glShaderSource(shaderID, 1, &path, nullptr);
	Utilities::Debug::LogGLError(glGetError());
	glCompileShader(shaderID);
	Utilities::Debug::LogGLError(glGetError());

	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	Utilities::Debug::LogGLError(glGetError());

	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		Utilities::Debug::LogGLError(glGetError());

		GLchar *strInfoLog = new GLchar[length + 1];
		glGetShaderInfoLog(shaderID, length, &length, strInfoLog);
		Utilities::Debug::LogGLError(glGetError());

		std::string errorMessage = "Error compiling shader " + file + "\n";
		errorMessage += std::string(strInfoLog);
		Utilities::Debug::LogError(errorMessage);

		delete[] strInfoLog;
		return false;
	}

	return true;
}
