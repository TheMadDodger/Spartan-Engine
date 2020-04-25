#include "stdafx.h"
#include "Material.h"
#include "BaseComponent.h"

namespace SpartanEngine
{
	Material::Material(ShaderData* pShader) : m_pShader(pShader), m_DoubleSided(false), m_Wireframe(false), m_BufferBindIndex(0)
	{
	}

	Material::~Material()
	{
		if (m_UniformBufferObjects.size() > 0)
		{
			glDeleteBuffers(m_UniformBufferObjects.size(), &m_UniformBufferObjects[0]);
			m_UniformBufferObjects.clear();
		}
		m_BufferBindIndex = 0;
	}

	void Material::Use()
	{
		glUseProgram(m_pShader->m_ShaderProgramID);
		Utilities::Debug::LogGLError(glGetError());

		m_TextureCounter = 0;

		glPolygonMode(m_DoubleSided ? GL_FRONT_AND_BACK : GL_FRONT, m_Wireframe ? GL_LINE : GL_FILL);
	}

	void Material::Reset()
	{
		glUseProgram(NULL);
		Utilities::Debug::LogGLError(glGetError());

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Material::SetFloat(const std::string& name, float value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1f(ID, value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetInt(const std::string& name, int value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1i(ID, value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetIntArray(const std::string& name, int size, int* value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1iv(ID, size, value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetBool(const std::string& name, bool value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1i(ID, (int)value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetVec2(const std::string& name, const Vector3& value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform2f(ID, value.x, value.y);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetVec3(const std::string& name, const Vector3& value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform3f(ID, value.x, value.y, value.z);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetVec4(const std::string& name, const Vector4& value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform4f(ID, value.x, value.y, value.z, value.w);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetColor(const std::string& name, const Color& value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform4f(ID, value.r, value.g, value.b, value.a);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetDouble(const std::string& name, double value) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1d(ID, value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetMatrix3(const std::string& name, float* pMatrix) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());

		glUniformMatrix3fv(ID, 1, GL_FALSE, pMatrix);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetMatrix4(const std::string& name, float* pMatrix) const
	{
		GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());

		glUniformMatrix4fv(ID, 1, GL_FALSE, pMatrix);
		Utilities::Debug::LogGLError(glGetError());
	}

	void Material::SetTexture(const std::string& name, TextureData* pTexture)
	{
		GLuint texLocation = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		glUniform1i(texLocation, m_TextureCounter);

		glActiveTexture(GL_TEXTURE0 + m_TextureCounter);
		glBindTexture(GL_TEXTURE_2D, pTexture->GetID());

		glActiveTexture(GL_TEXTURE0);

		++m_TextureCounter;
	}

	void Material::SetTexture(const std::string& name, const GLuint& textureID)
	{
		GLuint texLocation = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
		glUniform1i(texLocation, m_TextureCounter);

		glActiveTexture(GL_TEXTURE0 + m_TextureCounter);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glActiveTexture(GL_TEXTURE0);

		++m_TextureCounter;
	}

	void Material::SetDoubleSided(bool doubleSided)
	{
		m_DoubleSided = doubleSided;
	}

	void Material::EnableWireframe(bool enabled)
	{
		m_Wireframe = enabled;
	}

	GLuint Material::CreateUniformBuffer(const std::string& name, GLuint bufferSize)
	{
		GLuint uniformBlockIndex = glGetUniformBlockIndex(m_pShader->m_ShaderProgramID, name.data());
		if (uniformBlockIndex == GL_INVALID_INDEX)
		{
			Utilities::Debug::LogError("Material::CreateUniformBuffer > Uniform buffer block with name " + name + " not found!");
			return 0;
		}

		Utilities::Debug::LogGLError(glGetError());
		glUniformBlockBinding(m_pShader->m_ShaderProgramID, uniformBlockIndex, m_BufferBindIndex);
		Utilities::Debug::LogGLError(glGetError());

		// Uniform buffer object for lights
		GLuint bufferID;
		glGenBuffers(1, &bufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_DYNAMIC_DRAW);
		Utilities::Debug::LogGLError(glGetError());
		glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockIndex, bufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		Utilities::Debug::LogGLError(glGetError());

		m_UniformBufferObjects.push_back(bufferID);

		++m_BufferBindIndex;
		return bufferID;
	}

	void Material::SetUniformBuffer(GLuint bufferID, void* data, GLuint size)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}