#include "stdafx.h"
#include "ShaderLoader.h"
#include "BinaryContainer.h"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

ShaderData *ShaderLoader::LoadContent(const std::string &file)
{
	GLuint programID = glCreateProgram();
	Utilities::Debug::LogGLError(glGetError());

	std::ifstream fxFileStream(file);
	if (!fxFileStream.is_open())
	{
		Utilities::Debug::LogWarning("Could not open fx file " + file);
		return nullptr;
	}

	ShaderData* pMat = new ShaderData(file);
	pMat->m_ShaderProgramID = programID;

	std::string line;
	std::string shaderFile;

	while (!fxFileStream.eof())
	{
		std::getline(fxFileStream, line);
		shaderFile = file;
		GLuint shaderType = GetShaderType(line, shaderFile);
		std::string shaderSource = Utilities::BinaryContainer::ReadCompleteFile(shaderFile.data());
		shaderSource.pop_back();
		shaderSource += '\0';

		GLuint shaderID;
		if (!GetCompiledShader(shaderID, shaderType, shaderSource))
		{
			glDeleteProgram(programID);
			Utilities::Debug::LogGLError(glGetError());
			return nullptr;
		}

		glAttachShader(programID, shaderID);
		Utilities::Debug::LogGLError(glGetError());

		pMat->m_ShaderIDs.push_back(shaderID);
	}

	glLinkProgram(programID);
	Utilities::Debug::LogGLError(glGetError());
	glValidateProgram(programID);
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

GLuint ShaderLoader::GetShaderType(const std::string& line, std::string& path)
{
	int seperatorPos = line.find(":");
	std::string typeString = line.substr(0, seperatorPos);
	std::string file = line.substr(seperatorPos + 1);
	size_t forwardSlashPos = path.rfind('/');
	size_t backwardSlashPos = path.rfind('\\');
	size_t slashPos = forwardSlashPos;
	if (backwardSlashPos != string::npos && backwardSlashPos > forwardSlashPos) slashPos = backwardSlashPos;
	path = path.substr(0, slashPos + 1) + file;

	if (typeString == "vs") return GL_VERTEX_SHADER;
	if (typeString == "fs") return GL_FRAGMENT_SHADER;
	if (typeString == "gs") return GL_GEOMETRY_SHADER;
	if (typeString == "tc") return GL_TESS_CONTROL_SHADER;
	if (typeString == "te") return GL_TESS_EVALUATION_SHADER;

	Utilities::Debug::LogError("Unknown shader type: " + typeString + " in file " + file);
	return 0;
}