#pragma once
#include <Material.h>
#include <Gradient.h>

enum NoiseFilterType : int
{
    Simple,
    Rigid,
};

struct NoiseLayer
{
    float Strength;
    float BaseRoughness;
    float Roughness;
    float Persistance;

    SpartanEngine::Vector3 Center;
    float MinValue;
    
    int NumLayers;
    int UseFirstLayerAsMask;
    NoiseFilterType NoiseFilterType;
    float Weight;
};

class PlanetMaterial : public SpartanEngine::Material
{
public:
	PlanetMaterial(SpartanEngine::ShaderData* pShader);
	virtual ~PlanetMaterial();

	void Randomize(int seed);
    void SetLayerCount(int count);
    void SetLayer(size_t index, const NoiseLayer& layer);

private:
	virtual void SetShaderVars(SpartanEngine::BaseComponent*) override;

private:
	void UnpackLittleUint32(int value, byte buffer[]);

private:
	static const int Source[];
	static const int RandomSize;
	int* m_Random;
    static const GLuint MAXNOISELAYERS = 20;
    NoiseLayer m_NoiseLayers[MAXNOISELAYERS];
    int m_NumLayers;
    GLuint m_UniformNoiseBuffer;
    SpartanEngine::Gradient* m_pGradient;
};

