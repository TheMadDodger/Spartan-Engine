#pragma once
#include <Material.h>

class BufferTestMaterial : public SpartanEngine::Material
{
public:
	BufferTestMaterial(SpartanEngine::ShaderData* pShader);
	~BufferTestMaterial();

	void Randomize(int seed);

private:
	virtual void SetShaderVars(SpartanEngine::BaseComponent*) override;
	void UnpackLittleUint32(int value, byte buffer[]);

private:
	static const int Source[];
	static const int RandomSize;
	int* m_Random;

	GLuint m_RandomUBO;
	GLuint m_UniformBufferID;
	SpartanEngine::Color m_Colors[12];
};

