#pragma once
#include <Material.h>

class BufferTestMaterial : public Spartan::Material
{
public:
	BufferTestMaterial(Spartan::ShaderData* pShader);
	~BufferTestMaterial();

	void Randomize(int seed);

private:
	virtual void SetShaderVars(Spartan::BaseComponent*) override;
	void UnpackLittleUint32(int value, byte buffer[]);

private:
	static const int Source[];
	static const int RandomSize;
	int* m_Random;

	GLuint m_RandomUBO;
	GLuint m_UniformBufferID;
	Spartan::Color m_Colors[12];
};

