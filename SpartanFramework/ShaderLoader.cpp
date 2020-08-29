#include "stdafx.h"
#include "ShaderLoader.h"
#include "BinaryContainer.h"

namespace Spartan
{
	ShaderLoader::ShaderLoader()
	{
	}

	ShaderLoader::~ShaderLoader()
	{
	}

	ShaderData* ShaderLoader::LoadContent(const std::string& file)
	{
		GLuint programID = glCreateProgram();
		Utilities::Debug::LogGLError(glGetError());

		std::ifstream fxFileStream(file);
		if (!fxFileStream.is_open())
		{
			Utilities::Debug::LogWarning("Could not open fx file " + file);
			return nullptr;
		}

		ShaderData* pMat = new ShaderData();
		pMat->m_ShaderProgramID = programID;

		std::string line;
		std::string shaderFile;

		while (!fxFileStream.eof())
		{
			std::getline(fxFileStream, line);
			shaderFile = file;
			std::string rootPath;
			GLuint shaderType = GetShaderType(line, shaderFile, rootPath);
			std::string shaderSource = Utilities::BinaryContainer::ReadCompleteFile(shaderFile.data());

			GLuint shaderID;
			if (!GetCompiledShader(shaderID, shaderType, rootPath, shaderSource))
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

	bool ShaderLoader::GetCompiledShader(unsigned int& shaderID, unsigned int shader_type, const std::string& path, std::string& source)
	{
		PreProcessShader(path, source);

		shaderID = glCreateShader(shader_type);
		Utilities::Debug::LogGLError(glGetError());

		const char* sourceCode = source.c_str();
		glShaderSource(shaderID, 1, &sourceCode, nullptr);
		Utilities::Debug::LogGLError(glGetError());
		glCompileShader(shaderID);
		Utilities::Debug::LogGLError(glGetError());

		GLint result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		Utilities::Debug::LogGLError(glGetError());
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		Utilities::Debug::LogGLError(glGetError());
		GLchar* strInfoLog = new GLchar[length + 1];
		glGetShaderInfoLog(shaderID, length, &length, strInfoLog);
		Utilities::Debug::LogGLError(glGetError());

		if (result == GL_FALSE)
		{
			std::string errorMessage = "Error compiling shader " + source + "\n";
			errorMessage += std::string(strInfoLog);
			Utilities::Debug::LogError(errorMessage);

			delete[] strInfoLog;
			return false;
		}
		
		if (length > 0) Utilities::Debug::LogWarning(source + "\n" + std::string(strInfoLog));

		delete[] strInfoLog;
		return true;
	}

	bool ShaderLoader::PreProcessShader(const std::string& path, std::string& source)
	{
		std::istringstream stream(source);
		std::string line;

		source = "";

		while (!stream.eof())
		{
			getline(stream, line);
			if (line[0] == '#')
			{
				size_t space = line.find(' ');
				std::string keyword = line.substr(1, space - 1);
				if (keyword == "include")
				{
					std::string toincludeFile = line.substr(space + 1);
					size_t startPos = toincludeFile.find('\"');
					size_t endPos = toincludeFile.rfind('\"');
					if (startPos == string::npos || endPos == string::npos) return false;
					toincludeFile = toincludeFile.substr(startPos + 1, endPos - 1);
					std::string toincludeFilePath = path + "/" + toincludeFile;
					std::string shaderSource = Utilities::BinaryContainer::ReadCompleteFile(toincludeFilePath.data());
					if (shaderSource == "")
					{
						return false;
					}
					if (!PreProcessShader(path, shaderSource)) return false;
					shaderSource.pop_back();
					shaderSource.pop_back();
					source += shaderSource + '\n';
					continue;
				}
			}
			source += line + '\n';
		}

		source.pop_back();
		source.pop_back();
		source += '\0';
		return true;
	}

	GLuint ShaderLoader::GetShaderType(const std::string& line, std::string& path, std::string& rootPath)
	{
		int seperatorPos = line.find(":");
		std::string typeString = line.substr(0, seperatorPos);
		std::string file = line.substr(seperatorPos + 1);
		size_t forwardSlashPos = path.rfind('/');
		size_t backwardSlashPos = path.rfind('\\');
		size_t slashPos = forwardSlashPos;
		if (backwardSlashPos != string::npos && backwardSlashPos > forwardSlashPos) slashPos = backwardSlashPos;
		rootPath = path.substr(0, slashPos);
		path = rootPath + '/' + file;

		if (typeString == "vs") return GL_VERTEX_SHADER;
		if (typeString == "fs") return GL_FRAGMENT_SHADER;
		if (typeString == "gs") return GL_GEOMETRY_SHADER;
		if (typeString == "tc") return GL_TESS_CONTROL_SHADER;
		if (typeString == "te") return GL_TESS_EVALUATION_SHADER;

		Utilities::Debug::LogError("Unknown shader type: " + typeString + " in file " + file);
		return 0;
	}
}