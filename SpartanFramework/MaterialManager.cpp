#include "stdafx.h"
#include "MaterialManager.h"

std::vector<Material*> MaterialManager::m_pMaterials = std::vector<Material*>();

void MaterialManager::Cleanup()
{
	for (Material *pMat : m_pMaterials)
	{
		delete pMat;
	}
	m_pMaterials.clear();
}

unsigned int MaterialManager::CreateMaterial(const std::string &shaderPath)
{
	Material *pMaterial = ContentManager::GetInstance()->Load<Material>(shaderPath);

	m_pMaterials.push_back(pMaterial);

	return m_pMaterials.size() - 1;
}

Material * MaterialManager::GetMaterial(size_t id)
{
	if (id >= m_pMaterials.size()) return nullptr;
	return m_pMaterials[id];
}

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
}
