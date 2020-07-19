#include "stdafx.h"
#include "PlanetMaterial.h"
#include "Components.h"
#include "GameObject.h"
#include "GameScene.h"
#include <Gradient.h>

/// Initial permutation table
const int PlanetMaterial::Source[] =
{
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
    8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
    117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165,
    71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
    55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89,
    18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
    124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189,
    28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
    242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31,
    181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
    67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

const int PlanetMaterial::RandomSize = 256;

PlanetMaterial::PlanetMaterial(Spartan::ShaderData* pShader) : Material(pShader), m_Random(nullptr), m_NumLayers(0), m_UniformNoiseBuffer(0)
{
    Randomize(0);
    m_UniformNoiseBuffer = CreateUniformBuffer("NoiseBlock", sizeof(NoiseLayer) * MAXNOISELAYERS, 0);

    m_pGradient = new Spartan::Gradient(512, 2);
    m_pGradient->SetKey(Spartan::Color(242.0f / 256.0f, 209.0f / 256.0f, 107.0f / 256.0f, 1.0f), 0.0f);
    m_pGradient->SetKey(Spartan::Color::Green(), 15.0f);
    m_pGradient->SetKey(Spartan::Color(116.0f / 256.0f, 102.0f / 256.0f, 59.0f / 256.0f, 1.0f), 40.0f);
    m_pGradient->SetKey(Spartan::Color::Gray(), 90.0f);
    m_pGradient->SetKey(Spartan::Color::White(), 100.0f);


    //(0.3f, 0.25f, 0.7f, 1.0f)
    //(0.0f, 0.8f, 0.82f, 1.0f)
    m_pGradient->SetKey(Spartan::Color::Cyan(), 0.0f, 1);
    m_pGradient->SetKey(Spartan::Color(0.13f, 0.36f, 0.63f, 1.0f), 50.f, 1);
    m_pGradient->SetKey(Spartan::Color(0.13f, 0.36f, 0.63f, 1.0f), 100.f, 1);
    //m_pGradient->SetKey(Color(0.3f, 0.25f, 0.7f, 1.0f), 50.f, 1);
    //m_pGradient->SetKey(Color(0.2f, 0.2f, 0.6f, 1.0f), 100.0f, 1);
    m_pGradient->BuildTexture();
}

PlanetMaterial::~PlanetMaterial()
{
    if (m_Random != nullptr) delete[] m_Random;
    m_Random = nullptr;
    delete m_pGradient;
}

void PlanetMaterial::SetShaderVars(Spartan::BaseComponent *pComponent)
{
	auto pGameObject = pComponent->GetGameObject();
	Spartan::Vector3 camPos = pGameObject->GetGameScene()->GetActiveCamera()->GetGameObject()->GetTransform()->GetWorldPosition();
	Spartan::Matrix4X4 worldMatrix = pGameObject->GetTransform()->GetWorldMatrix();
    Spartan::Matrix3X3 rotationMatrix = pGameObject->GetTransform()->GetRotationMatrix();

    SetInt("NumNoiseLayers", m_NumLayers);
	SetVec3("CameraPosition", camPos);
	SetMatrix4("WorldMatrix", &worldMatrix.m[0][0]);

    
	SetMatrix3("NormalMatrix", &rotationMatrix.m[0][0]);
    SetIntArray("_random", RandomSize, m_Random);
    SetUniformBuffer(m_UniformNoiseBuffer, m_NoiseLayers, sizeof(NoiseLayer) * MAXNOISELAYERS);
    SetTexture("GradientTexture", m_pGradient->GetTexture());
}

void PlanetMaterial::Randomize(int seed)
{
    if (m_Random != nullptr) delete[] m_Random;

    m_Random = new int[RandomSize * 2];
    std::fill(m_Random, m_Random + RandomSize, 0);

    if (seed != 0)
    {
        // Shuffle the array using the given seed
        // Unpack the seed into 4 bytes then perform a bitwise XOR operation
        // with each byte
        byte *F = new byte[4];
        UnpackLittleUint32(seed, F);

        for (int i = 0; i < RandomSize; i++)
        {
            m_Random[i] = Source[i] ^ F[0];
            m_Random[i] ^= F[1];
            m_Random[i] ^= F[2];
            m_Random[i] ^= F[3];

            m_Random[i + RandomSize] = m_Random[i];
        }

    }
    else
    {
        for (int i = 0; i < RandomSize; i++)
            m_Random[i + RandomSize] = m_Random[i] = Source[i];
    }
}

void PlanetMaterial::SetLayerCount(int count)
{
    if (m_NumLayers == count) return;
    if (count <= 0) return;
    m_NumLayers = count;
}

void PlanetMaterial::SetLayer(size_t index, const NoiseLayer& layer)
{
    if (index >= MAXNOISELAYERS) return;
    m_NoiseLayers[index] = layer;
}

/// <summary>
/// Unpack the given integer (int32) to an array of 4 bytes  in little endian format.
/// If the length of the buffer is too smal, it wil be resized.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="buffer">The output buffer.</param>
void PlanetMaterial::UnpackLittleUint32(int value, byte buffer[])
{
    buffer[0] = (byte)(value & 0x00ff);
    buffer[1] = (byte)((value & 0xff00) >> 8);
    buffer[2] = (byte)((value & 0x00ff0000) >> 16);
    buffer[3] = (byte)((value & 0xff000000) >> 24);
}
