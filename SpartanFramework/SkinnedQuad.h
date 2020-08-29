#pragma once
#include "SEObject.h"
#include "TextureData.h"
#include "Skeleton.h"

namespace Spartan
{
	struct BlendWeightData
	{
		std::vector<unsigned int> BoneIndeces;
		std::vector<float> BoneWeights;
	};

	struct SkinnedVertice
	{
		BlendWeightData Blending;
		Math::Vector2 OriginalPosition;
		Math::Vector2 TransformedPosition;
		Math::Vector2 TextureCoordinates;
	};

	class SkinnedQuad
	{
	public:
		SkinnedQuad(std::vector<BlendWeightData> BlendData, TextureData* pTexture, Skeleton* pSkeleton);
		SkinnedQuad(const Math::Vector2& startPos, const Math::Vector2& endPos, std::vector<BlendWeightData> BlendData, TextureData* pTexture, Skeleton* pSkeleton);
		//SkinnedQuad(const std::vector<SkinnedVertice> &vertices, TextureData *pTexture, Skeleton *pSkeleton);

		~SkinnedQuad();

		void Update();
		void Draw(const GameContext& gameContext);

	private:
		std::vector<SkinnedVertice> m_Vertices;
		TextureData* m_pTexture;
		Skeleton* m_pSkeleton;
	};
}