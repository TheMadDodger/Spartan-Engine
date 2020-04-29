#pragma once
#include "Singleton.h"
#include "PPMaterial.h"
#include "RenderTexture.h"
#include "ScreenRect.h"

namespace SpartanEngine
{
	class PostProcessingStack : public Singleton<PostProcessingStack>
	{
	public:
		PostProcessingStack();
		~PostProcessingStack();

		void ClearPPStack();
		void AddPP(PPMaterial* pMaterial);
		void AddPP(size_t id);
		void RemovePP(PPMaterial* pMaterial);

		RenderTexture* GetFinalTexture();

	private:
		void RenderPP(ScreenRect* pScreen, RenderTexture* pStartTexture);

	private:
		friend class ScreenRect;
		list<PPMaterial*> m_pPostProcessMaterials;
		RenderTexture* m_pFinalTexture;
		RenderTexture* m_pTemporaryTexture;
	};
}