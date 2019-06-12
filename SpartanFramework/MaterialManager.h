#pragma once

class Material;

class MaterialManager
{
public:
	static void Cleanup();
	static unsigned int CreateMaterial(const std::string &shaderPath);
	static Material *GetMaterial(size_t id);

private:
	static std::vector<Material*> m_pMaterials;

private:
	MaterialManager();
	~MaterialManager();
};

