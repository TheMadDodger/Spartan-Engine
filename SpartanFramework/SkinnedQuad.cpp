#include "stdafx.h"
#include "SkinnedQuad.h"
#include "Skeleton.h"
#include "Bone.h"
#include "ContentManager.h"
#include "Components.h"

namespace Spartan
{
	SkinnedQuad::SkinnedQuad(std::vector<BlendWeightData> BlendData, TextureData* pTexture, Skeleton* pSkeleton) :
		m_pTexture(pTexture), m_pSkeleton(pSkeleton)
	{
		if (BlendData.size() < 4) return;
		SkinnedVertice vertex;
		vertex.OriginalPosition = Vector2(0.f, 0.f) * 100.f;
		vertex.TextureCoordinates = Vector2(0.f, 0.f);
		vertex.Blending = BlendData[0];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = Vector2(0.f, 1.f) * 100.f;
		vertex.TextureCoordinates = Vector2(0.f, 1.f);
		vertex.Blending = BlendData[1];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = Vector2(1.f, 1.f) * 100.f;
		vertex.TextureCoordinates = Vector2(1.f, 1.f);
		vertex.Blending = BlendData[2];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = Vector2(1.f, 0.f) * 100.f;
		vertex.TextureCoordinates = Vector2(1.f, 0.f);
		vertex.Blending = BlendData[3];
		m_Vertices.push_back(vertex);
	}

	SkinnedQuad::SkinnedQuad(const Vector2& startPos, const Vector2& endPos, std::vector<BlendWeightData> BlendData, TextureData* pTexture, Skeleton* pSkeleton) :
		m_pTexture(pTexture), m_pSkeleton(pSkeleton)
	{
		if (BlendData.size() < 4) return;
		SkinnedVertice vertex;
		vertex.OriginalPosition = startPos;
		vertex.TextureCoordinates = Vector2(0.f, 0.f);
		vertex.Blending = BlendData[0];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = Vector2(startPos.x, endPos.y);// Vector2(0.f, 1.f) * 100.f;
		vertex.TextureCoordinates = Vector2(0.f, 1.f);
		vertex.Blending = BlendData[1];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = endPos; //Vector2(1.f, 1.f) * 100.f;
		vertex.TextureCoordinates = Vector2(1.f, 1.f);
		vertex.Blending = BlendData[2];
		m_Vertices.push_back(vertex);

		vertex.OriginalPosition = Vector2(endPos.x, startPos.y);;//Vector2(1.f, 0.f) * 100.f;
		vertex.TextureCoordinates = Vector2(1.f, 0.f);
		vertex.Blending = BlendData[3];
		m_Vertices.push_back(vertex);
	}

	/*SkinnedQuad::SkinnedQuad(const std::vector<SkinnedVertice> &vertices, TextureData *pTexture, Skeleton *pSkeleton) :
		m_pTexture(pTexture), m_pSkeleton(pSkeleton)
	{
		std::move(vertices.begin(), vertices.end(), m_Vertices);
	}*/

	SkinnedQuad::~SkinnedQuad()
	{
	}

	void SkinnedQuad::Update()
	{
		for (auto& vertex : m_Vertices)
		{
			Vector2 endPos = Vector2::Zero();

			for (size_t i = 0; i < vertex.Blending.BoneIndeces.size(); ++i)
			{
				auto boneIndex = vertex.Blending.BoneIndeces[i];
				auto blendWeight = vertex.Blending.BoneWeights[i];
				auto pBone = m_pSkeleton->GetBone(boneIndex);
				Matrix4X4 bindPose = pBone->GetBindPose();
				Matrix4X4 boneWorld = pBone->GetTransform()->GetWorldMatrix();
				Matrix4X4 boneTransform = boneWorld * bindPose;
				auto newPos = boneTransform * Vector3(vertex.OriginalPosition.x, vertex.OriginalPosition.y, 0.f);
				endPos = endPos + newPos.xy() * blendWeight;
			}

			vertex.TransformedPosition = Vector2(endPos.x, endPos.y);

			/*auto boneIndex = vertex.Blending.BoneIndeces[0];
			auto pBone = m_pSkeleton->GetBone(boneIndex);
			Matrix3X3 bindPose = pBone->GetBindPose();
			Matrix3X3 boneWorld = pBone->GetTransform()->GetWorldMatrix();
			Matrix3X3 boneTransform = bindPose * boneWorld;
			auto newPos = boneWorld * Vector3(vertex.OriginalPosition.x, vertex.OriginalPosition.y, 1.f);
			vertex.TransformedPosition = Vector2(newPos.x, newPos.y);*/
		}
	}

	void SkinnedQuad::Draw(const GameContext& gameContext)
	{
		gameContext.pRenderer->DrawSkinnedQuad(m_Vertices, m_pSkeleton, m_pTexture);
	}
}