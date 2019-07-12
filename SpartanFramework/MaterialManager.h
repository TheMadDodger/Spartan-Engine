#pragma once
#include "Material.h"

class MaterialManager
{
public:
	static void Cleanup();

	template<typename T>
	static unsigned int CreateMaterial(const std::string &shaderPath)
	{
		ShaderData *pShader = ContentManager::GetInstance()->Load<ShaderData>(shaderPath);
		T *pMaterial = new T(pShader);

		Material *pNewMaterial = dynamic_cast<Material*>(pMaterial);

		if (pNewMaterial == nullptr)
		{
			delete pMaterial;
			Utilities::Debug::LogError("Error when trying to create material!");
			return 0;
		}

		m_pMaterials.push_back(pNewMaterial);

		return m_pMaterials.size() - 1;
	}

	static Material *GetMaterial(size_t id);

private:
	static std::vector<Material*> m_pMaterials;

private:
	MaterialManager();
	~MaterialManager();
};
