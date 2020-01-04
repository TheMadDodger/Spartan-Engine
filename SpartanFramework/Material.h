#pragma once
#include "SEObject.h"

class ShaderData;
class BaseComponent;

class Material : SEObject
{
public:
	Material(ShaderData *pShader);
	~Material();

	void Use()
	{
		glUseProgram(m_pShader->m_ShaderProgramID);
		Utilities::Debug::LogGLError(glGetError());

		m_TextureCounter = 0;
	}

	static void Reset()
	{
		glUseProgram(0);
		Utilities::Debug::LogGLError(glGetError());
	}

	template<typename T>
	T *As()
	{
		return dynamic_cast<T*>(this);
	}

protected: // Set shader vars
	void SetFloat(const std::string &name, float value) const;
	void SetInt(const std::string &name, int value) const;
	void SetBool(const std::string &name, bool value) const;
	void SetVec3(const std::string &name, const Vector3 &value) const;
	void SetVec2(const std::string &name, const Vector3 &value) const;
	void SetColor(const std::string &name, const Color &value) const;
	void SetDouble(const std::string &name, double value) const;
	void SetMatrix(const std::string &name, float *pMatrix) const;
	void SetTexture(const std::string &name, TextureData *pTexture);

protected:
	virtual void SetShaderVars(BaseComponent *) {};

private:
	friend class Mesh2DRenderComponent;
	ShaderData *m_pShader;
	GLint m_TextureCounter;
};

