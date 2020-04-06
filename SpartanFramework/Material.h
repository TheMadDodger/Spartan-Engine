#pragma once
#include "SEObject.h"

class ShaderData;
class BaseComponent;

class Material : SEObject
{
public:
	Material(ShaderData *pShader);
	~Material();

	void Use();
	static void Reset();

	template<typename T>
	T *As()
	{
		return dynamic_cast<T*>(this);
	}

public: // Set shader vars
	void SetFloat(const std::string &name, float value) const;
	void SetInt(const std::string &name, int value) const;
	void SetIntArray(const std::string &name, int size, int *value) const;
	void SetBool(const std::string &name, bool value) const;
	void SetVec3(const std::string &name, const Vector3 &value) const;
	void SetVec2(const std::string &name, const Vector3 &value) const;
	void SetVec4(const std::string& name, const Vector4& value) const;
	void SetColor(const std::string &name, const Color &value) const;
	void SetDouble(const std::string &name, double value) const;
	void SetMatrix3(const std::string &name, float *pMatrix) const;
	void SetMatrix4(const std::string &name, float *pMatrix) const;
	void SetTexture(const std::string &name, TextureData *pTexture);
	void SetTexture(const std::string &name, const GLuint &textureID);

	void SetDoubleSided(bool doubleSided);
	void EnableWireframe(bool enabled);

	GLuint CreateUniformBuffer(const std::string& name, GLuint bufferSize);
	void SetUniformBuffer(GLuint bufferID, void* data, GLuint size);

protected:
	virtual void SetShaderVars(BaseComponent *) {};

private:
	friend class MeshRenderComponent;
	ShaderData *m_pShader;
	GLint m_TextureCounter;

	bool m_DoubleSided;
	bool m_Wireframe;
	GLuint m_BufferBindIndex;
	std::vector<GLuint> m_UniformBufferObjects;
};

