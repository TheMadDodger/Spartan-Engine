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

    Spartan::Vector3 Center;
    float MinValue;
    
    int NumLayers;
    int UseFirstLayerAsMask;
    NoiseFilterType NoiseFilterType;
    float Weight;
};

class PlanetMaterial : public Spartan::Material
{
public:
	PlanetMaterial(Spartan::ShaderData* pShader);
	virtual ~PlanetMaterial();

	void Randomize(int seed);
    void SetLayerCount(int count);
    void SetLayer(size_t index, const NoiseLayer& layer);

private:
	virtual void SetShaderVars(Spartan::BaseComponent*) override;

private:
	void UnpackLittleUint32(int value, char buffer[]);

private:
	static const int Source[];
	static const int RandomSize;
	int* m_Random;
    static const GLuint MAXNOISELAYERS = 20;
    NoiseLayer m_NoiseLayers[MAXNOISELAYERS];
    int m_NumLayers;
    GLuint m_UniformNoiseBuffer;
    Spartan::Gradient* m_pGradient;
};

