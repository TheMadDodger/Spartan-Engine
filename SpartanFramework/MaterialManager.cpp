#include "stdafx.h"
#include "MaterialManager.h"

std::vector<Material*> MaterialManager::m_pMaterials = std::vector<Material*>();

void MaterialManager::Cleanup()
{
	for (auto pMaterial : m_pMaterials)
	{
		delete pMaterial;
	}
	m_pMaterials.clear();
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
