#include "stdafx.h"
#include "PostProcessingStack.h"
#include "MaterialManager.h"

namespace SpartanEngine
{
	PostProcessingStack::PostProcessingStack() : m_pTemporaryTexture(nullptr)
	{
	}

	PostProcessingStack::~PostProcessingStack()
	{
		m_pPostProcessMaterials.clear();
	}

	void PostProcessingStack::ClearPPStack()
	{
		m_pPostProcessMaterials.clear();
	}

	void PostProcessingStack::AddPP(PPMaterial* pMaterial)
	{
		if (pMaterial == nullptr) return;
		m_pPostProcessMaterials.push_back(pMaterial);
	}

	void PostProcessingStack::AddPP(size_t id)
	{
		AddPP(MaterialManager::GetMaterial<PPMaterial>(id));
	}

	void PostProcessingStack::RemovePP(PPMaterial* pMaterial)
	{
		m_pPostProcessMaterials.remove(pMaterial);
	}

	RenderTexture* PostProcessingStack::GetFinalTexture()
	{
		return m_pFinalTexture;
	}

	void PostProcessingStack::RenderPP(ScreenRect* pScreen, RenderTexture* pStartTexture)
	{
		if (m_pPostProcessMaterials.size() <= 0)
		{
			m_pFinalTexture = pStartTexture;
			return;
		}

		RenderTexture* pCurrentTexture = pStartTexture;
		auto dimensions = pCurrentTexture->GetDimensions();
		if (m_pTemporaryTexture == nullptr)
			m_pTemporaryTexture = RenderTexture::CreateRenderTexture(dimensions.x, dimensions.y, false);
		if (m_pTemporaryTexture->GetDimensions() != dimensions)
			m_pTemporaryTexture->Resize(dimensions.x, dimensions.y);

		RenderTexture* pNextTexture = m_pTemporaryTexture;
		for (auto pMaterial : m_pPostProcessMaterials)
		{
			pMaterial->Use();
			pNextTexture->Bind();
			pMaterial->SetBaseTexture(pCurrentTexture);
			pMaterial->SetShaderVars(pCurrentTexture);
			pScreen->DrawScreenMesh();
			pNextTexture->UnBind();

			m_pFinalTexture = pNextTexture;

			RenderTexture* tmpTexture = pNextTexture;
			pNextTexture = pCurrentTexture;
			pCurrentTexture = tmpTexture;
		}
	}
}