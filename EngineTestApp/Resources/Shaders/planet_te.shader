#version 450

#include "SimplexNoise.shader"

layout(triangles, equal_spacing, cw) in;
in vec3 tcPosition[];
out vec3 tePosition;
out vec3 tePatchDistance;
out float teElevation;

uniform int NumNoiseLayers;

struct NoiseLayer
{
    float Strength;
    float BaseRoughness;
    float Roughness;
    float Persistance;

    vec3 Center;
    float MinValue;

    int NumLayers;
    int UseFirstLayerAsMask;
    int NoiseFilterType;
    float Weight;
};

const int MaxNoiseLayers = 20;
layout(std140, binding = 0) uniform NoiseBlock
{
    NoiseLayer NoiseLayers[MaxNoiseLayers];
} _NoiseData;

float Evaluate(vec3 p, int layer)
{
    int filterType = _NoiseData.NoiseLayers[layer].NoiseFilterType;
    if (filterType == 0)
        return SimpleEvaluate(p, int(_NoiseData.NoiseLayers[layer].NumLayers), _NoiseData.NoiseLayers[layer].BaseRoughness, _NoiseData.NoiseLayers[layer].Roughness, _NoiseData.NoiseLayers[layer].Persistance, _NoiseData.NoiseLayers[layer].Center, _NoiseData.NoiseLayers[layer].MinValue, _NoiseData.NoiseLayers[layer].Strength);

    return RigidEvaluate(p, int(_NoiseData.NoiseLayers[layer].NumLayers), _NoiseData.NoiseLayers[layer].BaseRoughness, _NoiseData.NoiseLayers[layer].Roughness, _NoiseData.NoiseLayers[layer].Persistance, _NoiseData.NoiseLayers[layer].Center, _NoiseData.NoiseLayers[layer].MinValue, _NoiseData.NoiseLayers[layer].Strength, _NoiseData.NoiseLayers[layer].Weight);
}

float CalculateTotalStrength()
{
    float strength = 0.0;
    for (int i = 0; i < NumNoiseLayers; i++)
    {
        strength += _NoiseData.NoiseLayers[i].Strength;
    }
    return strength;
}

float LayeredEvaluate(vec3 p)
{
    float firstLayerValue = 0.0;
    float elevationAverage = 0.0;

    float totalStrength = CalculateTotalStrength();

    float unscaledElevation = 0.0;
    float scaledElevation = 0.0;

    float noiseValue = 0.0;
    float strengthPercentage = 0.0;
    if (NumNoiseLayers > 0)
    {
        unscaledElevation = Evaluate(p, 0);
        scaledElevation = max(0.0, unscaledElevation);
        noiseValue = scaledElevation;
        elevationAverage = unscaledElevation;
        firstLayerValue = noiseValue;
    }

    for (int i = 1; i < NumNoiseLayers; i++)
    {
        float mask = (_NoiseData.NoiseLayers[i].UseFirstLayerAsMask == 1) ? firstLayerValue : 1.0;
        unscaledElevation = Evaluate(p, 0);
        scaledElevation = max(0.0, unscaledElevation);
        elevationAverage += unscaledElevation;

        noiseValue += scaledElevation;
    }

    elevationAverage /= totalStrength;

    teElevation = clamp(elevationAverage * 115.0, -0.99, 0.99);

    return noiseValue;
}

void main()
{
    vec3 p0 = gl_TessCoord.x * tcPosition[0];
    vec3 p1 = gl_TessCoord.y * tcPosition[1];
    vec3 p2 = gl_TessCoord.z * tcPosition[2];
    tePatchDistance = gl_TessCoord;
    tePosition = normalize(p0 + p1 + p2);
    float hieght = LayeredEvaluate(tePosition);
    gl_Position = vec4(tePosition * (1.0 + hieght), 1);
}
