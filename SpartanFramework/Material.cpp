#include "stdafx.h"
#include "Material.h"
#include "BaseComponent.h"

Material::Material(ShaderData *pShader) : m_pShader(pShader)
{
}

Material::~Material()
{
}

void Material::SetFloat(const std::string & name, float value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform1f(ID, value);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetInt(const std::string & name, int value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform1ui(ID, value);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetBool(const std::string & name, bool value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform1i(ID, (int)value);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetVec3(const std::string & name, const Vector3 & value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform3f(ID, value.x, value.y, value.z);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetVec2(const std::string & name, const Vector3 & value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform2f(ID, value.x, value.y);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetColor(const std::string & name, const Color & value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform4f(ID, value.r, value.g, value.b, value.a);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetDouble(const std::string & name, double value) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());
	glUniform1d(ID, value);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetMatrix(const std::string & name, float * pMatrix) const
{
	GLint ID = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	Utilities::Debug::LogGLError(glGetError());

	glUniformMatrix3fv(ID, 1, GL_FALSE, pMatrix);
	Utilities::Debug::LogGLError(glGetError());
}

void Material::SetTexture(const std::string &name, TextureData *pTexture)
{
	GLuint texLocation = glGetUniformLocation(m_pShader->m_ShaderProgramID, name.c_str());
	glUniform1i(texLocation, m_TextureCounter);

	glActiveTexture(GL_TEXTURE0 + m_TextureCounter);
	glBindTexture(GL_TEXTURE_2D, pTexture->GetID());

	glActiveTexture(GL_TEXTURE0);

	++m_TextureCounter;
}
